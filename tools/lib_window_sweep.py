#!/usr/bin/env python3
"""Needle-place release-library function bodies into retail's library territory.

The linker copied whole COMDATs out of the static libraries this project ships
as build inputs, so 800 KB of retail `.text` is Microsoft's compiled code. The
attached rows prove that per body: `./build.sh` unpacks the archive member a
row's `member=` note names and byte-compares it against retail with every
relocation site masked. This sweep finds the bodies that have not been attached
yet, and it decides where each one went under one explicit standard.

THE COUNT-AGREEMENT STANDARD
----------------------------
A masked body is not a unique fingerprint. A 40-byte prologue-heavy span can
sit at several addresses, and picking one because "it matched" is how a wave
lands 17 wrong addresses. So a placement is only claimed when all three hold:

  in-window        the address lies in the sub-range of [0x9F6C00, 0xB00000)
                   that this library already owns in the ledger. The four
                   libraries occupy four contiguous, non-overlapping runs (see
                   WINDOWS below); a d3dx9 body found inside dxerr9's run is a
                   coincidence, not a placement.
  count-agreement  retail holds no MORE copies of a body than the archive
                   supplies. A class with 3 archive instances and 4 in-window
                   hits is over-subscribed: at least one hit is a collision, we
                   cannot tell which, and the whole class is refused.
  archive-order    with the counts agreeing, the i-th placement by ascending
                   RVA is the i-th instance in archive order. The linker emits
                   COMDATs in the order it pulls members in, so this is the
                   assignment, not a guess among equals.

This is deliberately WEAKER than global uniqueness, which is why the standard
is written down here and in vendor/d3dx9/PROVENANCE.txt rather than left
implicit in a matcher. Its corroborations and its limits are recorded there.

Two tests keep the ordering premise honest, because ordering is the part of the
standard that can be wrong while every byte still matches:

  ledger anchors   a class containing a body the ledger ALREADY attaches is a
                   class whose ordering has a known answer. If ascending-RVA
                   order disagrees with that answer, the premise failed here
                   and the WHOLE class is refused — not just the bad pair.
  callee targets   two masked-identical bodies differ exactly at their
                   relocation slots, and retail has those slots resolved. Every
                   REL32 in a claimed body is decoded and the archive's own
                   copy of the named callee must be at the far end. This is
                   what separates `??_GCSprite` from `??_GCCodec`: 28 identical
                   bytes, but one calls ??1CCodec and the linker wrote that
                   address down. 53 placements ascending order got wrong were
                   caught this way; they are refused, not repaired, because
                   repairing them means choosing among members that define the
                   same COMDAT and that is a second standard, not this one.

LEGALITY
--------
Placement says where the bytes are. Legality says whether the ledger will take
the row today:

  pure-unclaimed   overlaps no matched row                    -> plain append
  dump-exact       is exactly one gen-dump row's (rva, size)  -> supersede
  dump-padded      a gen-dump row starts here and is longer than the stripped
                   body but still inside the member's raw span, and the raw
                   span masked-verifies over the row's full extent -> supersede
                   at the DUMP row's size (validate_rows only supersedes an
                   exact range, and the trailing bytes are the member's own
                   0xCC padding, which retail kept)
  dump-mismatch    overlaps gen-dump rows on some other extent -> boundary
                   surgery, not this wave's business
  held-overlap     overlaps a real row                        -> refused

Usage
  python3 tools/lib_window_sweep.py --report
  python3 tools/lib_window_sweep.py --emit wave.csv --legal dump-exact,pure-unclaimed
"""
import argparse
import bisect
import csv
import re
import subprocess
import sys
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build as B
import coffar
import locate

ROOT = B.ROOT
MEMBER_CACHE = ROOT / "build" / "lib_window_sweep" / "members"

VC_LIB = (ROOT / "build/toolchains/vs2003/Program Files"
          / "Microsoft Visual Studio .NET 2003/Vc7/lib")
PSDK_LIB = (ROOT / "build/toolchains/vs2003/Program Files"
            / "Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Lib")

# The exe links /MD, so the static CRTs cannot be what retail holds; they are
# swept anyway because a handful of statics (RunTmChk, msvcrt's own stubs) do
# get pulled in, and because a body that ALSO exists in libcmt is evidence
# about which archive a CRT-window placement came from.
DEBUG_VARIANTS = {"libcd", "libcmtd", "libcpd", "libcpmtd", "msvcrtd", "msvcprtd",
                  "comsuppd", "comsuppwd", "oledbd"}

