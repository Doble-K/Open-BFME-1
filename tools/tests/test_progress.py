#!/usr/bin/env python3
"""Focused tests for tools/progress.py; stdlib only."""
import importlib.util
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TOOL = ROOT / "tools" / "progress.py"
COMMIT = "b08e5e856efced6d08c539153f5e229912f23b4f"

sys.path.insert(0, str(ROOT / "tools"))
spec = importlib.util.spec_from_file_location("progress", TOOL)
progress = importlib.util.module_from_spec(spec)
spec.loader.exec_module(progress)


def row(name, rva, size, source):
    return {(name, f"0x{rva:X}"): (size, source)}


def test_union_and_cpp_precedence():
    matched = {}
    matched.update(row("cpp-a", 0x1000, 10, "Code/a.cpp"))
    matched.update(row("cpp-b", 0x1005, 10, "Code/b.cpp"))
    matched.update(row("asm-overlap", 0x1008, 12, "Code/masm_dumps/a.asm"))
    matched.update(row("asm-only", 0x1030, 10, "Code/masm_dumps/b.asm"))
    stats = progress.coverage(matched, 0x1000, 100)
    assert stats == {
        "cpp": 15,
        "asm_only": 15,
        "unmatched": 70,
        "exact": 30,
        "text": 100,
    }, stats
    print("PASS interval union and C++ precedence")


def test_text_clipping():
    matched = {}
    matched.update(row("before", 0x0FF8, 12, "Code/a.cpp"))
    matched.update(row("after", 0x105E, 12, "Code/masm_dumps/a.asm"))
    stats = progress.coverage(matched, 0x1000, 100)
    assert stats["cpp"] == 4 and stats["asm_only"] == 6, stats
    assert stats["exact"] == 10 and stats["unmatched"] == 90, stats
    print("PASS .text boundary clipping")


def test_unknown_source_suffix_fails():
    matched = row("unknown", 0x1000, 10, "Code/generated/object.bin")
    try:
        progress.coverage(matched, 0x1000, 100)
    except SystemExit as exc:
        message = str(exc)
        assert "unsupported suffix .bin" in message and "object.bin" in message, message
    else:
        raise AssertionError("unknown matched-source suffix was counted as C++")
    print("PASS unknown matched-source suffix fails loudly")


def test_naked_cpp_to_clean_cpp_shifts_category_only():
    matched = row("?convert@Widget@@QAEXXZ", 0x1000, 3, "Code/convert.cpp")
    naked_text = """\
// ?convert@Widget@@QAEXXZ
__declspec(naked) void Widget::convert()
{
    __asm { __emit 0x8b __emit 0xc1 __emit 0xc3 }
}
"""
    naked_rows = progress.naked_cpp_rows(
        matched, {"Code/convert.cpp": naked_text},
        target_reader=lambda rva, size: bytes.fromhex("8b c1 c3"))
    assert naked_rows == set(matched), naked_rows

    before = progress.coverage(matched, 0x1000, 100, naked_rows)
    after = progress.coverage(matched, 0x1000, 100)
    assert before["asm_only"] == 3 and before["cpp"] == 0, before
    assert after["asm_only"] == 0 and after["cpp"] == 3, after
    assert before["exact"] == after["exact"] == 3
    assert before["unmatched"] == after["unmatched"] == 97
    print("PASS naked .cpp -> clean C++ shifts category but not exact coverage")


def test_bare_asm_emit_spray_is_asm_but_partial_emit_is_cpp():
    """A plain function whose __asm block emits the row's full retail bytes is
    a lift, not C++ (18 fleet commits smuggled these past the naked-only scan);
    a real body using the period _emit idiom for a few opcodes stays C++."""
    spray = row("?showBox@@YAXXZ", 0x1000, 8, "Code/spray.cpp")
    spray_text = """\
void showBox()
{
    __asm {
        __emit 0x8b;
        __emit 0xc1;
        call helper
        __emit 0x59;
        __emit 0xc3;
    }
}
"""
    found = progress.naked_cpp_rows(
        spray, {"Code/spray.cpp": spray_text},
        target_reader=lambda rva, size: bytes.fromhex("8bc1e800000000" + "59c3")[:size])
    assert found == set(spray), found

    idiom = row("?Init_CPU@@YAXXZ", 0x2000, 200, "Code/cpu.cpp")
    idiom_text = """\
void Init_CPU()
{
    int regs;
    __asm {
        mov eax, 1
        _emit 0x0f
        _emit 0xa2
        mov regs, eax
    }
}
"""
    found = progress.naked_cpp_rows(
        idiom, {"Code/cpu.cpp": idiom_text},
        target_reader=lambda rva, size: b"\x0f\xa2" + bytes(size - 2))
    assert found == set(), found
    print("PASS bare __asm emit spray is ASM; partial _emit idiom stays C++")


def test_mixed_file_marks_only_proven_naked_row():
    matched = {}
    matched.update(row("?raw@Widget@@QAEXXZ", 0x1000, 1, "Code/mixed.cpp"))
    matched.update(row("?clean@Widget@@QAEXXZ", 0x1010, 1, "Code/mixed.cpp"))
    text = """\
__declspec(naked) void Widget::raw() { __asm { ret } }
void Widget::clean() {}
"""
    found = progress.naked_cpp_rows(matched, {"Code/mixed.cpp": text})
    assert found == {("?raw@Widget@@QAEXXZ", "0x1000")}, found
    print("PASS mixed source classifies only signature-proven naked row")


