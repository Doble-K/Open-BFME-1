#!/usr/bin/env python3
"""Byte-true C++ for the MSVC unwind funclets retail left unclaimed.

Three funclet shapes carry both a frame displacement and a callee that can be
read straight out of the retail bytes, so an anonymous C++ body reproduces them
exactly:

  A  lea ecx,[ebp-D]; jmp <dtor>                       a local object
  B  lea ecx,[ebp+D]; jmp <dtor>                       a by-value class parameter
  C  mov eax,[ebp-D]; push eax; call <op delete>;      the block a throwing
     pop ecx; ret                                      new-expression allocated

The payloads are anonymous by design: they reproduce a frame slot and a call,
never a class identity, and every callee address comes from the retail bytes.

These funclets have no name of their own, so each ledger row is anchored to the
compiler-local `$L` label its body landed on.  Those numbers are assigned per
translation unit and shift whenever anything ahead of them changes, so this
generator OWNS `Code/gen_small/uw_gen_NNN.cpp` and every ledger row that cites
one: each run rewrites all of them and re-derives every label from a fresh
compile.  Hand-editing a landed file renumbers the labels and breaks rows whose
funclet is byte-for-byte untouched -- regenerate instead of editing, and let the
generator grow into a new file rather than appending to a landed one.

Unlike the 1,366 `gen-funclet` rows that sit on a reconstructed parent's object,
these funclets have no knowable parent: an `Unwind@`/`Catch@` name encodes the
funclet's own virtual address, and being unclaimed is what put them here.  Rows
therefore carry no `parent=` field, and nothing here guesses one from adjacency.

Usage:
  python3 tools/gen_uw.py classify   # measure the population; writes nothing
  python3 tools/gen_uw.py land       # regenerate every owned source and row
"""
import argparse
import bisect
import collections
import csv
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build      # noqa: E402
import harvest    # noqa: E402

FUNCTIONS = ROOT / "reverse" / "functions.csv"
SYMBOLS = ROOT / "reverse" / "symbols.csv"
DELETED = ROOT / "reverse" / "deleted_rows.csv"
GHIDRA = ROOT / "reverse" / "ghidra_functions.csv"
SOURCE_DIR = ROOT / "Code" / "gen_small"
OWNED_SOURCE_DIR = "Code/gen_small/uw_gen_"

# Everything the generator owns is recognised by these two markers alone.
ROW_NOTES = "gen-funclet;object-symbol="
OWNED_ROW_RE = re.compile((r",Code/gen_small/uw_gen_\d{3}\.cpp,matched,"
                           + re.escape(ROW_NOTES)).encode("utf-8"))
PIN_MARKER = "gen-uw-pin"
PIN_NOTE = PIN_MARKER + " dtor target read from the retail funclet bytes"
PIN_NOTE_BYTES = PIN_NOTE.encode("utf-8")

DELETE_NAME = "??3@YAXPAX@Z"
ROWS_PER_FILE = 1200


def source_name(index):
    return "Code/gen_small/uw_gen_%03d.cpp" % index


def rel32(body, offset, rva):
    return rva + offset + 5 + struct.unpack_from("<i", body, offset + 1)[0]


def disp8(value):
    return value - 256 if value > 127 else value