# Library territory, and the run each archive owns inside it. Each bound is the
# hull of that archive's ALREADY-ATTACHED rows, rounded out to the next
# library's first attached row.
#
# d3dx9's run starts BELOW its lowest attached row (0xA0009A) and below the
# 0xA00000 vendor/d3dx9/PROVENANCE.txt states: [0x9F8AC0, 0xA00000) holds
# d3dxmath.obj laid out in object order — ?WithinEpsilon, ?sincosf,
# c_D3DXFloat32To16Array, then thirty init_/c_ pairs in source sequence. Only
# one d3dxmath body had ever been attached, so the region read as unowned. The
# ledger cannot bound this window; the object-order run is what does.
WIN_LO, WIN_HI = 0x9F6C00, 0xB00000
WINDOWS = {
    "crt": (0x9F6C00, 0x9F8AC0),
    "d3dx9": (0x9F8AC0, 0xAD5401),
    "dxerr9": (0xAD5401, 0xAFD550),
    "comsupp": (0xAFD550, 0xB00000),
}

# tag -> (ledger source path, window key). A tag with no entry is CRT-window
# and has no ledger home yet; it is swept for accounting and refused for
# emission rather than silently attached to the wrong archive.
LEDGER_SOURCE = {
    "d3dx9": ("vendor/d3dx9/d3dx9.lib", "d3dx9"),
    "dxerr9": ("vendor/dxerr9/dxerr9.lib", "dxerr9"),
    "vcomsupp": ("vendor/comsupp/comsupp.lib", "comsupp"),
    "comsupp": ("vendor/comsupp/comsupp.lib", "comsupp"),
    "comsuppw": ("vendor/comsupp/comsupp.lib", "comsupp"),
}
for _stem in ("libc", "libcmt", "libcp", "libcpmt", "msvcrt", "msvcprt",
              "oldnames", "RunTmChk"):
    LEDGER_SOURCE.setdefault(
        _stem, (str((VC_LIB / f"{_stem}.lib").relative_to(ROOT)), "crt"))
for _stem in ("strsafe", "bufferoverflow"):
    LEDGER_SOURCE.setdefault(
        _stem, (str((PSDK_LIB / f"{_stem}.lib").relative_to(ROOT)), "crt"))

# A span shorter than this carries too little shape to place by needle at all,
# and build.py refuses a masked comparison with fewer than MIN_LIB_CONCRETE
# bytes outside a relocation site as proving nothing.
MIN_SPAN = 16
MEMBER_NOTE_RE = re.compile(r"(?:^|;)member=([^;]+)")
OBJECT_SYMBOL_RE = re.compile(r"(?:^|;)object-symbol=([^;]+)")


class SweepError(Exception):
    """The sweep found something it must not route around."""


# --------------------------------------------------------------------------
# inputs
# --------------------------------------------------------------------------

def archive_paths():
    """{tag: path} for every release archive and loose object worth sweeping."""
    libs = {}
    if not VC_LIB.is_dir():
        raise SweepError(f"{VC_LIB.relative_to(ROOT)} is not a directory — the VS2003 "
                         "toolchain is a tracked build input; this sweep cannot run without it")
    for path in sorted(VC_LIB.glob("*.lib")):
        if path.stem in DEBUG_VARIANTS:
            continue
        libs[path.stem] = path
    for path in sorted(VC_LIB.glob("*.obj")):
        libs["obj:" + path.stem] = path
    for tag, path in [("d3dx9", ROOT / "vendor/d3dx9/d3dx9.lib"),
                      ("dxerr9", ROOT / "vendor/dxerr9/dxerr9.lib"),
                      ("vcomsupp", ROOT / "vendor/comsupp/comsupp.lib"),
                      ("strsafe", PSDK_LIB / "strsafe.lib"),
                      ("bufferoverflow", PSDK_LIB / "bufferoverflow.lib")]:
        if path.exists():
            libs[tag] = path
    return libs


def tracked_sources():
    """The set of repo-relative paths git holds, so no wave can `git add` a 5 MB lib."""
    out = subprocess.run(["git", "-C", str(ROOT), "ls-files", "-z", "--",
                          "vendor", "build/toolchains"],
                         capture_output=True, text=True, check=True)
    return set(out.stdout.split("\0")) - {""}


