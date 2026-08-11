"""The naming harvester, and the invariants of what it publishes.

The mechanism these pin down is easy to get subtly wrong in a way that still
produces a plausible-looking file: resolving the callee through symbols.csv
instead of the retail bytes yields only names the project already had, and
stopping at the incremental-link thunk names the jump table rather than the
function. Both mistakes score zero new identity while looking like they worked.
"""
import csv
import importlib.util
import struct
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
ROOT = TOOLS.parent
RELOC_NAMES = ROOT / "reverse" / "reloc_names.csv"
REL32 = 0x0014


def _load(name):
    spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


sys.path.insert(0, str(TOOLS))
build = _load("build")


def call_row(caller_rva, callee_rva, opcode=0xE8, symbol="?callee@@YAXXZ"):
    """A byte-true row whose first instruction calls callee_rva."""
    displacement = struct.pack("<i", callee_rva - caller_rva - 5)
    return {"target_rva": caller_rva, "source": "Code/test.cpp",
            "target": bytes([opcode]) + displacement + b"\xc3",
            "relocs": [(1, REL32, symbol)]}


def a_thunked_function():
    """Return (body rva, one of its incremental-link thunk rvas)."""
    body, thunks = next(iter(build.build_call_thunks().items()))
    return body, thunks[0]


def a_publishable_function():
    """A thunked body that survives select_reloc_names' anonymous+unclaimed
    filters, so a test can exercise what the file actually publishes."""
    inventory = {int(row["rva"], 16): row["name"] for row in csv.DictReader(
        (ROOT / "reverse" / "ghidra_functions.csv").open(
            newline="", encoding="utf-8"))}
    claimed = {int(row["target_rva"], 16)
               for row in build.load_all_function_rows()}
    for body in build.build_call_thunks():
        if inventory.get(body, "").startswith("FUN_") and body not in claimed:
            return body
    raise AssertionError("no anonymous unclaimed thunked body in the image")


def test_callee_comes_from_the_retail_bytes():
    body, _ = a_thunked_function()
    caller = 0x1000
    named = build.harvest_reloc_names([call_row(caller, body)])
    assert named == {body: {"names": {"?callee@@YAXXZ"},
                            "sources": {"Code/test.cpp"}, "sites": 1}}, named
    print("PASS callee decoded from the displacement in the retail bytes")


def test_a_relocation_not_behind_a_call_is_ignored():
    """A REL32 fixup also sits behind `jmp` and inside data. Only the byte in
    front of the displacement says which, and reading the wrong ones would
    attach callee names to addresses nothing calls."""
    body, _ = a_thunked_function()
    assert build.harvest_reloc_names([call_row(0x1000, body, opcode=0xE9)]) == {}
    print("PASS relocation not preceded by 0xE8 is ignored")


def test_the_incremental_link_thunk_is_followed_to_the_body():
    """Call sites encode the thunk, not the function, for most of the image."""
    body, thunk = a_thunked_function()
    assert thunk != body
    named = build.harvest_reloc_names([call_row(0x1000, thunk)])
    assert list(named) == [body], (thunk, body, list(named))
    print(f"PASS thunk 0x{thunk:X} followed to body 0x{body:X}")


def test_two_names_for_one_address_are_dropped():
    """Identical-code folding gives one address several legitimate names. A row
    that kept one of them would be a coin flip the arity gate cannot see."""
    body, _ = a_thunked_function()
    rows = [call_row(0x1000, body, symbol="?one@@YAXXZ"),
            call_row(0x2000, body, symbol="?two@@YAXXZ")]
    named = build.harvest_reloc_names(rows)
    assert named[body]["names"] == {"?one@@YAXXZ", "?two@@YAXXZ"}
    assert build.select_reloc_names(named) == []
    print("PASS an address named two ways is dropped, not guessed at")


def test_a_generated_placeholder_name_is_marked_not_passed_off_as_identity():
    """Two thirds of the harvest names a class tools/gen_dump.py invented rather
    than one recovered from retail. The evidence is equally good; the name is
    worth nothing to a worker, so the row has to say which it is."""
    body = a_publishable_function()
    minted = build.select_reloc_names(build.harvest_reloc_names(
        [call_row(0x1000, body, symbol="??1Gen_dtor_0093e860@@UAE@XZ")]))
    recovered = build.select_reloc_names(build.harvest_reloc_names(
        [call_row(0x1000, body, symbol="?realName@SomeClass@@QAEXXZ")]))
    assert [row["notes"].endswith("identity=generated") for row in minted] == [True]
    assert [row["notes"].endswith("identity=real") for row in recovered] == [True]
    print("PASS a gen_dump-minted name is published marked, not as identity")


def test_published_rows_are_unambiguous_unclaimed_and_anonymous():
    with RELOC_NAMES.open(newline="", encoding="utf-8") as handle:
        reader = csv.DictReader(handle)
        assert "status" not in reader.fieldnames, (
            "a derived name file must not carry a status column: what is "
            "byte-verified here is the evidence, not the named body")
        rows = list(reader)
    inventory = {int(row["rva"], 16): row["name"] for row in csv.DictReader(
        (ROOT / "reverse" / "ghidra_functions.csv").open(newline="", encoding="utf-8"))}
    claimed = {int(row["target_rva"], 16) for row in build.load_all_function_rows()}

    seen = {}
    for row in rows:
        rva = int(row["target_rva"], 16)
        assert rva not in seen, f"0x{rva:X} published twice"
        assert rva not in claimed, f"0x{rva:X} is already claimed by the ledger"
        assert inventory.get(rva, "").startswith("FUN_"), (
            f"0x{rva:X} is not an anonymous function")
        assert int(row["target_size"]) > 0 and row["name"] and row["source"]
        seen[rva] = row["name"]
    print(f"PASS {len(rows)} published name(s) unambiguous, unclaimed, anonymous")