class Ledger:
    """The ledger rows and pins this generator does not own, plus the lookups
    that decide which funclets are still up for grabs.

    Everything owned is excluded from those lookups: a second run must see the
    same population as the first, and our own rows would otherwise mark their
    own funclets as claimed and their own pins as prior identity.
    """

    def __init__(self):
        self.claimed = {}          # rva -> name, from rows we do not own
        self.named = set()         # (name, address) pairs from rows we do not own
        self.addresses = set()     # byte-proved or explicitly pinned addresses
        self.pinned = set()        # addresses symbols.csv already carries a name for
        matched = []
        with FUNCTIONS.open(encoding="utf-8", errors="replace", newline="") as handle:
            for row in csv.DictReader(handle):
                if row["source"] and OWNED_SOURCE_DIR in row["source"]:
                    continue
                try:
                    rva = int(row["target_rva"], 16)
                    size = int(row["target_size"] or 0)
                except ValueError:
                    continue
                self.claimed[rva] = row["name"]
                if row["status"] == "matched":
                    matched.append((rva, rva + size))
                    self.addresses.add(rva)
                    self.named.add((row["name"], rva))
        with SYMBOLS.open(encoding="utf-8", errors="replace", newline="") as handle:
            for row in csv.DictReader(handle):
                if (row.get("notes") or "").startswith(PIN_MARKER):
                    continue
                try:
                    address = int(row["address"], 16)
                except ValueError:
                    continue
                self.addresses.add(address)
                self.pinned.add(address)
                self.named.add((row["name"], address))

        self.tombstoned = {}
        for line in DELETED.read_text(encoding="utf-8").splitlines():
            if line.startswith(("#", "name,")) or not line.strip():
                continue
            row = next(csv.reader([line]))
            if len(row) >= 2:
                self.tombstoned[(row[0], int(row[1], 16))] = row[2] if len(row) > 2 else ""

        self.merged = []
        for start, end in sorted(matched):
            if self.merged and start <= self.merged[-1][1]:
                self.merged[-1] = (self.merged[-1][0], max(self.merged[-1][1], end))
            else:
                self.merged.append((start, end))
        self.starts = [start for start, _ in self.merged]

    def overlaps(self, rva, size):
        """True when [rva, rva+size) touches any byte another matched row owns.

        Full containment is the common case, but a partial overlap would land a
        row check_csv rejects, so the weaker test is not enough.
        """
        index = bisect.bisect_right(self.starts, rva) - 1
        if index >= 0 and self.merged[index][1] > rva:
            return True
        return bisect.bisect_right(self.starts, rva + size - 1) - 1 > index

    def resolves(self, name, address):
        """True when the REL32 resolver would already reach `address` under
        `name` -- which is what a pin has to add, and is not the same question
        as whether the address carries some other name."""
        return (name, address) in self.named


Funclet = collections.namedtuple("Funclet", "kind rva size disp target")
Unit = collections.namedtuple("Unit", "kind target rows shape")


def read_funclets(ledger):
    """Every unclaimed named EH funclet, classified, with the ladder split out.

    Returns (on_ladder, off_ladder, tally, tally_bytes); the tallies count the
    whole population per class for the classify report.  A funclet is on the
    ladder when its displacement is a slot this generator can place in a frame.
    """
    data = build.EXE.read_bytes()
    on_ladder, off_ladder = [], []
    tally = collections.Counter()
    tally_bytes = collections.Counter()
    with GHIDRA.open(encoding="utf-8", newline="") as handle:
        for row in csv.DictReader(handle):
            if not row["name"].startswith(("Unwind@", "Catch@")):
                continue
            rva, size = int(row["rva"], 16), int(row["size"])
            if ledger.overlaps(rva, size):
                continue
            body = data[rva:rva + size]
            kind = target = disp = None
            if size == 8 and body[0] == 0x8D and body[1] == 0x4D and body[3] == 0xE9:
                disp = disp8(body[2])
                target = rel32(body, 3, rva)
                kind = "A" if disp < 0 else "B"
            elif (size == 11 and body[0] == 0x8B and body[1] == 0x45 and body[3] == 0x50
                    and body[4] == 0xE8 and body[9] == 0x59 and body[10] == 0xC3):
                disp = disp8(body[2])
                target = rel32(body, 4, rva)
                kind = "C"
            if kind is None:
                tally["D other"] += 1
                tally_bytes["D other"] += size
                continue
            label = "%s target-%s" % (kind, "known" if target in ledger.addresses else "UNKNOWN")
            tally[label] += 1
            tally_bytes[label] += size
            if target not in ledger.addresses:
                continue
            funclet = Funclet(kind, rva, size, disp, target)
            (on_ladder if on_the_ladder(funclet) else off_ladder).append(funclet)
    return on_ladder, off_ladder, tally, tally_bytes


def on_the_ladder(funclet):
    if funclet.kind == "B":
        return funclet.disp % 4 == 0 and funclet.disp >= 4
    return (-funclet.disp - 0x10) % 4 == 0 and funclet.disp <= -0x10