class Ledger:
    """The matched rows, indexed the three ways this sweep asks about them."""

    def __init__(self):
        self.rows = []
        with (ROOT / "reverse" / "functions.csv").open(newline="", encoding="utf-8") as handle:
            for record in csv.DictReader(handle):
                if record["status"] != "matched":
                    continue
                source = record["source"]
                lower = source.lower()
                kind = ("dump" if lower.endswith((".asm", ".s"))
                        else "lib" if lower.endswith(".lib") else "held")
                notes = record["notes"]
                symbol = record["name"]
                match = OBJECT_SYMBOL_RE.search(notes)
                if match:
                    symbol = match.group(1)
                member = MEMBER_NOTE_RE.search(notes)
                self.rows.append({
                    "name": record["name"], "rva": int(record["target_rva"], 16),
                    "size": int(record["target_size"]), "kind": kind, "source": source,
                    "symbol": symbol, "member": member.group(1) if member else None,
                    "is_dump": B.is_scaffold_row({"notes": notes}),
                })
        self.names = {row["name"] for row in self.rows}
        self.by_rva_sorted = sorted(self.rows, key=lambda row: row["rva"])
        self.starts = [row["rva"] for row in self.by_rva_sorted]
        self.dump_at = {row["rva"]: row for row in self.rows if row["is_dump"]}
        self.attached_rvas = {row["rva"] for row in self.rows if row["kind"] == "lib"}
        # Keyed by (source, member, symbol), NOT by address: the question this
        # answers is "has the ledger already consumed this COMDAT?", and asking
        # it by placement lets a body the ledger holds at a size we disagree
        # about be claimed a second time under a second name.
        self.consumed = {}
        for row in self.rows:
            if row["kind"] != "lib" or row["member"] is None:
                continue
            key = (row["source"], row["member"], row["symbol"])
            self.consumed.setdefault(key, []).append(row)
        self.widest = max((row["size"] for row in self.rows), default=0)

    def overlapping(self, rva, size):
        """Every matched row whose range intersects [rva, rva+size).

        Walks back from the first row starting at or after the end. `widest` is
        the real bound: stopping at the first non-overlapping row (what the
        spike did) walks straight past a long row that starts far earlier and
        still covers this address, and reports the ground as free.
        """
        out = []
        index = bisect.bisect_left(self.starts, rva + size) - 1
        while index >= 0:
            row = self.by_rva_sorted[index]
            if rva - row["rva"] > self.widest:
                break
            if row["rva"] + row["size"] > rva:
                out.append(row)
            index -= 1
        return out


# --------------------------------------------------------------------------
# span pool
# --------------------------------------------------------------------------

def canon(span, relocs):
    """The span with every relocation slot zeroed — its identity across instances."""
    out = bytearray(span)
    for offset, rtype, _ in relocs:
        width = coffar.RELOC_WIDTH.get(rtype, 4)
        out[offset:offset + width] = b"\0" * width
    return bytes(out)


class Instance:
    """One function body in one archive member."""

    __slots__ = ("tag", "member", "symbol", "span", "relocs", "raw", "raw_relocs", "order")

    def __init__(self, tag, member, symbol, span, relocs, raw, raw_relocs, order):
        self.tag, self.member, self.symbol = tag, member, symbol
        self.span, self.relocs = span, relocs
        self.raw, self.raw_relocs = raw, raw_relocs
        self.order = order


CALLEE_MIN_SPAN = 8


def collect_instances(libs, warn):
    """(classes, callees) over every release span, in archive order.

    `classes` is {(size, canon): [Instance]} — the placement pool, which needs a
    body long enough to needle-search. `callees` is {(tag, symbol): [Instance]}
    over EVERY span including the short ones, because a 10-byte destructor is a
    perfectly good thing for a claimed body to call, and the call is the
    evidence.
    """
    MEMBER_CACHE.mkdir(parents=True, exist_ok=True)
    classes = defaultdict(list)
    callees = defaultdict(list)
    order = 0
    for tag, path in libs.items():
        if path.suffix.lower() == ".obj":
            members = [(path.name, path.read_bytes())]
        else:
            try:
                members = coffar.read_archive(path)
            except ValueError as exc:
                warn(f"{path.relative_to(ROOT)}: {exc}")
                continue
            names = Counter(name for name, _ in members)
            repeated = {name for name, count in names.items() if count > 1}
            if repeated:
                # extract_lib_members does dict(read_archive(...)), so only the
                # LAST member of a repeated name is ever unpacked. Claiming a
                # body out of the earlier one would name a member the gate
                # resolves to different bytes.
                warn(f"{path.relative_to(ROOT)}: member name(s) repeated in the archive "
                     f"({', '.join(sorted(repeated)[:3])}); every span in them is skipped "
                     "because the gate unpacks one member per name")
                members = [(n, b) for n, b in members if n not in repeated]
        for member_name, body in members:
            # An import library's members are short-import records, not COFF.
            # Handing one to a COFF reader means 65,535 bogus section headers
            # parsed before it throws, so the machine type decides first.
            if len(body) < 20 or body[0:2] != b"\x4c\x01":
                continue
            cached = MEMBER_CACHE / (tag + "_" + re.sub(r"[\\/]", "_", member_name))
            if not cached.exists() or cached.read_bytes() != body:
                cached.write_bytes(body)
            try:
                functions = list(locate.object_functions(cached))
            except Exception as exc:            # a non-COFF or truncated member
                warn(f"{path.name}({member_name}): unreadable as COFF ({exc})")
                continue
            for symbol, raw_span, raw_relocs in functions:
                raw = bytes(raw_span)
                span = raw.rstrip(b"\xcc")
                if len(span) < CALLEE_MIN_SPAN:
                    continue
                relocs = sorted((o, t, s) for o, t, s in raw_relocs if o < len(span))
                order += 1
                instance = Instance(
                    tag, member_name, symbol, span, relocs, raw,
                    sorted((o, t, s) for o, t, s in raw_relocs if o < len(raw)), order)
                callees[(tag, symbol)].append(instance)
                if len(span) >= MIN_SPAN:
                    classes[(len(span), canon(span, relocs))].append(instance)
    return classes, callees


