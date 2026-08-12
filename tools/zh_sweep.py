#!/usr/bin/env python3
"""Place vendored Zero Hour code in BFME retail .text by masked-byte search.

BFME 1 and Generals: Zero Hour are both SAGE/W3D games built with the same
compiler, so a ZH translation unit frequently emits function bodies that are
byte-identical to BFME's. This sweep compiles the vendored tree, carves each
function COMDAT out of the objects, blanks every relocation slot -- those four
bytes hold link-time addresses two different executables cannot be expected to
agree on -- and searches .text for a placement of what is left.

  compile   build ZH translation units into the sweep object cache
  match     carve and place every COMDAT            -> build/zh_sweep/match.json
  land      append ledger rows for placements that survive filtering
  packets   write conversion work packets for near misses at unclaimed addresses

A placement is evidence of identical CODE, which is not the same as evidence of
identity: `land` drops every placement that overlaps ground another row already
claims, that carries a compiler-local label instead of a name, or whose name the
ledger already spends at another address. Search is uncapped on purpose -- a
capped needle scan can miss the second placement of a body and report an
ambiguous match as a unique one.
"""
import argparse
import bisect
import json
import struct
import subprocess
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build

ROOT = build.ROOT
ZH = build.ZH_REFERENCE_ROOT
OBJ_DIR = ROOT / "build" / "spike_zh"
OUT_DIR = ROOT / "build" / "zh_sweep"
MATCH_JSON = OUT_DIR / "match.json"
PACKET_DIR = ROOT / "reverse" / "zh_sweep" / "packets"

MIN_FUNC = 24           # under this, a body is a stub that places all over .text
SEARCHABLE = 10         # a body whose longest reloc-free run is shorter has no needle
MIN_NEEDLE = 4          # under this a run matches so much of .text it is pure noise
NEAR_ALIGN = 0.85       # near miss worth a work packet
DIR32, REL32 = 0x0006, 0x0014
CODE_SECTION = 0x00000020       # IMAGE_SCN_CNT_CODE

# The subtrees the sweep compiles, in the order it compiles them. Their split is
# what build.source_needs_stlport keys on: the WWVegas libraries build against
# MSVC's own STL, the GameEngine trees need STLport.
SUBTREES = [
    "Libraries/Source/WWVegas/WW3D2",
    "Libraries/Source/WWVegas/WWMath",
    "Libraries/Source/WWVegas/WWLib",
    "GameEngine/Source/GameLogic",
    "GameEngine/Source/Common",
    "GameEngine/Source/GameClient",
]


def object_stem(source):
    """Sweep cache name for a ZH source: its last three path parts.

    Objects built by the original spike are named this way and are expensive to
    reproduce (a 400-TU wine sweep), so the naming stays as they left it.
    zh_sources() proves it stays one-to-one over the tree.
    """
    return "_".join(Path(source).with_suffix("").parts[-3:])


def zh_sources():
    """Sweep cache name -> repo-relative ZH source, proven unambiguous."""
    table = {}
    for path in sorted(ZH.rglob("*.cpp")):
        relative = path.relative_to(ROOT)
        stem = object_stem(relative)
        if stem in table:
            raise SystemExit(
                f"zh_sweep: object stem {stem!r} names two sources ({table[stem]} and "
                f"{relative}); the cache cannot say which object came from which")
        table[stem] = relative.as_posix()
    return table


def object_source(obj, sources):
    stem = obj.name[: -len(".obj")].removesuffix(".stl")
    source = sources.get(stem)
    if source is None:
        raise SystemExit(f"zh_sweep: {obj.name} has no source in the ZH tree — the object "
                         "cache holds something this sweep did not build")
    return source


