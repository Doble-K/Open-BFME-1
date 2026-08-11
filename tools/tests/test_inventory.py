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


def test_call_derived_starts_stay_derivable():
    """Re-deriving must find nothing new: every start it can prove is landed.

    This is what stops the inventory drifting into a hand-edited list. A row
    deleted from it, or a predicate loosened into inventing starts, both show up
    here as a non-zero count.
    """
    proc = subprocess.run(
        [sys.executable, str(TOOLS / "new_starts.py")],
        cwd=ROOT, capture_output=True, text=True, check=True)
    assert "landing 0 row(s)" in proc.stdout, proc.stdout
    print("PASS call-derived starts: re-derivation is idempotent")