# --------------------------------------------------------------------------
# placement
# --------------------------------------------------------------------------

def holes_of(relocs):
    return [(offset, coffar.RELOC_WIDTH.get(rtype, 4)) for offset, rtype, _ in relocs]


def masked_eq(body, span, relocs, upto=None):
    """True when body matches span everywhere outside a relocation slot."""
    length = len(span) if upto is None else upto
    if len(body) < length:
        return False
    covered = bytearray(length)
    for offset, width in holes_of(relocs):
        if offset >= length:
            continue
        covered[offset:offset + width] = b"\1" * min(width, length - offset)
    for index in range(length):
        if covered[index]:
            continue
        if index >= len(span) or body[index] != span[index]:
            return False
    return True


def concrete_bytes(relocs, size):
    """build.py's `concrete`: bytes of a masked comparison that prove anything."""
    covered = bytearray(size)
    for offset, rtype, _ in relocs:
        if offset >= size:
            continue
        width = min(coffar.RELOC_WIDTH.get(rtype, 4), size - offset)
        covered[offset:offset + width] = b"\1" * width
    return size - sum(covered)


def longest_needle(span, relocs, minimum):
    """The longest run of span with no relocation slot in it — the search key."""
    segments, position = [], 0
    for offset, width in sorted(holes_of(relocs)):
        if offset > position:
            segments.append((position, offset))
        position = max(position, offset + width)
    if position < len(span):
        segments.append((position, len(span)))
    segments = [s for s in segments if s[1] - s[0] >= minimum]
    return max(segments, key=lambda s: s[1] - s[0]) if segments else None


REL32 = 0x0014
JMP_REL32 = 0xE9
IMPORT_THUNK = b"\xff\x25"


def callee_verdict(rva, size, instance, callees, image, text_range, follow=True):
    """(corroborated, contradicted) over this placement's outgoing calls.

    The count-agreement standard decides WHICH of several identical bodies sits
    at an address purely by ordering. This decides it by what the body calls.
    Two masked-identical bodies differ exactly at their relocation slots, and
    retail has those slots RESOLVED: decode each REL32, and the archive says
    which function is supposed to be there. If the callee's own library body is
    not at that address, this pair is not the pair — the ordering premise put
    the wrong symbol on these bytes.

    A miss is only ever reported against a callee the archive itself defines,
    so an import, a data reference or a symbol from another library is silent
    rather than guessed at.
    """
    text_lo, text_hi = text_range
    corroborated, contradicted = 0, []
    for offset, rtype, name in instance.relocs:
        if rtype != REL32 or offset + 4 > size:
            continue
        candidates = callees.get((instance.tag, name))
        if not candidates:
            continue
        stored = image(rva + offset, 4)
        if len(stored) < 4:
            contradicted.append((offset, name, None))
            continue
        destination = rva + offset + 4 + int.from_bytes(stored, "little", signed=True)
        if not (text_lo <= destination < text_hi):
            contradicted.append((offset, name, destination))
            continue
        if any(masked_eq(image(destination, len(c.span)), c.span, c.relocs)
               for c in candidates):
            corroborated += 1
            continue
        body = image(destination, 6)
        # A `jmp dword ptr [__imp__x]` stub means the linker satisfied this
        # callee from a DLL and never pulled the archive's copy in. That is
        # evidence about the LINK, not about this placement, so it is silent.
        if len(body) >= 2 and body[0:2] == IMPORT_THUNK:
            continue
        # One hop through a `jmp rel32` veneer before calling it a miss.
        if follow and len(body) >= 5 and body[0] == JMP_REL32:
            hop = destination + 5 + int.from_bytes(body[1:5], "little", signed=True)
            if text_lo <= hop < text_hi and any(
                    masked_eq(image(hop, len(c.span)), c.span, c.relocs) for c in candidates):
                corroborated += 1
                continue
        contradicted.append((offset, name, destination))
    return corroborated, contradicted


