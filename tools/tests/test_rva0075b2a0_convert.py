#!/usr/bin/env python3
"""Prove the 0x0075B2A0 float-getter conversion is clean C++ and byte-matches retail.

Drives tools/build.py on the shipped translation unit. Does not hard-code
retail bytes; the existing MSVC 7.1 gate is the oracle.
"""
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "Code" / "GameEngine" / "Source" / "Common" / "TinyFloatFieldGetters_75B2A0.cpp"
BUILD = ROOT / "tools" / "build.py"


def test_source_is_clean_cpp():
    text = SOURCE.read_text(encoding="utf-8")
    assert SOURCE.exists(), SOURCE
    for banned in ("__declspec(naked)", "__asm", "__emit"):
        assert banned not in text, f"{SOURCE} still contains {banned!r}"
    assert "BFME_FLOAT_FIELD_GETTER( Rva0075B2A0, 0x3A0 )" in text
    print("PASS clean C++ body (no naked/asm/emit)")


def test_build_py_matches_retail():
    text = SOURCE.read_text(encoding="utf-8")
    n = text.count("BFME_FLOAT_FIELD_GETTER( Rva")
    result = subprocess.run(
        [sys.executable, str(BUILD), str(SOURCE.relative_to(ROOT).as_posix())],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    output = result.stdout + result.stderr
    print(output)
    assert result.returncode == 0, output
    assert f"Functions: OK {n}/{n} matched" in output, output
    print("PASS build.py matches retail 0x0075B2A0")


if __name__ == "__main__":
    test_source_is_clean_cpp()
    test_build_py_matches_retail()
