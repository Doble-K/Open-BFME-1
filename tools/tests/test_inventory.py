"""Guards for reverse/ghidra_functions.csv, which nothing else validates.

check_csv covers functions.csv and symbols.csv only, so the inventory every
queue tool reads for sizes and anonymity has had no shape check at all. These
assert it directly, and that the call-derived starts landed in it stayed
derivable from the retail image rather than becoming a hand-maintained list.

The game-end closure baseline lives here too: `callers_of.py --closure` walks
that same inventory, and its per-tier figures may only move toward source and
identity.
"""
import csv
import importlib.util
import subprocess
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
ROOT = TOOLS.parent
INVENTORY = ROOT / "reverse" / "ghidra_functions.csv"
IMAGE_BASE = 0x400000


def _load(name):
    spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


sys.path.insert(0, str(TOOLS))
build = _load("build")


def test_inventory_rows_are_well_formed():
    with INVENTORY.open("r", encoding="utf-8", newline="") as handle:
        reader = csv.DictReader(handle)
        assert reader.fieldnames == ["rva", "size", "name"], reader.fieldnames
        rows = list(reader)
    sections = build.pe_sections(build.EXE.read_bytes())
    text = next(section for section in sections if section["name"] == ".text")
    low, high = text["rva"], text["rva"] + text["size"]

    previous = -1
    seen = set()
    for row in rows:
        rva = int(row["rva"], 16)
        size = int(row["size"])
        assert row["rva"] == f"0x{rva:X}", f"non-canonical rva {row['rva']!r}"
        assert size > 0, f"0x{rva:X}: {size}-byte function"
        assert low <= rva and rva + size <= high, f"0x{rva:X}+{size} leaves .text"
        assert rva not in seen, f"0x{rva:X} appears twice"
        assert rva > previous, f"0x{rva:X} is out of order"
        assert row["name"], f"0x{rva:X}: empty name"
        if row["name"].startswith("FUN_"):
            assert row["name"] == f"FUN_{rva + IMAGE_BASE:08x}", (
                f"0x{rva:X}: anonymous name {row['name']} does not spell its own "
                f"address, so it is not the placeholder it claims to be")
        seen.add(rva)
        previous = rva
    print(f"PASS inventory: {len(rows):,} rows well-formed, sorted and unique")


def test_a_jmp_leaving_text_is_not_an_incremental_link_thunk():
    """The bound on the displacement is what tells a thunk from a coincidence.

    0xA5E88E begins with 0xE9 and is not a thunk: it is the tail of a `mov`
    immediate inside a d3dx9 body, reached only because the linear decode read
    the 0xE8 of `89 65 e8` (mov [ebp-0x18], esp) as a call opcode. Following it
    unbounded yields RVA -0x2AD9506D, which is in no section at all, and that
    address passed every unknown/unclaimed filter and crashed the boundary scan.
    Junk targets are the decode working as designed; each one has to reach
    is_boundary to be rejected, so resolving one must never raise.
    """
    data, sections = build.exe_image()
    text = next(section for section in sections if section["name"] == ".text")
    low, high = text["rva"], text["rva"] + text["size"]

    assert data[build.rva_to_file_offset(sections, 0xA5E88E)] == 0xE9
    assert build.follow_thunk(data, sections, 0xA5E88E, low, high) == 0xA5E88E
    body, thunks = next(iter(build.build_call_thunks().items()))
    assert build.follow_thunk(data, sections, thunks[0], low, high) == body
    print("PASS a jmp whose displacement leaves .text stays its own address")


def test_call_derived_starts_stay_derivable():
    """Re-deriving must find nothing new: every start it can prove is landed.

    This is what stops the inventory drifting into a hand-edited list. A row
    deleted from it, or a predicate loosened into inventing starts, both show up
    here as a non-zero count.

    Ledger growth does not decay this. New byte-verified bodies contribute call
    sites, and the derivation is over the retail image, so a body landing can
    only ever prove a start that genuinely belongs in the inventory -- in which
    case the fix is to land it, not to relax the assertion.
    """
    proc = subprocess.run(
        [sys.executable, str(TOOLS / "new_starts.py")],
        cwd=ROOT, capture_output=True, text=True, check=False)
    assert proc.returncode == 0, (
        f"new_starts.py failed (rc {proc.returncode}) -- the derivation has to "
        f"survive every ledger state, junk call targets included:\n{proc.stderr}")
    assert "landing 0 row(s)" in proc.stdout, (
        "the retail image proves a function start the inventory does not have; "
        "run `python3 tools/new_starts.py --apply` and commit the inventory\n"
        + proc.stdout)
    print("PASS call-derived starts: re-derivation is idempotent")