HIT_CEILING = 64


def placements(window, instance):
    """Every RVA in the window where this body's masked bytes sit."""
    segment = (longest_needle(instance.span, instance.relocs, 8)
               or longest_needle(instance.span, instance.relocs, 4))
    if segment is None:
        return None
    lo, hi = segment
    needle = instance.span[lo:hi]
    size = len(instance.span)
    hits, start = [], 0
    while True:
        position = window.find(needle, start)
        if position < 0:
            break
        first = position - lo
        if 0 <= first <= len(window) - size and \
                masked_eq(window[first:first + size], instance.span, instance.relocs):
            hits.append(WIN_LO + first)
        start = position + 1
        if len(hits) > HIT_CEILING:
            break
    return hits


# --------------------------------------------------------------------------
# the sweep
# --------------------------------------------------------------------------

LEGAL_ORDER = ["dump-exact", "dump-padded", "pure-unclaimed", "dump-mismatch", "held-overlap"]


def sweep(report):
    ledger = Ledger()
    libs = archive_paths()
    tracked = tracked_sources()
    data, sections = B.exe_image()
    text = next(s for s in sections if s["name"] == ".text")
    base = text["raw_pointer"] - text["rva"]
    window = data[base + WIN_LO:base + WIN_HI]
    text_range = (text["rva"], text["rva"] + text["size"])

    def image(rva, count):
        return data[base + rva:base + rva + count]

    classes, callees = collect_instances(libs, report.warn)
    report.note(f"release spans: {sum(len(v) for v in classes.values()):,} in "
                f"{len(classes):,} masked-identity classes over {len(libs)} archives")

    # A byte the ledger already holds under a real row can never be re-claimed;
    # a byte a gen-dump holds can be superseded. Tracked as a lane so a class
    # that would claim ground an earlier class in THIS run already took is
    # refused rather than landed into an overlap the gate will reject.
    lane = bytearray(len(window))
    for row in ledger.rows:
        start = max(row["rva"], WIN_LO) - WIN_LO
        end = min(row["rva"] + row["size"], WIN_HI) - WIN_LO
        if start >= end:
            continue
        value = 1 if row["is_dump"] else 2
        for index in range(start, end):
            if lane[index] < value:
                lane[index] = value
    claimed = bytearray(len(window))

    results = []
    for key in sorted(classes, key=lambda k: (-k[0], k[1])):
        size = key[0]
        instances = classes[key]
        tags = {i.tag for i in instances}
        owner = next((t for t in ("d3dx9", "dxerr9", "vcomsupp") if t in tags),
                     sorted(tags)[0])
        source, window_key = LEDGER_SOURCE.get(owner, (None, "crt"))
        wlo, whi = WINDOWS[window_key]
        ordered = sorted((i for i in instances if i.tag == owner), key=lambda i: i.order)
        hits = placements(window, ordered[0])
        if hits is None:
            report.count("no-needle", size)
            continue
        if not hits:
            continue
        in_window = sorted(h for h in hits if wlo <= h < whi)
        if not in_window:
            continue
        # Supply is the OWNER's instance count, not the class's: only this
        # archive's members can have been linked into this archive's run, so
        # counting a libcmt twin as supply for a d3dx9-window hit would license
        # exactly the collision the standard exists to refuse.
        if len(in_window) > len(ordered):
            report.oversubscribed(size, len(in_window), len(ordered))
            continue

        # archive-order assignment over the FULL pairing, then drop the pairs
        # the ledger already owns. Pairing after the drop would slide every
        # later placement onto the wrong member.
        pairs = list(zip(in_window, ordered))

        # Every pair the ledger already holds is a test this class has to pass.
        # A class whose assignment contradicts an attached row is not a class
        # with one bad pair in it — the ordering premise failed there, so every
        # OTHER pair it produced is unevidenced too, and the whole class goes.
        # This is what caught the D3DXQUATERNION operators: inline COMDATs that
        # retail keeps both in their defining object's run and again in the
        # shared inline pool 200 KB later, which ascending-RVA order pairs the
        # wrong way round.
        anchors = 0
        contradicted = False
        for rva, instance in pairs:
            for row in ledger.consumed.get((source, instance.member, instance.symbol), ()):
                if row["rva"] == rva:
                    anchors += 1
                else:
                    contradicted = True
                    report.disagreement(source, instance.member, instance.symbol,
                                        row["rva"], rva)
        if contradicted:
            report.count("assignment-contradicts-ledger", size * len(pairs))
            continue
        report.witness(len(in_window), anchors)

        for rva, instance in pairs:
            if (source, instance.member, instance.symbol) in ledger.consumed:
                continue
            if rva in ledger.attached_rvas:
                report.count("rva-held-by-another-member", size)
                continue
            row = classify(rva, size, instance, ledger, lane, claimed,
                           image, source, owner, report, callees, text_range)
            if row is not None:
                row["placements"] = len(in_window)
                row["instances"] = len(ordered)
                row["anchors"] = anchors
                results.append(row)
    return results, ledger, tracked


