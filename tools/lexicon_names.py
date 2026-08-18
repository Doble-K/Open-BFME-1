#!/usr/bin/env python3
"""Name menu and gadget callbacks from the tables retail wires them up with.

BFME's .wnd screens name their callbacks as strings, and the engine turns a
string into a function pointer through fixed tables in .data: three dwords per
entry -- `const char *name`, the function, and a zero -- the shape ZH spells as
FunctionLexicon::TableEntry. The binary is therefore carrying the real name of
every window init/update/shutdown/input/system callback in the image, and of
every INI block parser wired the same way.

That is identity of a different kind from every other anchor here. locate.py,
reloc_names.csv and the ZH sweep all argue from bytes, so they go quiet exactly
where a body has drifted; a string literal (tools/string_anchors.py) names the
*compiland* and leaves the function to be guessed from it. A table entry names
the function outright, whatever its bytes look like, because that is what the
loader reads at run time.

    python3 tools/lexicon_names.py [--all] [--csv reverse/lexicon_names.csv]

Default output is the unclaimed ones: entries whose function no real-C++ ledger
row covers. The name is not a decorated symbol -- these are `extern "C"`-style
C++ free functions, so `Foo` in the table is `?Foo@@YAXPAVWindowLayout@@PAX@Z`
or whatever its real signature decorates to, which the disassembly still has to
settle. Verify with tools/add_match.py, which reverts on failure.
"""
import argparse
import bisect
import csv
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import build  # noqa: E402

IMAGE_BASE = 0x400000
LEDGER = 'reverse/functions.csv'


def image():
    data, _ = build.exe_image()
    return data, build.pe_sections(data)


def reader(data, sections):
    def read(rva, size):
        offset = build.rva_to_file_offset(sections, rva)
        return data[offset:offset + size]
    return read


def section_of(sections, rva):
    for section in sections:
        if section['rva'] <= rva < section['rva'] + section['size']:
            return section['name']
    return None


def cstring(read, sections, va, limit=160):
    """The printable C string at a virtual address, or None."""
    rva = va - IMAGE_BASE
    if section_of(sections, rva) not in ('.rdata', '.data'):
        return None
    raw = read(rva, limit).split(b'\0')[0]
    if len(raw) < 3 or not all(32 <= byte < 127 for byte in raw):
        return None
    text = raw.decode()
    return text if text[0].isalpha() else None


def follow_thunk(read, rva):
    """Past an incremental-link `jmp body` thunk to the body itself."""
    head = read(rva, 5)
    if len(head) == 5 and head[0] == 0xE9:
        return rva + 5 + struct.unpack('<i', head[1:5])[0]
    return rva


def ledger_index():
    rows = []
    with open(LEDGER, newline='') as handle:
        for row in csv.DictReader(handle):
            try:
                rva, size = int(row['target_rva'], 16), int(row['target_size'])
            except (ValueError, KeyError):
                continue
            rows.append((rva, size, row['name'], row['source']))
    rows.sort()
    return rows, [row[0] for row in rows]


def owner(rows, starts, rva):
    index = bisect.bisect_right(starts, rva) - 1
    while index >= 0 and rva - rows[index][0] < 0x10000:
        start, size, name, source = rows[index]
        if start <= rva < start + size:
            return rows[index]
        index -= 1
    return None


def entries(read, sections, text_lo, text_hi):
    """Every (table address, name, body rva) triple in .data, in table order."""
    found = []
    for section in sections:
        if section['name'] != '.data':
            continue
        base, size = section['rva'], section['size']
        blob = read(base, size)
        offset = 0
        while offset + 12 <= len(blob):
            name_va, func_va, zero = struct.unpack('<III', blob[offset:offset + 12])
            if zero == 0 and text_lo <= func_va - IMAGE_BASE < text_hi:
                name = cstring(read, sections, name_va)
                if name:
                    found.append((base + offset, name,
                                  follow_thunk(read, func_va - IMAGE_BASE)))
                    offset += 12
                    continue
            offset += 4
    return found


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument('--all', action='store_true',
                        help='include entries a real C++ row already covers')
    parser.add_argument('--csv', help='write the worklist here as CSV')
    args = parser.parse_args()

    data, sections = image()
    read = reader(data, sections)
    text = [s for s in sections if s['name'] == '.text'][0]
    rows, starts = ledger_index()

    out = []
    for table, name, body in entries(read, sections, text['rva'],
                                     text['rva'] + text['size']):
        held = owner(rows, starts, body)
        claimed = held is not None and 'gen_' not in held[3]
        if claimed and not args.all:
            continue
        out.append({
            'table_va': f'0x{table + IMAGE_BASE:08X}',
            'target_rva': f'0x{body:08X}',
            'lexicon_name': name,
            'size': '' if held is None else str(held[1]),
            'current_row': '' if held is None else held[2],
            'status': 'claimed' if claimed else 'unclaimed',
        })

    if args.csv:
        with open(args.csv, 'w', newline='') as handle:
            writer = csv.DictWriter(handle, fieldnames=list(out[0].keys()))
            writer.writeheader()
            writer.writerows(out)
        print(f'lexicon_names: {len(out)} row(s) -> {args.csv}')
        return 0

    for row in out:
        print(f"{row['target_rva']} {row['size'].rjust(5)}B  "
              f"{row['lexicon_name']:46} {row['current_row']}")
    print(f'lexicon_names: {len(out)} entr(ies)')
    return 0


if __name__ == '__main__':
    sys.exit(main())
