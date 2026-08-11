#!/usr/bin/env python3
"""Report exact-match coverage of the retail executable's .text section.

Every retail byte is counted once. Clean C++ ownership wins when it overlaps an
assembly-backed row (including ICF aliases), leaving "ASM-only" as actionable
porting debt. This reads the ledger but compiles nothing; build.sh is proof.

  python3 tools/progress.py                # HEAD vs worktree
  python3 tools/progress.py REF            # REF vs worktree
  python3 tools/progress.py REF1..REF2     # between two commits
  python3 tools/progress.py --details REF  # include ledger diagnostics
"""
import argparse
import csv
import re
import subprocess
from collections import Counter
from functools import lru_cache
from pathlib import Path

import build
from gaps import padding_split
from list_naked_candidates import NAKED_RE, block_bytes, symbol_comment

ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS = "reverse/functions.csv"
CPP_SUFFIXES = {".c", ".cc", ".cpp", ".cxx"}
ASM_SUFFIXES = {".asm", ".s"}
# Upstream libraries vendored into the tree. Reproducing their bytes is real
# code, but it is not recovering this game's identity, so they get their own
# lane instead of inflating the reverse-engineered figure. EA-authored
# libraries (EAC, DirtySock, debug) are the game and stay out of this list.
VENDORED_ROOTS = (
    "Code/Libraries/Source/Compression/ZLib/",
    "Code/Libraries/Source/JPEG/",
    "Code/Libraries/Source/LibPNG/",
    "Code/Libraries/Source/Lua/",
    "vendor/",
)
GEN_NOTE_RE = re.compile(r"(?:^|;)\s*gen-[a-z]")
EMIT_RE = re.compile(
    r"\b_{1,2}emit\s+(?:0x([0-9a-fA-F]{1,2})|([0-9a-fA-F]{1,3})h)\b",
    re.IGNORECASE,
)
ASM_BLOCK_RE = re.compile(r"^\s*__asm\b")
# Prefilter for sources worth scanning: naked bodies or emitted bytes. Plain
# "_emit" also hits "__emit"; a false hit only costs reading one extra file.
ASM_MARKER_GREP = r"__declspec[[:space:]]*\([[:space:]]*naked|_emit"


@lru_cache(maxsize=None)
def _functions_text(ref):
    """Return the whole ledger as text for one repository state."""
    if ref is None:
        return (ROOT / FUNCTIONS).read_text(encoding="utf-8")
    proc = subprocess.run(
        ["git", "show", f"{ref}:{FUNCTIONS}"],
        cwd=ROOT, capture_output=True, text=True,
    )
    if proc.returncode != 0:
        raise SystemExit(f"cannot read {FUNCTIONS} at {ref}: {proc.stderr.strip()}")
    return proc.stdout


def matched_at(ref):
    """Return {(name, target_rva): (size, source)} for one repository state."""
    out = {}
    for row in csv.DictReader(_functions_text(ref).splitlines()):
        if row["status"] == "matched":
            out[(row["name"], row["target_rva"])] = (
                int(row["target_size"]), row["source"])
    return out


def notes_at(ref):
    """Return {(name, target_rva): notes} for the matched rows at one state."""
    return {
        (row["name"], row["target_rva"]): row["notes"]
        for row in csv.DictReader(_functions_text(ref).splitlines())
        if row["status"] == "matched"
    }


def retail_text():
    """Return (start RVA, byte size) using the build gate's PE parser/baseline."""
    sections = build.pe_sections(build.EXE.read_bytes())
    text = next((section for section in sections if section["name"] == ".text"), None)
    if text is None:
        raise SystemExit(f"{build.EXE}: no .text section")
    return text["rva"], text["size"]


def merge_intervals(intervals):
    """Return sorted, non-overlapping half-open intervals."""
    merged = []
    for start, end in sorted(intervals):
        if start >= end:
            continue
        if merged and start <= merged[-1][1]:
            merged[-1] = (merged[-1][0], max(merged[-1][1], end))
        else:
            merged.append((start, end))
    return merged


def interval_bytes(intervals):
    return sum(end - start for start, end in merge_intervals(intervals))