def classify(rva, size, instance, ledger, lane, claimed, image, source, owner, report,
             callees, text_range):
    offset = rva - WIN_LO
    # The class was placed with its FIRST instance's relocation layout. Two
    # instances can canonicalise the same and still hole differently, so the
    # instance this address was actually assigned re-verifies here — a refusal
    # the sweep can explain beats a drop the gate has to.
    if not masked_eq(image(rva, size), instance.span, instance.relocs):
        report.count("assigned-instance-disagrees", size)
        return None
    corroborated, contradicted = callee_verdict(rva, size, instance, callees, image, text_range)
    if contradicted:
        report.callee_miss(rva, instance, contradicted)
        report.count("callee-target-contradicts", size)
        return None
    overlaps = ledger.overlapping(rva, size)
    dump = ledger.dump_at.get(rva)
    claim_size = size
    relocs = instance.relocs
    if not overlaps:
        legal = "pure-unclaimed"
    elif dump is not None and len(overlaps) == 1 and overlaps[0] is dump:
        if dump["size"] == size:
            legal = "dump-exact"
        elif dump["size"] <= len(instance.raw) and masked_eq(
                image(rva, dump["size"]), instance.raw, instance.raw_relocs, upto=dump["size"]):
            legal = "dump-padded"
            claim_size = dump["size"]
            relocs = instance.raw_relocs
        else:
            legal = "dump-mismatch"
    elif all(row["is_dump"] for row in overlaps):
        legal = "dump-mismatch"
    else:
        legal = "held-overlap"

    if legal in ("held-overlap", "dump-mismatch"):
        report.count(legal, claim_size)
        return None
    # Any overlap with a claim this run already made, not just a total one:
    # land_wave refuses a wave whose own rows straddle each other, and it
    # refuses the WHOLE wave, so a partial overlap emitted here costs every
    # other row in the batch.
    if any(claimed[i] for i in range(offset, offset + claim_size)):
        report.count("overlaps-earlier-claim-this-run", claim_size)
        return None
    new_bytes = sum(1 for i in range(offset, offset + claim_size) if lane[i] != 2)
    if new_bytes == 0:
        report.count("no-new-bytes", claim_size)
        return None
    concrete = concrete_bytes(relocs, claim_size)
    if concrete < B.MIN_LIB_CONCRETE:
        report.thin(rva, instance, claim_size, concrete)
        return None
    for i in range(offset, offset + claim_size):
        claimed[i] = 1
    return {"rva": rva, "size": claim_size, "new": new_bytes, "owner": owner,
            "source": source, "legal": legal, "symbol": instance.symbol,
            "member": instance.member, "tag": instance.tag,
            "dump_row": dump["name"] if dump else "", "concrete": concrete,
            "callees_ok": corroborated}


# --------------------------------------------------------------------------
# reporting
# --------------------------------------------------------------------------

class Report:
    def __init__(self):
        self.warnings, self.notes = [], []
        self.counts, self.bytes = Counter(), Counter()
        self.oversub = Counter()
        self.disagreements, self.thins = [], []
        # How much of the standard's weight each accepted class actually
        # carries: a class with one in-window placement needs no ordering
        # premise at all, and a class an attached row anchors has had it tested.
        self.classes = Counter()
        self.callee_misses = []

    def warn(self, text):
        self.warnings.append(text)

    def note(self, text):
        self.notes.append(text)
        print(text)

    def count(self, reason, size):
        self.counts[reason] += 1
        self.bytes[reason] += size

    def oversubscribed(self, size, hits, supply):
        self.oversub["classes"] += 1
        self.oversub["bytes"] += size * (hits - supply)
        self.count("oversubscribed", size * hits)

    def witness(self, in_window, anchors):
        if in_window == 1:
            self.classes["single placement (no ordering premise used)"] += 1
        elif anchors:
            self.classes["multi, ordering confirmed by an attached row"] += 1
        else:
            self.classes["multi, ordering unwitnessed"] += 1

    def callee_miss(self, rva, instance, contradicted):
        self.callee_misses.append((rva, instance.member, instance.symbol, contradicted))

    def disagreement(self, source, member, symbol, held_rva, assigned_rva):
        self.disagreements.append((source, member, symbol, held_rva, assigned_rva))

    def thin(self, rva, instance, size, concrete):
        self.thins.append((rva, instance.member, instance.symbol, size, concrete))
        self.count("thin-masked-comparison", size)