CLOSURE_SEEDS = "reverse/game_end/seeds.json"
# `callers_of.py --closure` at the commit that introduced it, per (group, tier):
# (functions, bytes) in each ledger state and on each side of identity. The
# regressing columns may only fall and the improving ones only rise, so landing
# a conversion or a pin inside the game-end region is what moves a figure here,
# and a lost row or a broken thunk walk is what turns one red.
CLOSURE_BASELINE = {
    ("A_victory", 0): {
        "UNCLAIMED": (0, 0), "ASM": (8, 2732), "SMALL": (0, 0), "LIB": (0, 0),
        "CPP": (0, 0), "identified": (2, 1349), "anonymous": (6, 1383)},
    ("A_victory", 1): {
        "UNCLAIMED": (4, 5816), "ASM": (41, 14918), "SMALL": (4, 75), "LIB": (4, 119),
        "CPP": (13, 1156), "identified": (28, 10465), "anonymous": (38, 11619)},
    ("A_victory", 2): {
        "UNCLAIMED": (34, 23581), "ASM": (570, 157446), "SMALL": (45, 3570), "LIB": (15, 682),
        "CPP": (149, 13373), "identified": (232, 51543), "anonymous": (581, 147109)},
    ("B_script", 0): {
        "UNCLAIMED": (0, 0), "ASM": (1, 290), "SMALL": (0, 0), "LIB": (0, 0),
        "CPP": (4, 19630), "identified": (5, 19920), "anonymous": (0, 0)},
    ("B_script", 1): {
        "UNCLAIMED": (0, 0), "ASM": (5, 39960), "SMALL": (0, 0), "LIB": (1, 59),
        "CPP": (0, 0), "identified": (2, 39659), "anonymous": (4, 360)},
    ("B_script", 2): {
        "UNCLAIMED": (0, 0), "ASM": (7, 569), "SMALL": (0, 0), "LIB": (0, 0),
        "CPP": (4, 240), "identified": (3, 183), "anonymous": (8, 626)},
    ("C_results", 0): {
        "UNCLAIMED": (3, 10871), "ASM": (16, 16084), "SMALL": (0, 0), "LIB": (0, 0),
        "CPP": (6, 6151), "identified": (9, 11974), "anonymous": (16, 21132)},
    ("C_results", 1): {
        "UNCLAIMED": (3, 5314), "ASM": (100, 32295), "SMALL": (7, 483), "LIB": (9, 710),
        "CPP": (54, 13330), "identified": (84, 26731), "anonymous": (89, 25401)},
    ("C_results", 2): {
        "UNCLAIMED": (11, 16462), "ASM": (241, 71021), "SMALL": (36, 3830), "LIB": (8, 466),
        "CPP": (101, 15499), "identified": (177, 44811), "anonymous": (220, 62467)},
    ("D_desync", 0): {
        "UNCLAIMED": (0, 0), "ASM": (2, 861), "SMALL": (0, 0), "LIB": (0, 0),
        "CPP": (0, 0), "identified": (1, 501), "anonymous": (1, 360)},
    ("D_desync", 1): {
        "UNCLAIMED": (0, 0), "ASM": (10, 2683), "SMALL": (1, 8), "LIB": (0, 0),
        "CPP": (1, 13), "identified": (2, 1972), "anonymous": (10, 732)},
    ("D_desync", 2): {
        "UNCLAIMED": (0, 0), "ASM": (29, 2673), "SMALL": (10, 1074), "LIB": (0, 0),
        "CPP": (3, 362), "identified": (7, 949), "anonymous": (35, 3160)},
    ("E_leave", 0): {
        "UNCLAIMED": (0, 0), "ASM": (38, 11957), "SMALL": (0, 0), "LIB": (0, 0),
        "CPP": (5, 463), "identified": (25, 8200), "anonymous": (18, 4220)},
    ("E_leave", 1): {
        "UNCLAIMED": (0, 0), "ASM": (105, 16034), "SMALL": (4, 122), "LIB": (0, 0),
        "CPP": (86, 6128), "identified": (124, 16090), "anonymous": (71, 6194)},
    ("E_leave", 2): {
        "UNCLAIMED": (6, 2145), "ASM": (115, 28567), "SMALL": (19, 2703), "LIB": (4, 2711),
        "CPP": (198, 15436), "identified": (255, 40938), "anonymous": (87, 10624)},
    ("F_engine_quit", 0): {
        "UNCLAIMED": (0, 0), "ASM": (6, 13470), "SMALL": (0, 0), "LIB": (0, 0),
        "CPP": (0, 0), "identified": (3, 12059), "anonymous": (3, 1411)},
    ("F_engine_quit", 1): {
        "UNCLAIMED": (17, 7410), "ASM": (117, 30410), "SMALL": (1, 3), "LIB": (3, 106),
        "CPP": (32, 1926), "identified": (50, 14662), "anonymous": (120, 25193)},
}
REGRESSING = ("UNCLAIMED", "ASM", "SMALL", "anonymous")
IMPROVING = ("CPP", "identified")


def _closure_table(stdout):
    lines = stdout.splitlines()
    columns = lines[0].split()[4:]
    table = {}
    for line in lines[1:]:
        fields = line.split()
        if fields[0] != "TOTAL":
            table[(fields[0], int(fields[1]))] = {
                column: tuple(int(v) for v in cell.split("/"))
                for column, cell in zip(columns, fields[4:])}
    return table


def test_game_end_closure_coverage_never_regresses():
    proc = subprocess.run(
        [sys.executable, str(TOOLS / "callers_of.py"), "--closure", CLOSURE_SEEDS],
        cwd=ROOT, capture_output=True, text=True, check=False)
    assert proc.returncode == 0, (
        f"callers_of.py --closure failed (rc {proc.returncode}):\n{proc.stderr}")
    table = _closure_table(proc.stdout)
    zero = {column: (0, 0) for column in REGRESSING + IMPROVING}
    moved = []
    for key in sorted(set(CLOSURE_BASELINE) | set(table)):
        base = CLOSURE_BASELINE.get(key, zero)
        now = table.get(key, zero)
        for column in REGRESSING:
            if now[column][0] > base[column][0] or now[column][1] > base[column][1]:
                moved.append(f"{key}: {column} rose to {now[column]} from {base[column]}")
        for column in IMPROVING:
            if now[column][0] < base[column][0] or now[column][1] < base[column][1]:
                moved.append(f"{key}: {column} fell to {now[column]} from {base[column]}")
    assert not moved, "\n".join(moved) + "\n\n" + proc.stdout
    print("PASS game-end closure: no state or identity figure moved the wrong way")