def source_kind(source):
    suffix = Path(source).suffix.lower()
    if suffix in CPP_SUFFIXES:
        return "cpp"
    if suffix in ASM_SUFFIXES:
        return "asm"
    raise SystemExit(
        f"matched source has unsupported suffix {suffix or '<none>'}: {source}")


def _is_naked_declaration(lines, index):
    """True for an explicit-instantiation declaration with no function body."""
    for line in lines[index:]:
        brace = line.find("{")
        semicolon = line.find(";")
        if semicolon >= 0 and (brace < 0 or semicolon < brace):
            return True
        if brace >= 0:
            return False
    return True


def _signature_identity(name):
    """Return a conservative source-level Class::method spelling, when simple."""
    special = re.match(r"^\?\?([014])([A-Za-z_][A-Za-z0-9_]*)@@", name)
    if special:
        code, cls = special.groups()
        method = {"0": cls, "1": f"~{cls}", "4": "operator="}[code]
        return f"{cls}::{method}"
    normal = re.match(r"^\?([A-Za-z_][A-Za-z0-9_]*)@([A-Za-z_][A-Za-z0-9_]*)@@", name)
    if normal:
        return f"{normal.group(2)}::{normal.group(1)}"
    c_name = re.match(r"^_([A-Za-z_][A-Za-z0-9_]*)$", name)
    return c_name.group(1) if c_name else None


@lru_cache(maxsize=None)
def scan_naked_bodies(text):
    """Return proven asm implementation evidence without treating a file as a unit.

    Triggers on __declspec(naked) bodies and on bare __asm blocks. A bare
    __asm block is evidence only when it emits raw bytes: mnemonic-only inline
    asm inside real C++ (the period cpuid idiom) stays C++, and 18 fleet lifts
    proved plain functions can smuggle a full __emit spray past a naked-only
    scan and inflate the C++ figure."""
    lines = text.splitlines()
    bodies = []
    last_end = -1
    for index, line in enumerate(lines):
        if index <= last_end:
            continue
        naked = bool(NAKED_RE.search(line)) and not _is_naked_declaration(lines, index)
        if not naked and not ASM_BLOCK_RE.match(line):
            continue
        _, end = block_bytes(lines, index)
        emitted = []
        for body_line in lines[index:end + 1]:
            for match in EMIT_RE.finditer(body_line):
                emitted.append(int(match.group(1) or match.group(2), 16))
        if not naked and not emitted:
            continue
        last_end = end
        declaration = []
        for declaration_line in lines[index:end + 1]:
            before_brace, brace, _ = declaration_line.partition("{")
            declaration.append(before_brace)
            if brace:
                break
        bodies.append({
            "symbol": symbol_comment(lines, index),
            "signature": " ".join(" ".join(declaration).split()),
            "emitted": bytes(emitted),
            "naked": naked,
        })
    return tuple(bodies)


def naked_cpp_rows(matched, source_texts, target_reader=build.read_target_bytes):
    """Return matched-row keys proven to be naked assembly inside C/C++ files."""
    rows_by_source = {}
    for key, value in matched.items():
        if Path(value[1]).suffix.lower() in CPP_SUFFIXES:
            rows_by_source.setdefault(value[1], []).append((key, value))

    naked = set()
    target_cache = {}
    for source, text in source_texts.items():
        rows = rows_by_source.get(source, [])
        bodies = scan_naked_bodies(text)
        if not rows or not bodies:
            continue
        # Name and signature evidence is only trusted from naked bodies: a
        # bare __asm spray sits inside an ordinary function whose declaration
        # matches its row by construction. Sprays interleave __emit bytes with
        # real mnemonics at relocated call sites, so full byte equality cannot
        # prove them either; the discriminator is emitted mass. The period
        # _emit idiom (cpuid) is a few bytes of a body, a lift is most of it.
        naked_bodies = [body for body in bodies if body["naked"]]
        symbols = {body["symbol"] for body in naked_bodies if body["symbol"]}
        emitted = {body["emitted"] for body in bodies if body["emitted"]}
        signatures = [body["signature"] for body in naked_bodies]
        spray_mass = sum(len(body["emitted"]) for body in bodies if not body["naked"])
        for key, (size, _) in rows:
            name, target_rva = key
            identity = _signature_identity(name)
            proven = name in symbols or (
                identity is not None and any(
                    re.search(rf"(?<![A-Za-z0-9_]){re.escape(identity)}\s*\(", signature)
                    for signature in signatures))
            if not proven and emitted:
                target_key = (int(target_rva, 16), size)
                if target_key not in target_cache:
                    target_cache[target_key] = target_reader(*target_key)
                proven = target_cache[target_key] in emitted
            if proven or (len(rows) == 1 and len(naked_bodies) == 1) or \
                    (len(rows) == 1 and spray_mass * 2 >= size):
                naked.add(key)
    return naked