def print_report(rows, report):
    score, counts = Counter(), Counter()
    for row in rows:
        score[(row["owner"], row["legal"])] += row["new"]
        counts[(row["owner"], row["legal"])] += 1
    print("\n=== claimable placements, count-agreement standard ===")
    for key in sorted(score, key=lambda k: (k[0], LEGAL_ORDER.index(k[1]))):
        print(f"  {key[0]:<14} {key[1]:<15} {score[key]:>9,}B  {counts[key]:>5} rows")
    totals, row_totals = Counter(), Counter()
    for key, value in score.items():
        totals[key[1]] += value
        row_totals[key[1]] += counts[key]
    print()
    for legal in LEGAL_ORDER:
        if legal in totals:
            print(f"  TOTAL {legal:<15} {totals[legal]:>9,}B  {row_totals[legal]:>5} rows")
    print(f"  GRAND TOTAL {sum(totals.values()):,}B over {len(rows):,} rows")
    lone = [r for r in rows if r["placements"] == 1]
    anchored = [r for r in rows if r["placements"] > 1 and r["anchors"]]
    bare = [r for r in rows if r["placements"] > 1 and not r["anchors"]]
    print(f"  of which sole in-window placement of its body: {len(lone):,} rows, "
          f"{sum(r['new'] for r in lone):,}B")
    print(f"           multi-placement, an attached row anchors the order: "
          f"{len(anchored):,} rows, {sum(r['new'] for r in anchored):,}B")
    print(f"           multi-placement, order unwitnessed: {len(bare):,} rows, "
          f"{sum(r['new'] for r in bare):,}B")
    calls = [r for r in rows if r["callees_ok"]]
    print(f"  rows whose own calls land on the callee the archive names: {len(calls):,}, "
          f"{sum(r['new'] for r in calls):,}B")
    if report.classes:
        print("\n=== how much each accepted class leans on archive order ===")
        for label, count in sorted(report.classes.items()):
            print(f"  {label:<48} {count:>5} class(es)")
    if report.counts:
        print("\n=== refused ===")
        for reason, count in sorted(report.counts.items(), key=lambda kv: -kv[1]):
            print(f"  {reason:<28} {count:>6} placement(s)  {report.bytes[reason]:>10,}B")
    if report.oversub["classes"]:
        print(f"  oversubscribed classes: {report.oversub['classes']} "
              f"({report.oversub['bytes']:,}B of surplus retail copies)")
    for text in report.warnings:
        print(f"  WARN {text}")
    if report.disagreements:
        print("\n=== archive-order assignment DISAGREES with the ledger ===")
        for source, member, symbol, held, assigned in report.disagreements[:20]:
            print(f"  {member} {symbol[:60]}: ledger 0x{held:08X}, order-assignment "
                  f"0x{assigned:08X}")
        print(f"  {len(report.disagreements)} disagreement(s) — every one is a placement "
              "this standard would have got wrong, or a row that was.")
    else:
        print("\narchive-order assignment agrees with every attached row it re-derives")
    if report.callee_misses:
        print(f"\n=== {len(report.callee_misses)} placement(s) refused: a call goes somewhere "
              "the named callee is not ===")
        for rva, member, symbol, misses in report.callee_misses[:15]:
            offset, name, destination = misses[0]
            where = f"0x{destination:08X}" if destination is not None else "(truncated)"
            print(f"  0x{rva:08X} {member} {symbol[:46]}: +{offset} calls {where}, "
                  f"which is not {name[:46]}")
    if report.thins:
        print(f"\n{len(report.thins)} placement(s) dropped: fewer than "
              f"{B.MIN_LIB_CONCRETE} bytes outside a relocation slot")


# --------------------------------------------------------------------------
# emission
# --------------------------------------------------------------------------