def carve(data):
    """Yield (symbol, body, relocs) per function COMDAT of a COFF object.

    relocs are (offset, type, callee) restricted to the two i386 kinds whose
    bytes are a link-time address. Only symbols at offset zero of a code section
    are taken: those are whole COMDAT bodies, so the section size is the body
    size, with no guessing about where the next function starts.
    """
    machine, section_count, _, symbol_table, symbol_count, optional, _ = \
        struct.unpack_from("<HHIIIHH", data, 0)
    if machine != 0x14C:
        return
    sections = []
    for index in range(section_count):
        offset = 20 + optional + 40 * index
        name, _, _, raw_size, raw_pointer, reloc_pointer, _, reloc_count, _, characteristics = \
            struct.unpack_from("<8sIIIIIIHHI", data, offset)
        sections.append((name.rstrip(b"\0").decode(errors="replace"), raw_size,
                         raw_pointer, reloc_pointer, reloc_count, characteristics))
    strings = symbol_table + symbol_count * 18

    def name_at(offset):
        raw = data[offset : offset + 8]
        if raw[:4] == b"\0\0\0\0":
            start = strings + struct.unpack_from("<I", raw, 4)[0]
            return data[start : data.index(b"\0", start)].decode(errors="replace")
        return raw.rstrip(b"\0").decode(errors="replace")

    symbols, names, index = [], [], 0
    while index < symbol_count:
        offset = symbol_table + 18 * index
        value, section, kind, storage, aux = struct.unpack_from("<IhHBB", data, offset + 8)
        symbols.append((name_at(offset), value, section, kind, storage))
        # relocations index the raw table, so the auxiliary records a symbol
        # carries have to keep their slots in the name lookup
        names += [symbols[-1][0]] + [""] * aux
        index += 1 + aux

    for name, value, section, kind, storage in symbols:
        if section <= 0 or value != 0 or kind != 0x20 or storage not in (2, 3):
            continue
        section_name, raw_size, raw_pointer, reloc_pointer, reloc_count, characteristics = \
            sections[section - 1]
        if not section_name.startswith(".text") or not characteristics & CODE_SECTION:
            continue
        relocs = []
        for r in range(reloc_count):
            address, symbol_index, kind = struct.unpack_from("<IIH", data, reloc_pointer + 10 * r)
            if kind in (DIR32, REL32):
                relocs.append((address, kind, names[symbol_index]))
        yield name, data[raw_pointer : raw_pointer + raw_size], sorted(relocs)


def mask(body, relocs):
    """The body with every relocation slot blanked, plus which bytes were blanked."""
    masked, holes = bytearray(body), bytearray(len(body))
    for offset, _, _ in relocs:
        for index in range(offset, min(offset + 4, len(body))):
            masked[index] = 0
            holes[index] = 1
    return bytes(masked), bytes(holes)


def needles(holes, count=2):
    """Offsets and lengths of the longest reloc-free runs — the searchable parts."""
    runs, start = [], None
    for index, hole in enumerate(bytes(holes) + b"\1"):
        if not hole and start is None:
            start = index
        elif hole and start is not None:
            runs.append((index - start, start))
            start = None
    runs.sort(reverse=True)
    return runs[:count]


def placements(text, body, masked, holes):
    """Every offset in .text where the unmasked bytes of `body` appear.

    Uncapped: a limit on hits per needle silently turns a body that appears
    twice into a unique placement, which is exactly the error that would let an
    ICF-folded twin be landed under the wrong address.
    """
    found = set()
    runs = needles(holes)
    if not runs or runs[0][0] < SEARCHABLE:
        return found
    for length, offset in runs:
        if length < MIN_NEEDLE:
            continue
        needle = masked[offset : offset + length]
        position = text.find(needle)
        while position != -1:
            candidate = position - offset
            if 0 <= candidate <= len(text) - len(body):
                found.add(candidate)
            position = text.find(needle, position + 1)
    return found


def alignment(window, masked, holes):
    same = sum(1 for index in range(len(masked)) if holes[index] or window[index] == masked[index])
    return same / len(masked)


def retail_text():
    data = build.EXE.read_bytes()
    section = next(s for s in build.pe_sections(data) if s["name"] == ".text")
    return section["rva"], data[section["raw_pointer"] : section["raw_pointer"] + section["size"]]


def merged_claims():
    """Matched retail ranges, merged, plus a true overlap test over them.

    Containment ("is this whole body inside one claim?") is not the question a
    double-claim check asks: a body that starts inside a claim and runs past its
    end contains bytes another row already owns, and passes a containment test.

    Matched rows only, matching check_csv's overlap rule: an unmatched row is a
    hypothesis about an address, not proof that the ground is spoken for.
    """
    spans = []
    for row in build.load_function_rows():
        start = int(row["target_rva"], 16)
        spans.append((start, start + int(row["target_size"])))
    spans.sort()
    merged = []
    for start, end in spans:
        if merged and start <= merged[-1][1]:
            merged[-1][1] = max(merged[-1][1], end)
        else:
            merged.append([start, end])
    starts = [start for start, _ in merged]

    def overlaps(rva, size):
        index = bisect.bisect_right(starts, rva) - 1
        if index >= 0 and merged[index][1] > rva:
            return True
        index = bisect.bisect_left(starts, rva)
        return index < len(merged) and merged[index][0] < rva + size

    return overlaps