def _batch_git_texts(ref, paths):
    if not paths:
        return {}
    request = "".join(f"{ref}:{path}\n" for path in paths).encode()
    proc = subprocess.run(
        ["git", "cat-file", "--batch"], cwd=ROOT, input=request,
        capture_output=True,
    )
    if proc.returncode != 0:
        raise SystemExit(f"cannot read naked sources at {ref}: {proc.stderr.decode().strip()}")
    output = proc.stdout
    offset = 0
    texts = {}
    for path in paths:
        line_end = output.find(b"\n", offset)
        if line_end < 0:
            raise SystemExit(f"cannot read {path} at {ref}: malformed git cat-file output")
        header = output[offset:line_end].decode(errors="replace")
        offset = line_end + 1
        fields = header.rsplit(" ", 2)
        if len(fields) != 3 or fields[1] != "blob":
            raise SystemExit(f"cannot read {path} at {ref}: {header}")
        size = int(fields[2])
        texts[path] = output[offset:offset + size].decode("utf-8", errors="replace")
        offset += size + 1  # blob plus cat-file's separating newline
    return texts


def naked_source_texts(matched, ref):
    """Read only matched C/C++ sources containing naked bodies at one state."""
    sources = {
        source for _, source in matched.values()
        if Path(source).suffix.lower() in CPP_SUFFIXES
    }
    if ref is None:
        grep = subprocess.run(
            ["git", "grep", "-l", "-E", ASM_MARKER_GREP, "--", "Code"],
            cwd=ROOT, capture_output=True, text=True,
        )
        if grep.returncode not in (0, 1):
            raise SystemExit(f"cannot scan worktree naked sources: {grep.stderr.strip()}")
        paths = set(grep.stdout.splitlines()) & sources
        tracked = set(subprocess.run(
            ["git", "ls-files", "-z", "--", "Code"], cwd=ROOT,
            capture_output=True, check=True,
        ).stdout.decode(errors="replace").split("\0"))
        changed = set(subprocess.run(
            ["git", "diff", "--name-only", "-z", "HEAD", "--", "Code"],
            cwd=ROOT, capture_output=True, check=True,
        ).stdout.decode(errors="replace").split("\0"))
        disk_paths = paths & (changed | (sources - tracked))
        for source in (changed & sources) | (sources - tracked):
            if not (ROOT / source).is_file():
                raise SystemExit(f"cannot read matched source {source}")
        texts = _batch_git_texts("HEAD", sorted(paths - disk_paths))
        for source in sources - tracked:
            text = (ROOT / source).read_bytes().decode("utf-8", errors="replace")
            if NAKED_RE.search(text) or EMIT_RE.search(text):
                disk_paths.add(source)
        for source in disk_paths:
            texts[source] = (ROOT / source).read_bytes().decode("utf-8", errors="replace")
        return texts

    proc = subprocess.run(
        ["git", "grep", "-l", "-E", ASM_MARKER_GREP, ref, "--", "Code"],
        cwd=ROOT, capture_output=True, text=True,
    )
    if proc.returncode not in (0, 1):
        raise SystemExit(f"cannot scan naked sources at {ref}: {proc.stderr.strip()}")
    prefix = f"{ref}:"
    paths = []
    for line in proc.stdout.splitlines():
        path = line[len(prefix):] if line.startswith(prefix) else line.split(":", 1)[-1]
        if path in sources:
            paths.append(path)
    return _batch_git_texts(ref, sorted(paths))


def naked_cpp_rows_at(matched, ref):
    return naked_cpp_rows(matched, naked_source_texts(matched, ref))


