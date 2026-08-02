#!/usr/bin/env python3
"""Decode BFME's entire INI schema -- every block, field, type and struct offset.

Retail registers each INI block in a singly-linked list whose head is the global
at 0x0130CE50. INI::findBlockParse walks it comparing the keyword. The nodes are
statically allocated, so the registration constructor that MSVC inlined at each
site only has to link them in; the keyword and function pointer are already sat
in .data. That means the whole registry can be read without decoding any code:
find each `mov [0x0130CE50], <node>` and read the node.

    node: { node* next; const char* keyword; void (*parse)(INI*); }

Each block-parse function then references a FieldParse table, which is likewise
plain data:

    FieldParse: { const char* token; INIFieldParseProc parse; const void* userData; Int offset; }

terminated by a NULL token. Field procs that are themselves sub-block parsers
(the Weapon nuggets, the Object modules) carry their own tables, so this
recurses into them.

Nothing here is inferred: tokens and offsets are bytes out of the image. The
only judgement call is which 4-byte immediate in a function body is a table
pointer, and that is settled by requiring the candidate to decode as a
well-formed, NULL-terminated array of plausible entries.

Usage:
  python3 tools/dump_ini_schema.py [--out docs/ini_schema.md] [--json PATH]
"""
import argparse
import csv
import json
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build as B
import capstone

_MD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
_BRANCH = {"jmp", "je", "jne", "jg", "jge", "jl", "jle", "ja", "jae", "jb",
           "jbe", "js", "jns", "jo", "jno", "jp", "jnp", "jecxz", "loop"}

BLOCK_LIST_HEAD = 0x0130CE50    # INI::findBlockParse walks the list rooted here
IMAGE_BASE = 0x00400000
MIN_EXPECTED_BLOCKS = 50        # sanity floor; the pattern finds ~97


class Image:
    def __init__(self):
        self.data = open(B.EXE, "rb").read()
        self.secs = B.pe_sections(self.data)
        text = next(s for s in self.secs if s["name"] == ".text")
        self.text = bytes(self.data[text["raw_pointer"]:text["raw_pointer"] + text["size"]])
        self.tbase = text["rva"]

    def read(self, vma, n):
        rva = vma - IMAGE_BASE
        for s in self.secs:
            if s["rva"] <= rva < s["rva"] + max(s["size"], 1):
                o = s["raw_pointer"] + (rva - s["rva"])
                return self.data[o:o + n]
        return b""

    def cstr(self, vma, limit=96):
        b = self.read(vma, limit)
        if not b:
            return None
        b = b.split(b"\x00")[0]
        if not b or len(b) > 64 or not all(32 <= c < 127 for c in b):
            return None
        return b.decode("latin1")

    def in_text(self, vma):
        return self.tbase <= vma - IMAGE_BASE < self.tbase + len(self.text)

    def deref_thunk(self, rva, limit=8):
        """Follow 5-byte incremental-link E9 jumps to the real body.

        Chains, not a single hop. The AIData block registers a thunk that jumps
        to another thunk that jumps to ?parseAiDataDefinition@AI@@ -- stopping
        after one hop leaves you looking at five bytes of jump, which measures as
        a 5-byte function with no field table. AIData is the game's AI tuning
        block; it was published as "parses its body directly" for exactly that
        reason.
        """
        for _ in range(limit):
            o = rva - self.tbase
            if not (0 <= o < len(self.text) - 5) or self.text[o] != 0xE9:
                return rva
            nxt = rva + 5 + struct.unpack("<i", self.text[o + 1:o + 5])[0]
            if nxt == rva:
                return rva
            rva = nxt
        return rva

    def body_size(self, rva, limit=8192):
        """Length of the function at rva, by disassembly rather than int3 scanning.

        Scanning for the first 0xCC is wrong: 0xCC occurs inside instructions
        (immediates, displacements, ModRM bytes), and truncating there silently
        under-reports. INI::parseAudioEventRTS at 0x000BBB60 measures 47 bytes
        that way and is really 181 -- and a short body means the tail's field
        tables are never seen. So walk instructions instead, tracking the
        furthest branch target, and stop at the first ret/tail-jmp that no
        branch reaches past.
        """
        o = rva - self.tbase
        if not (0 <= o < len(self.text)):
            return None
        furthest = rva
        for ins in _MD.disasm(self.text[o:o + limit], rva):
            if ins.op_str.startswith("0x") and ins.mnemonic in _BRANCH:
                furthest = max(furthest, int(ins.op_str, 16))
            end = ins.address + ins.size
            if ins.mnemonic in ("ret", "retf") and ins.address >= furthest:
                return end - rva
            if ins.mnemonic == "jmp" and ins.address >= furthest:
                return end - rva          # tail call
            if ins.mnemonic == "int3" and ins.address >= furthest:
                return ins.address - rva  # ran into padding
        return None