def do_compile(args):
    sources = []
    for subtree in SUBTREES:
        found = sorted((ZH / subtree).rglob("*.cpp"))
        if args.limit and len(found) > args.limit:
            step = len(found) / args.limit
            found = [found[int(i * step)] for i in range(args.limit)]
        sources += found
    OBJ_DIR.mkdir(parents=True, exist_ok=True)
    built = failed = cached = 0
    for source in sources:
        obj = OBJ_DIR / (object_stem(source.relative_to(ROOT))
                         + (".stl" if build.source_needs_stlport(source) else "") + ".obj")
        if obj.exists() and not args.force:
            cached += 1
            continue
        try:
            build.compile_source(source, obj)
            built += 1
        except SystemExit:
            # A ZH TU that will not compile is the expected minority (the sweep
            # runs at ~95%), not a reason to abandon the other 400.
            failed += 1
            print(f"  compile FAILED {source.relative_to(ROOT)}", flush=True)
    print(f"compile: {built} built, {cached} cached, {failed} failed "
          f"of {len(sources)} translation unit(s)")


def do_match(args):
    text_rva, text = retail_text()
    overlaps = merged_claims()
    sources = zh_sources()
    records, seen = [], set()
    for obj in sorted(OBJ_DIR.glob("*.obj")):
        source = object_source(obj, sources)
        for name, body, relocs in carve(obj.read_bytes()):
            if len(body) < MIN_FUNC or name in seen:
                continue
            seen.add(name)
            masked, holes = mask(body, relocs)
            runs = needles(holes)
            record = {"sym": name, "obj": obj.name, "source": source,
                      "size": len(body), "relocs": len(relocs)}
            exact, best, best_align = [], None, 0.0
            for candidate in placements(text, body, masked, holes):
                align = alignment(text[candidate : candidate + len(body)], masked, holes)
                if align == 1.0:
                    exact.append(candidate)
                if align > best_align:
                    best_align, best = align, candidate
            if len(exact) == 1:
                record["rva"] = text_rva + exact[0]
                record["bucket"] = ("exact-unique-claimed"
                                    if overlaps(record["rva"], len(body))
                                    else "exact-unique-unclaimed")
            elif len(exact) > 1:
                record["bucket"] = "exact-multi"
                record["hits"] = len(exact)
            elif best is not None:
                record["rva"] = text_rva + best
                record["bucket"] = "near"
                record["align"] = round(best_align, 3)
                record["claimed"] = overlaps(record["rva"], len(body))
            else:
                record["bucket"] = ("no-placement" if runs and runs[0][0] >= SEARCHABLE
                                    else "no-needle")
            records.append(record)
    OUT_DIR.mkdir(parents=True, exist_ok=True)
    MATCH_JSON.write_text(json.dumps(records, indent=1))
    counts, sizes = Counter(), Counter()
    for record in records:
        counts[record["bucket"]] += 1
        sizes[record["bucket"]] += record["size"]
    print(f"match: {len(records)} function(s) from {len(list(OBJ_DIR.glob('*.obj')))} object(s)")
    for bucket in sorted(counts):
        print(f"  {bucket:24s} {counts[bucket]:5d} funcs {sizes[bucket]:9,} bytes")
    print(f"  -> {MATCH_JSON.relative_to(ROOT)}")


def landable(records):
    """The exact-unique placements that carry a landable identity, and why the
    others do not. Each filter answers a different question, so a placement can
    fail several; the counts below are of placements failing each, not a split."""
    ledger = list(build.load_all_function_rows())
    claimed_names = {row["name"] for row in ledger}
    ledger_sizes = {int(row["target_rva"], 16): int(row["target_size"]) for row in ledger}
    overlaps = merged_claims()
    candidates = [r for r in records if r["bucket"] == "exact-unique-unclaimed"]
    address_use = Counter(r["rva"] for r in candidates)

    reasons, keep = Counter(), []
    for record in candidates:
        why = []
        if overlaps(record["rva"], record["size"]):
            why.append("overlaps-existing-claim")
        if ledger_sizes.get(record["rva"], record["size"]) != record["size"]:
            # even an unmatched row at this address fixes what size the function
            # is; two sizes at one address is a contradiction check_csv rejects
            why.append("address-held-at-another-size")
        if record["sym"].startswith("$L"):
            why.append("compiler-local-label")
        if record["sym"] in claimed_names:
            why.append("name-already-claimed")
        if address_use[record["rva"]] > 1:
            why.append("address-claimed-by-siblings")
        for reason in why:
            reasons[reason] += 1
        if why:
            record["rejected"] = why
        else:
            keep.append(record)
    return keep, reasons