def coverage(matched, text_start, text_size, naked_rows=()):
    """Return absolute .text-byte ownership for clean C++ and assembly rows."""
    text_end = text_start + text_size
    cpp = []
    asm = []
    naked_rows = set(naked_rows)
    for key, (size, source) in matched.items():
        _, target_rva = key
        kind = source_kind(source)
        if kind == "cpp" and key in naked_rows:
            kind = "asm"
        start = max(int(target_rva, 16), text_start)
        end = min(int(target_rva, 16) + size, text_end)
        if start >= end:
            continue
        (asm if kind == "asm" else cpp).append((start, end))

    cpp_bytes = interval_bytes(cpp)
    exact_bytes = interval_bytes(cpp + asm)
    return {
        "cpp": cpp_bytes,
        "asm_only": exact_bytes - cpp_bytes,
        "unmatched": text_size - exact_bytes,
        "exact": exact_bytes,
        "text": text_size,
    }


def identity_lane(source, notes):
    """Return the identity-axis lane for a matched row.

    This axis is independent of the code axis on purpose. A gen-* funclet is
    compiled C++ on the code axis and a placeholder on this one, and both
    statements are true at once, so neither axis can contradict the other.
    """
    if GEN_NOTE_RE.search(notes):
        return "generated"
    if source.startswith(VENDORED_ROOTS):
        return "vendored"
    return "real"


def identity_split(matched, notes, text_start, text_size):
    """Return per-lane .text bytes on the identity axis.

    Real identity wins an overlap the way clean C++ does on the code axis: an
    ICF alias shared with a generated placeholder is still a named function.
    """
    text_end = text_start + text_size
    lanes = {"real": [], "vendored": [], "generated": []}
    for key, (size, source) in matched.items():
        start = max(int(key[1], 16), text_start)
        end = min(int(key[1], 16) + size, text_end)
        if start >= end:
            continue
        lanes[identity_lane(source, notes[key])].append((start, end))
    real = interval_bytes(lanes["real"])
    vendored = interval_bytes(lanes["real"] + lanes["vendored"]) - real
    total = interval_bytes(lanes["real"] + lanes["vendored"] + lanes["generated"])
    return {"real": real, "vendored": vendored,
            "generated": total - real - vendored}


def real_code_denominator(text_start, text_size):
    """Return (0xCC padding bytes, real code bytes) across the whole section.

    This is the denominator the porting effort is actually measured against:
    3.3 MB of the section is inter-function 0xCC filler that no one will ever
    port, including a single 982,242-byte block at 0xB028EE. Counted over the
    whole section rather than over unclaimed gaps so the denominator does not
    drift every time a function is matched.
    """
    return padding_split(build.read_target_bytes(text_start, text_size))


def percent(count, total):
    return 100.0 * count / total if total else 0.0


def format_delta(current, previous, total):
    byte_delta = current - previous
    return f"{byte_delta:+,} bytes, {percent(byte_delta, total):+.2f} pp"


def print_scorecard(ref1, label2, old_stats, new_stats):
    total = new_stats["text"]
    print(f"retail .text exact coverage {ref1} -> {label2} ({total:,} bytes)")
    rows = (
        ("C++ exact", "cpp"),
        ("ASM-only exact", "asm_only"),
        ("Unmatched", "unmatched"),
        ("Total exact", "exact"),
    )
    for label, key in rows:
        value = new_stats[key]
        delta = format_delta(value, old_stats[key], total)
        print(f"  {label:<15} {value:>10,} bytes ({percent(value, total):6.2f}%)"
              f"  delta {delta}")


def print_real_code(padding, denominator, old_stats, new_stats,
                    old_identity, new_identity):
    print(f"\nreal-code view (.text minus {padding:,} bytes of 0xCC padding "
          f"= {denominator:,} bytes)")
    rows = (
        ("Total exact", new_stats["exact"], old_stats["exact"]),
        ("code: C++", new_stats["cpp"], old_stats["cpp"]),
        ("code: assembly", new_stats["asm_only"], old_stats["asm_only"]),
        ("identity: real", new_identity["real"], old_identity["real"]),
        ("identity: generated", new_identity["generated"], old_identity["generated"]),
        ("identity: vendored", new_identity["vendored"], old_identity["vendored"]),
    )
    for label, value, previous in rows:
        print(f"  {label:<20} {value:>10,} bytes ({percent(value, denominator):6.2f}%)"
              f"  delta {format_delta(value, previous, denominator)}")


