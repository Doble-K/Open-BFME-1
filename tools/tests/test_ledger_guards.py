"""Guards against the two ways a union-merged ledger corrupts itself silently.

Both of these actually happened while merging PR #67, and neither was caught by
anything: dedup_csv picked a source that no longer defined the symbol, and a
merge from a stale branch put a proven-wrong row back on master.
"""
import csv
import importlib.util
import io
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
HEADER = "name,export_rva,target_rva,target_size,source,status,notes"


def _load(name):
    spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


dedup_csv = _load("dedup_csv")
check_csv = _load("check_csv")


def _write(path, *rows):
    path.write_text(HEADER + "\r\n" + "".join(r + "\r\n" for r in rows), encoding="utf-8")


FIND_FIELD_PARSE = "?findFieldParse@@YAP6AXPAVINI@@PAX1PBX@ZPBUFieldParse@@PBDAAHAAPBX@Z"


def test_dedup_refuses_when_one_row_is_claimed_by_two_sources(tmp_path):
    """The findFieldParse bug: lexical tiebreak picked ini.cpp, which no longer
    defines it, and the full gate died with 'symbol not found in object'."""
    ledger = tmp_path / "functions.csv"
    _write(ledger,
           f"{FIND_FIELD_PARSE},,0x00850880,128,Code/GameEngine/Source/Common/INI/ini.cpp,matched,",
           f"{FIND_FIELD_PARSE},,0x00850880,128,Code/GameEngine/Source/Common/INI/ini_parsers.cpp,matched,moved to the parser TU")
    before = ledger.read_bytes()

    with pytest.raises(SystemExit) as exc:
        dedup_csv.dedup_functions(ledger)

    assert exc.value.code == 1
    assert ledger.read_bytes() == before, "must not rewrite the ledger when it cannot decide"


def test_dedup_still_collapses_true_duplicates(tmp_path):
    """Same source twice is the ordinary union-merge case and must still collapse."""
    ledger = tmp_path / "functions.csv"
    src = "Code/GameEngine/Source/Common/INI/ini_parsers.cpp"
    _write(ledger,
           f"{FIND_FIELD_PARSE},,0x00850880,128,{src},matched,",
           f"{FIND_FIELD_PARSE},,0x00850880,128,{src},matched,moved to the parser TU")

    before, after = dedup_csv.dedup_functions(ledger)

    assert (before, after) == (2, 1)
    kept = list(csv.DictReader(io.StringIO(ledger.read_text(encoding="utf-8"))))
    assert kept[0]["source"] == src
    assert kept[0]["notes"] == "moved to the parser TU", "keep the more informative row"


def test_icf_alias_group_survives_dedup(tmp_path):
    """Distinct names at one address are folded COMDATs, not a conflict."""
    ledger = tmp_path / "functions.csv"
    src = "Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp"
    _write(ledger,
           f"?removeAllTerrainBibs@BaseHeightMapRenderObjClass@@QAEXXZ,,0x006CB050,31,{src},matched,",
           f"?setShoreLineDetail@BaseHeightMapRenderObjClass@@QAEXXZ,,0x006CB050,31,{src},matched,")

    before, after = dedup_csv.dedup_functions(ledger)

    assert (before, after) == (2, 2)


def test_check_csv_flags_a_resurrected_row(tmp_path, monkeypatch):
    """A branch that forked before a delete re-adds the row with no conflict,
    because git's union driver cannot express a deletion."""
    monkeypatch.setattr(check_csv, "DELETED", tmp_path / "deleted_rows.csv")
    check_csv.DELETED.write_text(
        "name,target_rva,reason\n"
        "# comment line must be ignored\n"
        "??0BehaviorModule@@QAE@PAVThing@@PBVModuleData@@@Z,0x00121F60,vtable base disagrees with ten other TUs\n",
        encoding="utf-8")
    src = "Code/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdate.cpp"
    raw = (HEADER + "\r\n"
           + f"??0BehaviorModule@@QAE@PAVThing@@PBVModuleData@@@Z,,0x00121F60,46,{src},matched,\r\n"
           ).encode("utf-8")

    problems = []
    check_csv.check_functions(raw, problems, {src})

    assert any("come back" in p for p in problems), problems
    assert any("vtable base disagrees" in p for p in problems), "must say why it was deleted"


def test_check_csv_allows_rows_that_are_not_tombstoned(tmp_path, monkeypatch):
    monkeypatch.setattr(check_csv, "DELETED", tmp_path / "deleted_rows.csv")
    check_csv.DELETED.write_text(
        "name,target_rva,reason\n"
        "??0BehaviorModule@@QAE@PAVThing@@PBVModuleData@@@Z,0x00121F60,proven wrong\n",
        encoding="utf-8")
    src = "Code/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdate.cpp"
    # same name, DIFFERENT address -> not the tombstoned row
    raw = (HEADER + "\r\n"
           + f"??0BehaviorModule@@QAE@PAVThing@@PBVModuleData@@@Z,,0x00999000,46,{src},matched,\r\n"
           ).encode("utf-8")

    problems = []
    check_csv.check_functions(raw, problems, {src})

    assert not any("come back" in p for p in problems), problems


def test_shipped_tombstone_file_parses():
    """The real reverse/deleted_rows.csv must load, or the guard is silently off."""
    entries = check_csv.tombstones()
    assert entries, "reverse/deleted_rows.csv produced no entries"
    assert all(isinstance(rva, int) and reason for (_, rva), reason in entries.items()), entries