NOTE = "zh-sweep exact-unique placement in unclaimed .text"


def ledger_line(record):
    return (f"{record['sym']},,0x{record['rva']:08X},{record['size']},{record['source']},"
            f"matched,{NOTE}")


def do_land(args):
    records = json.loads(MATCH_JSON.read_text())
    keep, reasons = landable(records)
    print(f"land: {sum(1 for r in records if r['bucket'] == 'exact-unique-unclaimed')} "
          f"exact-unique-unclaimed placement(s)")
    for reason, count in sorted(reasons.items()):
        print(f"  rejected {count:4d}  {reason}")
    print(f"  landable {len(keep):4d}  {sum(r['size'] for r in keep):,} bytes")
    if not args.apply:
        for record in sorted(keep, key=lambda r: r["rva"]):
            print(ledger_line(record))
        return

    # Append everything before verifying anything. These bodies call each other,
    # and a callee only resolves once its own row is in the ledger, so landing
    # source by source would reject a row purely for sorting before its callee.
    write_rows(keep)
    live = {record["sym"]: record for record in keep}
    for attempt in range(5):
        rejected = {}
        for source in sorted({record["source"] for record in live.values()}):
            verify = subprocess.run([sys.executable, str(ROOT / "tools" / "build.py"), source],
                                    cwd=ROOT, capture_output=True, text=True, timeout=900)
            if verify.returncode == 0:
                continue
            for line in verify.stdout.splitlines():
                if line.startswith("  FAIL "):
                    rejected[line[len("  FAIL "):].rsplit(" (", 1)[0]] = verify.stdout
        if not rejected:
            break
        for name, output in rejected.items():
            reason = next((l.strip() for l in output.splitlines()
                           if "unresolved call(s)" in l and name in output), "byte mismatch")
            print(f"  DROP {name}\n       {reason}")
            live.pop(name)
        # A dropped row can be the callee another surviving row needed, so the
        # survivors are only proven once a full pass rejects nothing.
        write_rows(live.values())
    else:
        raise SystemExit("zh_sweep: rows kept failing after 5 rounds; nothing landed")
    by_source = Counter(record["source"] for record in live.values())
    for source, count in sorted(by_source.items()):
        print(f"  +{count:3d} {source}")
    print(f"landed {len(live)} row(s), {sum(r['size'] for r in live.values()):,} bytes")


def write_rows(records):
    """Rewrite the ledger with exactly this sweep's rows appended.

    Binary, with explicit CRLF: the ledger is a CRLF file, and a text-mode
    rewrite silently normalises every line in it to LF — check_csv rejects the
    whole file for that, which reads as ledger corruption rather than as a
    landing bug.
    """
    kept = [line for line in build.FUNCTIONS.read_bytes().splitlines(keepends=True)
            if NOTE.encode() not in line]
    rows = [(ledger_line(record) + "\r\n").encode()
            for record in sorted(records, key=lambda r: r["rva"])]
    build.FUNCTIONS.write_bytes(b"".join(kept + rows))


def do_packets(args):
    records = json.loads(MATCH_JSON.read_text())
    near = [r for r in records if r["bucket"] == "near"
            and r["align"] >= NEAR_ALIGN and not r["claimed"]]
    text_rva, text = retail_text()
    overlaps = merged_claims()
    still_claimed = [r for r in near if overlaps(r["rva"], r["size"])]
    if still_claimed:
        raise SystemExit(f"zh_sweep: {len(still_claimed)} near match(es) sit on claimed "
                         "retail bytes; a packet for solved code is a wasted work slot")
    reloc_index = packet_relocs({r["obj"] for r in near})
    PACKET_DIR.mkdir(parents=True, exist_ok=True)
    for stale in PACKET_DIR.glob("*.md"):
        stale.unlink()
    for record in sorted(near, key=lambda r: r["rva"]):
        body = text[record["rva"] - text_rva : record["rva"] - text_rva + record["size"]]
        path = PACKET_DIR / f"{record['rva']:08x}.md"
        path.write_text(packet_text(record, body, reloc_index[(record["obj"], record["sym"])]))
    print(f"packets: {len(near)} written to {PACKET_DIR.relative_to(ROOT)} "
          f"({sum(r['size'] for r in near):,} bytes of unclaimed .text)")