def slot_of(funclet):
    if funclet.kind == "B":
        return funclet.disp // 4 - 1
    return (-funclet.disp - 0x10) // 4


def plan(on_ladder):
    """Group the funclets into the units a translation unit is built from.

    A unit is one destructor target's locals and parameters, or the whole
    template-C population, which shares one set of new-expression frames.
    `shape` is what the emitter needs: (locals, parameters) for a type, the
    slots to reach for the new-expression unit.
    """
    locals_of = collections.defaultdict(set)
    params_of = collections.defaultdict(set)
    new_slots = set()
    for funclet in on_ladder:
        slot = slot_of(funclet)
        if funclet.kind == "A":
            locals_of[funclet.target].add(slot)
        elif funclet.kind == "B":
            params_of[funclet.target].add(slot)
        else:
            new_slots.add(slot)
    units = []
    for target in sorted(set(locals_of) | set(params_of)):
        rows = sum(1 for f in on_ladder if f.kind in "AB" and f.target == target)
        units.append(Unit("type", target, rows,
                          (max(locals_of[target]) + 1 if target in locals_of else 0,
                           max(params_of[target]) + 1 if target in params_of else 0)))
    if new_slots:
        rows = sum(1 for f in on_ladder if f.kind == "C")
        units.append(Unit("new", None, rows, tuple(sorted(new_slots))))
    files = [[]]
    count = 0
    for unit in units:
        if files[-1] and count + unit.rows > ROWS_PER_FILE:
            files.append([])
            count = 0
        files[-1].append(unit)
        count += unit.rows
    return files


HEADER = """\
// cl: /DNDEBUG /MD /EHsc
// Generated by: python3 tools/gen_uw.py land
// Do not edit by hand -- regenerate. Every row in this file is anchored to a
// compiler-local $L label, so inserting or removing anything renumbers the
// labels and breaks rows whose funclet bytes never changed.
//
// Each body exists to make MSVC emit one unwind funclet that retail also emits.
// The payloads are anonymous by design -- a frame slot and a destructor call,
// never a class identity -- and every callee address is read out of the retail
// funclet and pinned in reverse/symbols.csv, so the bytes prove the target.

void gen_uw_ext();
void gen_uw_sink(void *);
"""


def emit_source(units):
    out = [HEADER]
    types = [unit for unit in units if unit.kind == "type"]
    if types:
        out.append("\n".join("struct Gen_uw_%08x { int m; ~Gen_uw_%08x(); };" % (u.target, u.target)
                             for u in types) + "\n")
    for target, (locals_needed, params_needed) in ((u.target, u.shape) for u in types):
        if locals_needed:
            body = "\n".join("\tGen_uw_%08x v%d; gen_uw_ext();" % (target, i)
                             for i in range(locals_needed))
            out.append("void gen_uw_f_%08x()\n{\n%s\n}\n" % (target, body))
        if params_needed:
            args = ", ".join("Gen_uw_%08x a%d" % (target, i) for i in range(params_needed))
            out.append("void gen_uw_p%d_%08x(%s) { gen_uw_ext(); }\n"
                       % (params_needed, target, args))
    for unit in units:
        if unit.kind != "new":
            continue
        out.append("// A throwing new-expression leaves its block to be freed from a frame\n"
                   "// slot, and padding ahead of it walks that slot down the ladder. Slot 1\n"
                   "// is the exception: a 4-byte pad lands in the spare slot the frame\n"
                   "// already has and does not move the temporary, so only a second\n"
                   "// new-expression that is live at the same time reaches it.\n"
                   "struct Gen_uw_new { int m; Gen_uw_new(int); ~Gen_uw_new(); };\n"
                   "struct Gen_uw_new2 { int m; Gen_uw_new2(Gen_uw_new *); ~Gen_uw_new2(); };\n")
        for slot in unit.shape:
            if slot == 0:
                out.append("Gen_uw_new *gen_uw_c0() { return new Gen_uw_new(0); }\n")
            elif slot == 1:
                out.append("Gen_uw_new2 *gen_uw_c1()"
                           " { return new Gen_uw_new2(new Gen_uw_new(0)); }\n")
            else:
                out.append("Gen_uw_new *gen_uw_c%d()"
                           " { char p[%d]; gen_uw_sink(p); return new Gen_uw_new(0); }\n"
                           % (slot, 4 * slot))
    return "\n".join(out)