def load_ledger():
    rows = []
    with open(B.ROOT / "reverse/functions.csv", newline="", encoding="utf-8") as fh:
        for r in csv.DictReader(fh):
            try:
                rows.append((int(r["target_rva"], 16), int(r["target_size"]), r["name"]))
            except ValueError:
                pass
    rows.sort()

    def owner(t):
        lo, hi, best = 0, len(rows) - 1, None
        while lo <= hi:
            m = (lo + hi) // 2
            if rows[m][0] <= t:
                best, lo = rows[m], m + 1
            else:
                hi = m - 1
        return best[2] if best and best[0] <= t < best[0] + best[1] else None

    return owner


def find_blocks(img):
    """Every {keyword, parse} the block list is built from."""
    pat = re.compile(rb"\xc7\x05" + struct.pack("<I", BLOCK_LIST_HEAD) + rb"(....)", re.DOTALL)
    nodes = sorted({struct.unpack("<I", m.group(1))[0] for m in pat.finditer(img.text)})
    if len(nodes) < MIN_EXPECTED_BLOCKS:
        raise SystemExit(
            f"dump_ini_schema: found only {len(nodes)} block nodes via the "
            f"0x{BLOCK_LIST_HEAD:08X} store pattern, expected >= {MIN_EXPECTED_BLOCKS}. "
            "The list head or the registration shape has changed -- fix this "
            "before trusting any output."
        )
    out = []
    for nd in nodes:
        raw = img.read(nd, 12)
        if len(raw) < 12:
            continue
        _next, kwp, fnp = struct.unpack("<III", bytes(raw))
        kw = img.cstr(kwp)
        if kw is None or not img.in_text(fnp):
            continue
        out.append((kw, img.deref_thunk(fnp - IMAGE_BASE)))
    return out


def decode_table(img, vma, maxn=512):
    """Entries if vma is a NULL-terminated FieldParse array, else None."""
    ents = []
    for i in range(maxn):
        raw = img.read(vma + i * 16, 16)
        if len(raw) < 16:
            return None
        tok, fn, ud, off = struct.unpack("<IIIi", bytes(raw))
        if tok == 0:
            return ents or None
        s = img.cstr(tok)
        if s is None or not img.in_text(fn) or not (0 <= off < 0x8000):
            return None
        ents.append(dict(token=s, fn=fn - IMAGE_BASE, userData=ud, offset=off))
    return None


def tables_in(img, rva, size):
    """FieldParse tables referenced by absolute address inside a function body."""
    o = rva - img.tbase
    body = img.text[o:o + size]
    seen, out = set(), []
    for i in range(max(0, len(body) - 3)):
        v = struct.unpack("<I", body[i:i + 4])[0]
        if not (IMAGE_BASE < v < 0x01400000) or v in seen:
            continue
        seen.add(v)
        ents = decode_table(img, v)
        if ents:
            out.append((v, ents))
    out.sort(key=lambda t: -len(t[1]))
    return out


def walk(img, rva, depth, seen_tables, max_depth=3):
    """Tables for a parse function, recursing into sub-block field procs."""
    size = img.body_size(rva)
    if not size or depth > max_depth:
        return []
    out = []
    for addr, ents in tables_in(img, rva, size):
        if addr in seen_tables:
            continue
        seen_tables.add(addr)
        sub = []
        for e in ents:
            target = img.deref_thunk(e["fn"])
            nested = walk(img, target, depth + 1, seen_tables, max_depth)
            if nested:
                sub.append(dict(token=e["token"], tables=nested))
        out.append(dict(addr=addr, entries=ents, sub=sub))
    return out


TYPE_HINT = re.compile(r"\?parse(\w+?)@")