def packet_relocs(objects):
    """(obj, symbol) -> relocations, for the objects the packets need."""
    index = {}
    for name in sorted(objects):
        for symbol, _, relocs in carve((OBJ_DIR / name).read_bytes()):
            index[(name, symbol)] = relocs
    return index


def disassemble(body, rva):
    scratch = OUT_DIR / "disassemble.bin"
    scratch.parent.mkdir(parents=True, exist_ok=True)
    scratch.write_bytes(body)
    listing = subprocess.run(
        ["objdump", "-b", "binary", "-m", "i386", "-M", "intel",
         f"--adjust-vma=0x{rva:x}", "-D", str(scratch)], capture_output=True)
    if listing.returncode != 0:
        raise SystemExit("zh_sweep: objdump failed: " + listing.stderr.decode(errors="replace"))
    lines = listing.stdout.decode(errors="replace").splitlines()
    body_start = next(i for i, line in enumerate(lines) if line.endswith(">:")) + 1
    return "\n".join(lines[body_start:])


def callee_pins(record, body, relocs, names):
    """Each REL32 callee with the address THIS call site encodes in retail.

    The displacement is read out of the retail bytes, so the address is the
    binary's answer rather than a guess: callee = site + 4 + displacement.
    """
    lines = []
    for offset, kind, callee in relocs:
        if kind != REL32 or offset + 4 > len(body):
            continue
        displacement = struct.unpack_from("<i", body, offset)[0]
        address = record["rva"] + offset + 4 + displacement
        known = " (already in the ledger)" if callee in names else ""
        lines.append(f"{callee},0x{address:08X}{known}")
    return "\n".join(lines) or "(no relative calls in this body)"


def packet_text(record, body, relocs):
    names = {row["name"] for row in build.load_all_function_rows()}
    return "\n".join([
        f"# Work packet: `{record['sym']}`",
        "",
        f"- retail address: `0x{record['rva']:08X}`, {record['size']} bytes, unclaimed",
        f"- the Zero Hour twin of this body agrees on {record['align'] * 100:.1f}% of its "
        "bytes outside relocation sites",
        f"- reference source: `{record['source']}`",
        "",
        "## What this is",
        "",
        "The vendored Zero Hour tree contains the same function. Compiled with this",
        "repo's toolchain it lands *near* these retail bytes but not on them, so the",
        "two versions differ by something real: a changed constant, an extra member,",
        "a different inlining decision. Port the reference body into a `Code/` source,",
        "then close the remaining gap against the disassembly below.",
        "",
        "## Retail disassembly (the exact target)",
        "",
        "```",
        disassemble(body, record["rva"]),
        "```",
        "",
        "## Callee pins (paste unresolved ones into reverse/symbols.csv)",
        "",
        "```",
        callee_pins(record, body, relocs, names),
        "```",
        "",
        "## Landing it",
        "",
        f"Add a row to `reverse/functions.csv` naming your source, then run",
        f"`./build.sh '{record['sym']}'`. It passes only when every byte outside a",
        "relocation site is identical to the address above.",
        "",
    ])


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)
    compile_parser = sub.add_parser("compile", help="build ZH TUs into the object cache")
    compile_parser.add_argument("--limit", type=int, default=0,
                                help="sample at most N sources per subtree")
    compile_parser.add_argument("--force", action="store_true", help="rebuild cached objects")
    compile_parser.set_defaults(run=do_compile)
    sub.add_parser("match", help="place every carved COMDAT in .text").set_defaults(run=do_match)
    land_parser = sub.add_parser("land", help="ledger rows for landable placements")
    land_parser.add_argument("--apply", action="store_true",
                             help="append the rows and byte-verify each source")
    land_parser.set_defaults(run=do_land)
    sub.add_parser("packets", help="work packets for unclaimed near misses").set_defaults(
        run=do_packets)
    args = parser.parse_args()
    args.run(args)


if __name__ == "__main__":
    main()