def compiled_slots(source):
    """Map every funclet the compiler emitted to its $L label.

    Key is what identifies a retail funclet: the shape, its frame displacement,
    and the callee.  The lowest-numbered label wins so the mapping does not move
    when an unrelated unit adds another copy of the same funclet.
    """
    obj = harvest.compile_obj(source, [])
    labels = sorted({s["name"] for s in build.read_object_symbols(obj.read_bytes())
                     if re.fullmatch(r"\$L\d+", s["name"])}, key=lambda n: int(n[2:]))
    slots = {}
    for label in labels:
        body, relocs = build.read_object_symbol_bytes(obj, label)
        calls = {offset: name for offset, rtype, name in relocs if rtype == 0x0014}
        if (len(body) >= 8 and body[0] == 0x8D and body[1] == 0x4D and body[3] == 0xE9
                and calls.get(4, "").startswith("??1Gen_uw_")):
            key = ("AB", disp8(body[2]), int(calls[4][len("??1Gen_uw_"):][:8], 16))
        elif (len(body) >= 11 and body[0] == 0x8B and body[1] == 0x45 and body[3] == 0x50
                and body[4] == 0xE8 and body[9] == 0x59 and body[10] == 0xC3
                and calls.get(5) == DELETE_NAME):
            key = ("C", disp8(body[2]), None)
        else:
            continue
        slots.setdefault(key, label)
    return slots


def key_of(funclet):
    if funclet.kind == "C":
        return ("C", funclet.disp, None)
    return ("AB", funclet.disp, funclet.target)


def rewrite_lines(path, owned, fresh, newline):
    """Replace the lines this generator owns, leaving every other byte alone.

    Splitting on b"\\n" and rejoining reproduces the file exactly, which matters:
    functions.csv carries three shapes of historical line-ending damage that a
    csv round-trip would silently normalise.
    """
    lines = path.read_bytes().split(b"\n")
    kept = [line for line in lines if not owned(line)]
    if kept and kept[-1] == b"":
        kept.pop()
    kept += [text.encode("utf-8") + newline for text in fresh]
    path.write_bytes(b"\n".join(kept) + b"\n")