def marker_delta(ref1, ref2):
    """Net present-unmatched/absent-from-retail markers added between states."""
    cmd = ["git", "diff", ref1] + ([ref2] if ref2 else []) + ["--", "Code"]
    diff = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True).stdout
    added = removed = 0
    for line in diff.splitlines():
        if line.startswith("+++") or line.startswith("---"):
            continue
        if "present-unmatched" in line or "absent-from-retail" in line:
            if line.startswith("+"):
                added += 1
            elif line.startswith("-"):
                removed += 1
    return added - removed


def area(source):
    parts = source.split("/")
    return "/".join(parts[:2]) if len(parts) > 1 else source


def asm_diagnostics(matched, naked_rows):
    naked_rows = set(naked_rows)
    sources = {
        source for key, (_, source) in matched.items()
        if Path(source).suffix.lower() in ASM_SUFFIXES or key in naked_rows
    }
    rows = sum(
        1 for key, (_, source) in matched.items()
        if Path(source).suffix.lower() in ASM_SUFFIXES or key in naked_rows
    )
    return rows, len(sources)


def print_details(ref1, ref2, old, new, old_naked=(), new_naked=()):
    added = {name: new[name] for name in new.keys() - old.keys()}
    removed = {name: old[name] for name in old.keys() - new.keys()}
    print("\nledger details (diagnostics, not unique-byte progress)")
    print(f"  matched rows:      {len(old):,} -> {len(new):,}"
          f"  (+{len(added):,}, -{len(removed):,})")
    print(f"  distinct RVAs:     {len({int(rva, 16) for _, rva in old}):,}"
          f" -> {len({int(rva, 16) for _, rva in new}):,}")
    old_asm_rows, old_asm_files = asm_diagnostics(old, old_naked)
    new_asm_rows, new_asm_files = asm_diagnostics(new, new_naked)
    print(f"  ASM-backed rows:   {old_asm_rows:,} -> {new_asm_rows:,}")
    print(f"  ASM-bearing files: {old_asm_files:,} -> {new_asm_files:,}")
    print(f"  unclaimed markers: {marker_delta(ref1, ref2):+d}")

    if added:
        by_area = Counter()
        by_file = Counter()
        for _, source in added.values():
            by_area[area(source)] += 1
            by_file[source] += 1
        print("  added by area: "
              + ", ".join(f"{name} +{count}" for name, count in by_area.most_common()))
        print("  top added files:")
        for source, count in by_file.most_common(10):
            print(f"    +{count:<4d} {source}")
    if removed:
        print("  removed rows:")
        for (name, _), (size, source) in sorted(removed.items())[:10]:
            print(f"    -{size:<5d} {source}  {name[:60]}")


def parse_range(value):
    if ".." in value:
        ref1, _, ref2 = value.partition("..")
        return ref1, ref2 or None
    return value, None


def main():
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("range", nargs="?", default="HEAD",
                        help="REF (vs worktree) or REF1..REF2")
    parser.add_argument("--details", action="store_true",
                        help="show row, RVA, marker, area, and file diagnostics")
    args = parser.parse_args()

    ref1, ref2 = parse_range(args.range)
    old = matched_at(ref1)
    new = matched_at(ref2)
    text_start, text_size = retail_text()
    old_naked = naked_cpp_rows_at(old, ref1)
    new_naked = naked_cpp_rows_at(new, ref2)
    old_stats = coverage(old, text_start, text_size, old_naked)
    new_stats = coverage(new, text_start, text_size, new_naked)
    label2 = ref2 or "worktree"

    print_scorecard(ref1, label2, old_stats, new_stats)
    padding, denominator = real_code_denominator(text_start, text_size)
    print_real_code(
        padding, denominator, old_stats, new_stats,
        identity_split(old, notes_at(ref1), text_start, text_size),
        identity_split(new, notes_at(ref2), text_start, text_size))
    if args.details:
        print_details(ref1, ref2, old, new, old_naked, new_naked)
    print("\nledger-derived; a clean build.sh run is the byte-match proof.")


if __name__ == "__main__":
    main()
