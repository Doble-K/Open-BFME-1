#!/usr/bin/env python3
"""Name the DLL import behind an IAT slot, or list every import in the image.

Retail calls imports indirectly -- `call dword ptr [0x01358CCC]` -- and that
absolute address is a DIR32 slot, which build.py fills in from the target. So a
call through an import verifies byte-for-byte no matter which import our source
names: CloseHandle, GlobalFree and LocalFree all "match" equally. The bytes
cannot settle it and the import table has to.

That is not a hypothetical. File::~File was recorded as calling "some __stdcall
deallocator" on the word at File+0x10 -- the only thing its bytes proved was the
calling convention, since retail never adjusts esp after it. The table says
KERNEL32!CloseHandle, which makes that word an OS file handle rather than an
owned buffer.

Usage:
  python3 tools/resolve_import.py 0x01358CCC [0x...]   # name specific slots
  python3 tools/resolve_import.py --list [--dll KERNEL32]
"""
import argparse
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build as B

IMAGE_BASE = 0x00400000


def iter_imports(data, secs):
    """Yield (iat_va, dll, symbol) for every imported function."""
    def off(rva):
        for s in secs:
            if s["rva"] <= rva < s["rva"] + max(s["size"], 1):
                return s["raw_pointer"] + (rva - s["rva"])
        return None

    pe = struct.unpack("<I", data[0x3C:0x40])[0]
    magic = struct.unpack("<H", data[pe + 0x18:pe + 0x1A])[0]
    ddir = pe + 0x18 + (0x60 if magic == 0x10B else 0x70)
    imp_rva = struct.unpack("<I", data[ddir + 8:ddir + 12])[0]
    if not imp_rva:
        return

    i = off(imp_rva)
    while True:
        oft, _tds, _fwd, name, fthunk = struct.unpack("<IIIII", data[i:i + 20])
        if name == 0:
            break
        no = off(name)
        dll = data[no:no + 64].split(b"\x00")[0].decode() if no else "?"
        thunk_off = off(fthunk)
        names_off = off(oft) if oft else thunk_off
        k = 0
        while thunk_off is not None:
            v = struct.unpack("<I", data[thunk_off + k * 4:thunk_off + k * 4 + 4])[0]
            if v == 0:
                break
            hint = struct.unpack("<I", data[names_off + k * 4:names_off + k * 4 + 4])[0]
            if hint & 0x80000000:
                sym = f"ordinal {hint & 0xFFFF}"
            else:
                h = off(hint)
                sym = data[h + 2:h + 66].split(b"\x00")[0].decode() if h else "?"
            yield IMAGE_BASE + fthunk + k * 4, dll, sym
            k += 1
        i += 20


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("slots", nargs="*", help="IAT virtual addresses, hex (0x...)")
    ap.add_argument("--list", action="store_true", help="list every import")
    ap.add_argument("--dll", help="with --list, only this DLL (case-insensitive)")
    args = ap.parse_args()

    data = open(B.EXE, "rb").read()
    secs = B.pe_sections(data)
    table = {va: (dll, sym) for va, dll, sym in iter_imports(data, secs)}

    if args.list:
        for va in sorted(table):
            dll, sym = table[va]
            if args.dll and args.dll.lower() not in dll.lower():
                continue
            print(f"  0x{va:08X}  {dll}!{sym}")
        return

    if not args.slots:
        ap.error("give one or more IAT addresses, or --list")

    missing = 0
    for s in args.slots:
        va = int(s, 16)
        hit = table.get(va)
        if hit:
            print(f"  0x{va:08X} -> {hit[0]}!{hit[1]}")
        else:
            print(f"  0x{va:08X} -> not an import thunk slot")
            missing += 1
    if missing:
        raise SystemExit(1)


if __name__ == "__main__":
    main()