def land():
    ledger = Ledger()
    on_ladder, off_ladder, _, _ = read_funclets(ledger)
    for funclet in on_ladder:
        if funclet.rva in ledger.claimed:
            raise SystemExit(
                "0x%08X is already claimed by %s -- a generated row would collide"
                % (funclet.rva, ledger.claimed[funclet.rva]))
        # A tombstone records a row that was retracted for cause. Emitting one
        # again is a decision a person has to make against the recorded reason
        # and fresh byte proof, so stop rather than resurrect it quietly.
        name = "uw_%08x" % funclet.rva
        if (name, funclet.rva) in ledger.tombstoned:
            raise SystemExit(
                "%s @ 0x%08X is tombstoned in reverse/deleted_rows.csv and this run would "
                "re-land it. Reason recorded: %s\nEither byte-prove the row and retire that "
                "tombstone in the same commit, or keep the tombstone and exclude the address."
                % (name, funclet.rva, ledger.tombstoned[(name, funclet.rva)]))
    print("on-ladder %d rows / %d B ; off-ladder skipped %d (%s)"
          % (len(on_ladder), sum(f.size for f in on_ladder), len(off_ladder),
             ", ".join("%s=%d" % kv for kv in
                       sorted(collections.Counter(f.kind for f in off_ladder).items()))))

    files = plan(on_ladder)
    by_key = collections.defaultdict(list)
    for funclet in on_ladder:
        by_key[key_of(funclet)].append(funclet)

    rows, targets, written = [], set(), []
    for index, units in enumerate(files):
        path = ROOT / source_name(index)
        path.write_text(emit_source(units), encoding="utf-8", newline="\n")
        slots = compiled_slots(path)
        unit_targets = {u.target for u in units if u.kind == "type"}
        targets |= unit_targets
        emits_new = any(u.kind == "new" for u in units)
        wanted = sorted(k for k in by_key if (k[0] == "AB" and k[2] in unit_targets)
                        or (k[0] == "C" and emits_new))
        missing = [k for k in wanted if k not in slots]
        if missing:
            raise SystemExit(
                "%s: the compiler emitted no funclet for %d needed slot(s), e.g. %s. "
                "Fix the emitted shape; a row must not be dropped silently."
                % (path.name, len(missing), missing[:8]))
        count = 0
        for key in wanted:
            for funclet in by_key[key]:
                rows.append(("uw_%08x" % funclet.rva, "", "0x%08X" % funclet.rva,
                             str(funclet.size), source_name(index), "matched",
                             ROW_NOTES + slots[key]))
                count += 1
        written.append(path)
        print("  %s: %d units, %d rows" % (path.name, len(units), count))

    for stale in sorted(SOURCE_DIR.glob("uw_gen_*.cpp")):
        if stale not in written:
            stale.unlink()
            print("  removed stale %s" % stale.name)

    # Every destructor target gets its own pin. The resolver matches a REL32
    # callee by NAME, so an address already pinned under some other name still
    # leaves ??1Gen_uw_* unresolvable -- filtering on the address would drop
    # exactly the pins the build needs.
    pins = [("??1Gen_uw_%08x@@QAE@XZ" % t, t) for t in sorted(targets)]
    pins += [(DELETE_NAME, f.target) for f in on_ladder
             if f.kind == "C" and not ledger.resolves(DELETE_NAME, f.target)]
    pins = sorted(set(pins), key=lambda pin: (pin[1], pin[0]))
    redundant = [pin for pin in pins if ledger.resolves(*pin)]
    if redundant:
        raise SystemExit("pin duplicates a row that already carries it: %s" % redundant[:4])

    rows.sort(key=lambda row: row[2])
    rewrite_lines(FUNCTIONS, OWNED_ROW_RE.search,
                  [",".join(row) for row in rows], b"\r")
    rewrite_lines(SYMBOLS, lambda line: line.startswith(b"?") and line.endswith(PIN_NOTE_BYTES),
                  ["%s,0x%08X,%s" % (name, address, PIN_NOTE) for name, address in pins], b"")
    print("landed %d rows across %d file(s); %d pins, %d of them at an address "
          "symbols.csv already names differently"
          % (len(rows), len(written), len(pins),
             sum(1 for _, address in pins if address in ledger.pinned)))


def classify():
    ledger = Ledger()
    on_ladder, off_ladder, tally, tally_bytes = read_funclets(ledger)
    print("=== unclaimed named-EH population by template ===")
    for label in sorted(tally):
        print("  %-22s %6d rows %8d B" % (label, tally[label], tally_bytes[label]))
    print("  %-22s %6d rows %8d B" % ("TOTAL", sum(tally.values()), sum(tally_bytes.values())))
    print("\non-ladder (what land emits): %d rows / %d B"
          % (len(on_ladder), sum(f.size for f in on_ladder)))
    for kind, count in sorted(collections.Counter(f.kind for f in on_ladder).items()):
        print("    %s %5d rows" % (kind, count))
    print("off-ladder (no frame slot this generator can place): %d rows / %d B  %s"
          % (len(off_ladder), sum(f.size for f in off_ladder),
             dict(sorted(collections.Counter(f.kind for f in off_ladder).items()))))
    targets = {f.target for f in on_ladder if f.kind in "AB"}
    print("distinct destructor targets: %d (%d already carry another name in symbols.csv, "
          "which a pin filtered on address would wrongly skip)"
          % (len(targets), sum(1 for t in targets if t in ledger.pinned)))
    print("template-C operator delete targets: %s"
          % sorted({hex(f.target) for f in on_ladder if f.kind == "C"}))
    print("plan: %d file(s) at <= %d rows each" % (len(plan(on_ladder)), ROWS_PER_FILE))


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("mode", choices=("classify", "land"))
    args = parser.parse_args()
    (classify if args.mode == "classify" else land)()


if __name__ == "__main__":
    main()