def type_of(owner_name):
    if not owner_name:
        return "?"
    m = TYPE_HINT.match(owner_name)
    return m.group(1) if m else owner_name.split("@")[0].lstrip("?")


def emit(fh, img, owner, blocks, results):
    fields = sum(len(t["entries"]) for r in results for t in r["tables"])
    fh.write("# BFME 1.03 INI schema\n\n")
    fh.write(
        "Generated by `tools/dump_ini_schema.py` straight from `lotrbfme.exe`. Every\n"
        "block keyword, field token and struct offset below is a byte read out of the\n"
        "image, not an inference: the block registry is a linked list of static nodes\n"
        "rooted at `0x%08X`, and each block-parse function points at a\n"
        "NULL-terminated `FieldParse` array of\n"
        "`{const char* token; INIFieldParseProc parse; const void* userData; Int offset;}`.\n\n"
        "`Type` is the parse procedure the field dispatches to; where that procedure is\n"
        "already recovered in `reverse/functions.csv` it is named, otherwise its address\n"
        "is given. `Offset` is the field's byte offset into the block's own struct, so\n"
        "these tables double as the class layouts.\n\n" % BLOCK_LIST_HEAD
    )
    fh.write(f"- **{len(blocks)}** registered block keywords\n")
    fh.write(f"- **{sum(1 for r in results if r['tables'])}** with a decodable field table\n")
    fh.write(f"- **{fields}** field entries\n\n")
    fh.write("## Blocks\n\n")
    for r in sorted(results, key=lambda x: x["keyword"].lower()):
        fh.write(f"### `{r['keyword']}`\n\n")
        fh.write(f"Parsed by `0x{r['fn']:08X}`")
        if r["row"]:
            fh.write(f" — `{r['row']}`")
        fh.write("\n\n")
        if not r["tables"]:
            fh.write("_No field table: this block parses its body directly._\n\n")
            continue
        for t in r["tables"]:
            fh.write(f"Field table `0x{t['addr']:08X}` — {len(t['entries'])} fields\n\n")
            fh.write("| Field | Offset | Type |\n|---|---|---|\n")
            for e in t["entries"]:
                nm = owner(img.deref_thunk(e["fn"]))
                ty = f"`{type_of(nm)}`" if nm else f"`0x{img.deref_thunk(e['fn']):08X}`"
                fh.write(f"| `{e['token']}` | `0x{e['offset']:03X}` | {ty} |\n")
            fh.write("\n")
            for s in t["sub"]:
                for st in s["tables"]:
                    fh.write(f"<details><summary><code>{s['token']}</code> sub-block "
                             f"— {len(st['entries'])} fields</summary>\n\n")
                    fh.write("| Field | Offset | Type |\n|---|---|---|\n")
                    for e in st["entries"]:
                        nm = owner(img.deref_thunk(e["fn"]))
                        ty = f"`{type_of(nm)}`" if nm else f"`0x{img.deref_thunk(e['fn']):08X}`"
                        fh.write(f"| `{e['token']}` | `0x{e['offset']:03X}` | {ty} |\n")
                    fh.write("\n</details>\n\n")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", default="docs/ini_schema.md")
    ap.add_argument("--json", default=None)
    args = ap.parse_args()

    img = Image()
    owner = load_ledger()
    blocks = find_blocks(img)

    results = []
    for kw, fn in blocks:
        seen = set()
        results.append(dict(keyword=kw, fn=fn, row=owner(fn),
                            tables=walk(img, fn, 0, seen)))

    out = B.ROOT / args.out
    out.parent.mkdir(parents=True, exist_ok=True)
    with open(out, "w", encoding="utf-8") as fh:
        emit(fh, img, owner, blocks, results)

    if args.json:
        json.dump(results, open(B.ROOT / args.json, "w"), indent=1)

    procs = {}
    for r in results:
        for t in r["tables"]:
            for e in t["entries"]:
                procs.setdefault(img.deref_thunk(e["fn"]), set()).add(e["token"])
    named = sum(1 for p in procs if owner(p))
    print(f"{len(blocks)} blocks, "
          f"{sum(len(t['entries']) for r in results for t in r['tables'])} fields -> {out}")
    print(f"{len(procs)} distinct field procs: {named} named, {len(procs) - named} unclaimed")


if __name__ == "__main__":
    main()
