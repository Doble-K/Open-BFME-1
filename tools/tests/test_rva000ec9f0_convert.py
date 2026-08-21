#!/usr/bin/env python3
"""Prove the 0x000EC9F0 float-getter conversion is clean C++ and byte-matches retail.

Drives tools/build.py on the shipped translation unit. Does not hard-code
retail bytes; the existing MSVC 7.1 gate is the oracle.
"""
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "Code" / "GameEngine" / "Source" / "Common" / "TinyFloatFieldGetters_EC9F0.cpp"
BUILD = ROOT / "tools" / "build.py"


def test_source_is_clean_cpp():
    text = SOURCE.read_text(encoding="utf-8")
    assert SOURCE.exists(), SOURCE
    for banned in ("__declspec(naked)", "__asm", "__emit"):
        assert banned not in text, f"{SOURCE} still contains {banned!r}"
    assert "float Rva000EC9F0::get()" in text
    print("PASS clean C++ body (no naked/asm/emit)")


def test_build_py_matches_retail():
    result = subprocess.run(
        [sys.executable, str(BUILD), str(SOURCE.relative_to(ROOT).as_posix())],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    output = result.stdout + result.stderr
    print(output)
    assert result.returncode == 0, output
    assert "Functions: OK" in output, output
    assert "?get@Rva000EC9F0@@QAEMXZ" in output, output
    print("PASS build.py matches retail 0x000EC9F0")


if __name__ == "__main__":
    test_source_is_clean_cpp()
    test_build_py_matches_retail()