def row_names(rows, ledger, tracked, report):
    """Assign each row a name unique in the wave AND in functions.csv.

    A symbol shared by two members is the common case here (the jpeg decoders
    d3dx9 links twice, the SSE float16 pair). The ledger cannot hold one name at
    two RVAs, so a twin gets `<symbol>$<member stem>` and an `object-symbol=`
    note pointing the gate back at the real COFF symbol — the shape the eight
    twins already in the ledger use.
    """
    occurrences = Counter(row["symbol"] for row in rows)
    used, named, refused = set(ledger.names), [], []
    for row in rows:
        if row["source"] is None or row["source"] not in tracked:
            refused.append((row, f"no tracked ledger source for archive tag {row['tag']}"))
            continue
        symbol = row["symbol"]
        alias = occurrences[symbol] > 1 or symbol in used
        name = symbol
        if alias:
            stem = re.sub(r"\.obj$", "", row["member"], flags=re.I)
            name = f"{symbol}${stem}"
        suffix = 1
        while name in used:
            suffix += 1
            stem = re.sub(r"\.obj$", "", row["member"], flags=re.I)
            name = f"{symbol}${stem}#{suffix}"
        if any(char in name for char in ',"\r\n'):
            refused.append((row, f"symbol carries a CSV-hostile character: {symbol!r}"))
            continue
        used.add(name)
        notes = f"vendored={vendor_tag(row['source'])};member={row['member']}"
        if name != symbol:
            notes += f";object-symbol={symbol}"
        named.append(dict(row, name=name, notes=notes))
    for row, reason in refused:
        report.warn(f"0x{row['rva']:08X} {row['symbol'][:60]}: {reason}")
    return named, refused


def vendor_tag(source):
    """The `vendored=` value a row on this archive carries."""
    stem = Path(source).stem
    return {"d3dx9": "d3dx9-summer2003", "dxerr9": "dxerr9-summer2003",
            "comsupp": "comsupp-vs2003"}.get(stem, f"{stem}-vs2003")


def write_wave(path, rows):
    with Path(path).open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, ["name", "rva", "size", "source", "notes"],
                                lineterminator="\n")
        writer.writeheader()
        for row in rows:
            writer.writerow({"name": row["name"], "rva": f"0x{row['rva']:08X}",
                             "size": row["size"], "source": row["source"],
                             "notes": row["notes"]})


def write_detail(path, rows):
    columns = ["rva", "size", "new", "owner", "legal", "tag", "member", "symbol",
               "dump_row", "concrete", "callees_ok", "placements", "instances", "anchors",
               "name", "notes", "source"]
    with Path(path).open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, columns, lineterminator="\n", extrasaction="ignore")
        writer.writeheader()
        for row in rows:
            writer.writerow(dict(row, rva=f"0x{row['rva']:08X}"))


def main(argv=None):
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--report", action="store_true", help="print the score table")
    parser.add_argument("--emit", help="write a land_wave CSV here")
    parser.add_argument("--detail", help="write the full per-placement CSV here")
    parser.add_argument("--legal", default="dump-exact,dump-padded,pure-unclaimed",
                        help="comma-separated legality classes to emit")
    parser.add_argument("--owner", help="restrict emission to one archive tag")
    parser.add_argument("--limit", type=int, help="emit at most this many rows")
    parser.add_argument("--offset", type=int, default=0, help="skip this many emittable rows")
    args = parser.parse_args(argv)

    report = Report()
    try:
        rows, ledger, tracked = sweep(report)
    except SweepError as exc:
        raise SystemExit(f"lib_window_sweep: {exc}")
    rows.sort(key=lambda row: row["rva"])
    named, refused = row_names(rows, ledger, tracked, report)
    if args.report or not (args.emit or args.detail):
        print_report(named, report)
    if args.detail:
        write_detail(args.detail, named)
        print(f"wrote {args.detail} ({len(named)} placement(s))")
    if args.emit:
        wanted = {c.strip() for c in args.legal.split(",") if c.strip()}
        unknown = wanted - set(LEGAL_ORDER)
        if unknown:
            raise SystemExit(f"lib_window_sweep: unknown legality class(es) "
                             f"{', '.join(sorted(unknown))}; known: {', '.join(LEGAL_ORDER)}")
        emit = [r for r in named if r["legal"] in wanted
                and (args.owner is None or r["owner"] == args.owner)]
        emit = emit[args.offset:]
        if args.limit is not None:
            emit = emit[:args.limit]
        if not emit:
            raise SystemExit("lib_window_sweep: no rows to emit under those filters — "
                             "nothing was written")
        write_wave(args.emit, emit)
        print(f"wrote {args.emit}: {len(emit)} row(s), {sum(r['size'] for r in emit):,}B "
              f"({Counter(r['legal'] for r in emit).most_common()})")
    if refused:
        print(f"\n{len(refused)} placement(s) refused emission — see WARN lines above",
              file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