def test_naked_body_callee_is_not_signature_evidence():
    matched = {}
    matched.update(row("?raw@Widget@@QAEXXZ", 0x1000, 1, "Code/wrapper.cpp"))
    matched.update(row("?clean@Widget@@QAEXXZ", 0x1010, 1, "Code/wrapper.cpp"))
    text = """\
__declspec(naked) void Widget::raw()
{
    __asm { call Widget::clean ret }
}
void Widget::clean() {}
"""
    found = progress.naked_cpp_rows(matched, {"Code/wrapper.cpp": text})
    assert found == {("?raw@Widget@@QAEXXZ", "0x1000")}, found
    print("PASS naked callee text cannot reclassify a clean row")


def test_naked_declaration_is_not_a_body():
    text = """\
__declspec(naked) void Widget::declared();
__declspec(naked) void Widget::defined() { __asm { ret } }
"""
    bodies = progress.scan_naked_bodies(text)
    assert len(bodies) == 1 and "Widget::defined" in bodies[0]["signature"], bodies
    print("PASS naked declarations are not counted as ASM bodies")


def test_signature_prefix_does_not_match_another_method():
    matched = {}
    matched.update(row("?raw@Widget@@QAEXXZ", 0x1000, 1, "Code/prefix.cpp"))
    matched.update(row("?rawHelper@Widget@@QAEXXZ", 0x1010, 1, "Code/prefix.cpp"))
    text = """\
void Widget::raw() {}
__declspec(naked) void Widget::rawHelper() { __asm { ret } }
"""
    found = progress.naked_cpp_rows(matched, {"Code/prefix.cpp": text})
    assert found == {("?rawHelper@Widget@@QAEXXZ", "0x1010")}, found
    print("PASS naked signature matching respects method boundaries")


def test_c_naked_signature_matches_decorated_row():
    matched = row("_GetPreviewFromMap", 0x1000, 1, "Code/free.cpp")
    text = "__declspec(naked) void *GetPreviewFromMap(void *, void *) { __asm { ret } }\n"
    found = progress.naked_cpp_rows(matched, {"Code/free.cpp": text})
    assert found == set(matched), found
    print("PASS C-linkage naked signature maps to its decorated row")


def test_live_naked_and_clean_rows_are_distinguished():
    """Every naked classification must point at a source that really contains a
    naked body, and clean rows must dominate.

    This used to pin two symbols by name, which rots by design: the project's
    goal is to convert every naked row, so any pinned naked symbol eventually
    becomes clean and the test breaks on progress (it died when the fleet
    converted ?construct@BFMENetworkBackend). Self-consistency over whatever
    is naked right now cannot rot, and an empty naked set is success."""
    matched = progress.matched_at("HEAD")
    naked = progress.naked_cpp_rows_at(matched, "HEAD")
    texts = progress.naked_source_texts(matched, "HEAD")
    for key in naked:
        source = matched[key][1]
        assert source in texts and (
            progress.NAKED_RE.search(texts[source])
            or progress.EMIT_RE.search(texts[source])), (
            f"{key} classified asm but {source} carries no naked or emit marker")
    clean = {key for key, (_, src) in matched.items()
             if src.endswith(".cpp")} - set(naked)
    assert len(clean) > len(naked), (len(clean), len(naked))
    print(f"PASS live ledger: {len(naked)} naked rows all self-consistent, "
          f"{len(clean)} clean")


def test_b08_is_zero_byte_progress():
    start, size = progress.retail_text()
    before_rows = progress.matched_at(f"{COMMIT}^")
    after_rows = progress.matched_at(COMMIT)
    before = progress.coverage(
        before_rows, start, size, progress.naked_cpp_rows_at(before_rows, f"{COMMIT}^"))
    after = progress.coverage(
        after_rows, start, size, progress.naked_cpp_rows_at(after_rows, COMMIT))
    assert before == after, (before, after)

    proc = subprocess.run(
        [sys.executable, str(TOOL), f"{COMMIT}^..{COMMIT}"],
        cwd=ROOT, capture_output=True, text=True, check=True)
    # Every delta the scorecard prints must be zero, on whichever views exist.
    # Pinning the line count instead broke the moment the real-code view added
    # six more of them, which is a report gaining detail, not progress moving.
    deltas = proc.stdout.count("delta ")
    assert deltas and proc.stdout.count("delta +0 bytes, +0.00 pp") == deltas, proc.stdout
    assert "matched rows" not in proc.stdout, proc.stdout
    print(f"PASS b08 reports zero byte progress on all {deltas} reported lanes")


def test_details_are_opt_in():
    plain = subprocess.run(
        [sys.executable, str(TOOL), f"{COMMIT}^..{COMMIT}"],
        cwd=ROOT, capture_output=True, text=True, check=True).stdout
    detailed = subprocess.run(
        [sys.executable, str(TOOL), "--details", f"{COMMIT}^..{COMMIT}"],
        cwd=ROOT, capture_output=True, text=True, check=True).stdout
    assert "ledger details" not in plain
    assert "ledger details" in detailed and "distinct RVAs" in detailed
    assert "ASM-backed rows:" in detailed and "ASM-bearing files:" in detailed
    print("PASS ledger diagnostics require --details")


def main():
    test_union_and_cpp_precedence()
    test_text_clipping()
    test_unknown_source_suffix_fails()
    test_naked_cpp_to_clean_cpp_shifts_category_only()
    test_bare_asm_emit_spray_is_asm_but_partial_emit_is_cpp()
    test_mixed_file_marks_only_proven_naked_row()
    test_naked_body_callee_is_not_signature_evidence()
    test_naked_declaration_is_not_a_body()
    test_signature_prefix_does_not_match_another_method()
    test_c_naked_signature_matches_decorated_row()
    test_live_naked_and_clean_rows_are_distinguished()
    test_b08_is_zero_byte_progress()
    test_details_are_opt_in()
    print("ALL TESTS PASSED")


if __name__ == "__main__":
    main()
