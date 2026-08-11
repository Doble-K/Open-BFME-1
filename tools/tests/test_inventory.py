"""Guards for reverse/ghidra_functions.csv, which nothing else validates.

check_csv covers functions.csv and symbols.csv only, so the inventory every
queue tool reads for sizes and anonymity has had no shape check at all. These
assert it directly, and that the call-derived starts landed in it stayed
derivable from the retail image rather than becoming a hand-maintained list.
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
