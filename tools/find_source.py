#!/usr/bin/env python3
"""Locate the .cpp that DEFINES a candidate, by text search rather than inference.

Why this exists: the remaining gen-dump pool is not mostly blocked on layout
drift. It is blocked on not knowing which source file should define the row at
all. Of 318 workable one-real-pin candidates, 286 sit in a class with no matched
sibling anywhere in functions.csv, so there is no file to point a compiler at,
and every mismatch-explaining tool in tools/ is useless on them because they all
start from "compile this TU and diff". The heuristic tried before this tool --
"use the file where most of the class's matched siblings live" -- located the
symbol in under 30% of the cases where it could even be applied, and by
construction it cannot be applied at all to a class with zero matched siblings.

The observation this tool rests on: a definition is TEXT. `Object::hasUpgradeMask`
appears literally in whatever .cpp defines it, whether or not the ledger has ever
heard of the class. So instead of inferring the file from ledger statistics, scan
the tree once for `Scope::member(` definition sites and look the candidate up.

This tool DECIDES NOTHING and CLAIMS NOTHING. A text hit is a place to point
tools/build.py, not evidence that the bytes match -- name collisions across
unrelated classes, overloads, and same-named overrides in derived classes are all
common here (Drawable::replaceModelConditionState was refuted precisely because
the only hit was a W3DModelDraw override). It writes no ledger rows and spends no
attempt. Byte-verify remains the only judge.

Usage:
  python3 tools/find_source.py --pool            # locate every one-real-pin candidate
  python3 tools/find_source.py --name '?foo@Bar@@QAEXXZ'
  python3 tools/find_source.py --pool --out reverse/source_candidates.csv
  python3 tools/find_source.py --pool --stats    # just the coverage numbers

Scope filtering: vendored and reference trees (Code/Libraries/**/reference,
CnC_Generals_Zero_Hour, and the generator outputs Code/gen_asm, Code/gen_small,
Code/masm_dumps) are searched but reported separately and NEVER counted as a
located source -- a hit in a different game's source tree is a lead, not an
answer, and treating one as an answer is how a wrong pin gets landed.
"""
import argparse
import csv
import io
import re
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS = ROOT / "reverse" / "functions.csv"
SYMBOLS = ROOT / "reverse" / "symbols.csv"
CODE = ROOT / "Code"


# Generator output and vendored/reference trees. Hits here are reported but never
# counted as a located source.
NON_ANSWER_PARTS = (
    "gen_asm", "gen_small", "masm_dumps", "reference",
    "CnC_Generals_Zero_Hour", "Generals",
)

PLACEHOLDER_RE = re.compile(r"^\?[bd]_[0-9a-f]{8}@@")
SRC_SUFFIXES = {".cpp", ".c", ".cc", ".h", ".hpp", ".inl"}

# `Scope::member(` at a definition site. Deliberately loose on what precedes it
# (return types here range across templates, macros and calling conventions) and
# strict on what follows, since a definition is always followed by a parameter
# list. Call sites like `obj->Scope::member(` are excluded by requiring the
# scope to not be preceded by `.`/`->`.
DEF_RE = re.compile(
    r"(?<![.>\w])([A-Za-z_]\w*)\s*::\s*(~?[A-Za-z_]\w*|operator\s*\S{1,2})\s*\(")


def is_placeholder(name):
    return bool(PLACEHOLDER_RE.match(name))


def parse_scope(mangled):
    """MSVC mangling -> ('Scope', 'member') as it appears in source text.

    Handles the three shapes that actually dominate this pool:
      ?member@Scope@@...     -> ('Scope', 'member')
      ??0Scope@@...          -> ('Scope', 'Scope')      constructor
      ??1Scope@@...          -> ('Scope', '~Scope')     destructor
      ?member@Inner@Outer@@  -> ('Inner', 'member')     nested: the qualifier
                                written at the definition site is the INNERMOST
                                scope, which is what the text search must match.

    Templates (`?$`), vftables/thunks (`??_`), operators and free functions are
    returned as None. Each would need a different search string and guessing one
    produces confident hits for the wrong entity, which is worse than a miss.
    """
    if not mangled.startswith("?"):
        return None
    if "?$" in mangled or mangled.startswith("??_"):
        return None

    if mangled.startswith("??0") or mangled.startswith("??1"):
        is_dtor = mangled[2] == "1"
        body = mangled[3:]
        at = body.find("@@")
        if at == -1:
            return None
        parts = [p for p in body[:at].split("@") if p]
        if not parts or not re.fullmatch(r"[A-Za-z_]\w*", parts[0]):
            return None
        cls = parts[0]
        return cls, ("~" + cls if is_dtor else cls)

    if mangled.startswith("??"):
        return None  # operator / other special name

    body = mangled[1:]
    at = body.find("@@")
    if at == -1:
        return None
    parts = body[:at].split("@")
    if len(parts) < 2:
        return None  # free function -- no `Scope::` text to search for
    member, scope = parts[0], parts[1]
    if not re.fullmatch(r"[A-Za-z_]\w*", scope or ""):
        return None
    if not re.fullmatch(r"[A-Za-z_]\w*", member or ""):
        return None
    return scope, member


def load_ledger():
    rows = []
    raw = FUNCTIONS.read_bytes().decode("utf-8")
    for i, r in enumerate(csv.reader(io.StringIO(raw)), start=1):
        if i == 1 or not r or (len(r) == 1 and not r[0]):
            continue
        if len(r) != 7:
            raise SystemExit(f"functions.csv line {i}: {len(r)} fields, not 7")
        rows.append(r)
    return rows


def load_real_pins():
    """address(RVA) -> [names], placeholders excluded.

    symbols.csv addresses are RVAs, in the SAME space as functions.csv. This
    was originally written as VA and the pool was built at `IMAGE_BASE + rva`,
    which silently paired every candidate with a DIFFERENT function's pin and
    voided a whole 70-candidate work queue. Verified after the fact: of matched
    functions.csv rows whose name also appears in symbols.csv, 743 agree on the
    address exactly and ZERO agree at +0x400000.
    """
    pins = defaultdict(list)
    raw = SYMBOLS.read_bytes().decode("utf-8")
    for i, r in enumerate(csv.reader(io.StringIO(raw)), start=1):
        if i == 1 or not r or len(r) < 2 or not r[1]:
            continue
        name = r[0]
        if is_placeholder(name):
            continue
        try:
            pins[int(r[1], 16)].append(name)
        except ValueError:
            continue
    return pins


def build_pool():
    """gen-dump scaffold rows containing exactly one real pin."""
    pins = load_real_pins()
    addrs = sorted(pins)
    import bisect
    out = []
    for name, _exp, rva_s, size_s, source, status, notes in load_ledger():
        if status != "matched" or not notes.lstrip().startswith("gen-dump"):
            continue
        if not is_placeholder(name):
            continue
        rva = int(rva_s, 16)
        size = int(size_s or 0)
        if size <= 0:
            continue
        lo = rva
        hi = lo + size
        i = bisect.bisect_left(addrs, lo)
        hits = []
        while i < len(addrs) and addrs[i] < hi:
            hits.extend(pins[addrs[i]])
            i += 1
        if len(hits) == 1:
            out.append({"row": name, "rva": rva, "size": size,
                        "source": source, "pin": hits[0]})
    return out


NEWLINE = chr(10)


def strip_comments(text):
    """Blank out // and /* */ comments, preserving length and line structure.

    Without this the index reports commented-out code as a definition:
    dx8renderer.cpp contains only `//DX8Wrapper::Set_DX8_ZBias(zbias);`, which
    was confidently reported as that symbol's defining file while the real
    definition sits in dx8wrapper.cpp. Offsets are preserved (replaced in place,
    newlines kept) so is_definition() can still index into the result.
    """
    out = list(text)
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c in "\"'":
            q = c
            i += 1
            while i < n and text[i] != q:
                if text[i] == "\\":
                    i += 1
                i += 1
            i += 1
        elif text.startswith("//", i):
            while i < n and text[i] != NEWLINE:
                out[i] = " "
                i += 1
        elif text.startswith("/*", i):
            while i < n and not text.startswith("*/", i):
                if text[i] != NEWLINE:
                    out[i] = " "
                i += 1
            for j in range(i, min(i + 2, n)):
                out[j] = " "
            i += 2
        else:
            i += 1
    return "".join(out)


def is_definition(text, open_paren):
    """True if the `(` at open_paren starts a DEFINITION's parameter list.

    A call site (`Shim::run();`) is textually identical to a definition header
    under DEF_RE, and treating one as the other is how this tool first reported
    four declaration-only pin-scaffold TUs as the located source for shims they
    only declare and call. The discriminator is what follows the closing paren:
    a definition opens a body, everything else terminates. Constructors may
    carry an initialiser list, so `:` counts as a definition too -- but `::`
    does not, since that is a qualified name in a trailing return or default
    argument, not an init list.
    """
    depth = 0
    i = open_paren
    n = len(text)
    while i < n:
        c = text[i]
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
            if depth == 0:
                break
        elif c in ";{}":
            return False  # ran off the end of a sane parameter list
        i += 1
    else:
        return False
    i += 1
    # skip cv-qualifiers, exception specs and whitespace between `)` and the body
    while i < n:
        if text[i].isspace():
            i += 1
            continue
        for kw in ("const", "throw", "volatile"):
            if text.startswith(kw, i) and not (text[i + len(kw):i + len(kw) + 1] or " ").isalnum():
                i += len(kw)
                break
        else:
            break
    if i >= n:
        return False
    if text[i] == "{":
        return True
    return text[i] == ":" and not text.startswith("::", i)


def index_definitions():
    """'Scope::member' -> {answerable: [paths], excluded: [paths]}."""
    idx = defaultdict(lambda: {"answerable": [], "excluded": []})
    scanned = 0
    for path in CODE.rglob("*"):
        if not path.is_file() or path.suffix.lower() not in SRC_SUFFIXES:
            continue
        rel = path.relative_to(ROOT).as_posix()
        bucket = "excluded" if any(p in rel for p in NON_ANSWER_PARTS) else "answerable"
        try:
            text = path.read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        scanned += 1
        text = strip_comments(text)
        seen = set()
        for m in DEF_RE.finditer(text):
            key = f"{m.group(1)}::{m.group(2)}"
            if key in seen or not is_definition(text, m.end() - 1):
                continue
            seen.add(key)
            idx[key][bucket].append(rel)
    return idx, scanned


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pool", action="store_true",
                    help="locate every one-real-pin gen-dump candidate")
    ap.add_argument("--name", action="append", default=[],
                    help="locate one mangled name (repeatable)")
    ap.add_argument("--out", help="write results as CSV")
    ap.add_argument("--stats", action="store_true", help="coverage summary only")
    args = ap.parse_args()

    if not args.pool and not args.name:
        raise SystemExit(__doc__)

    idx, scanned = index_definitions()
    print(f"indexed {len(idx)} distinct Scope::member definition sites "
          f"across {scanned} files", file=sys.stderr)

    if args.pool:
        pool = build_pool()
    else:
        pool = [{"row": "", "rva": 0, "size": 0, "source": "", "pin": n}
                for n in args.name]

    results = []
    counts = defaultdict(int)
    for c in pool:
        parsed = parse_scope(c["pin"])
        if parsed is None:
            counts["unparseable"] += 1
            verdict, files = "UNPARSEABLE", []
        else:
            key = f"{parsed[0]}::{parsed[1]}"
            hit = idx.get(key)
            if hit and hit["answerable"]:
                n = len(hit["answerable"])
                verdict = "LOCATED" if n == 1 else f"AMBIGUOUS({n})"
                counts["located" if n == 1 else "ambiguous"] += 1
                files = hit["answerable"]
            elif hit and hit["excluded"]:
                verdict, files = "REFERENCE-ONLY", hit["excluded"]
                counts["reference_only"] += 1
            else:
                verdict, files = "NO-DEFINITION", []
                counts["no_definition"] += 1
        results.append({**c, "verdict": verdict, "files": ";".join(files[:4])})

    total = len(pool)
    print(f"\npool: {total} candidate(s)")
    for k in ("located", "ambiguous", "reference_only", "no_definition", "unparseable"):
        v = counts[k]
        pct = (100.0 * v / total) if total else 0.0
        print(f"  {k:<16} {v:>5}  {pct:5.1f}%")

    if not args.stats:
        for r in results:
            if r["verdict"] in ("NO-DEFINITION", "UNPARSEABLE"):
                continue
            print(f"0x{r['rva']:08X} {r['verdict']:<14} {r['pin']}")
            for f in r["files"].split(";"):
                if f:
                    print(f"      {f}")

    if args.out:
        p = Path(args.out)
        if not p.is_absolute():
            p = ROOT / p
        with p.open("w", newline="", encoding="utf-8") as fh:
            w = csv.writer(fh, lineterminator="\r\n")
            w.writerow(["row", "target_rva", "target_size", "scaffold_source",
                        "pin", "verdict", "files"])
            for r in results:
                w.writerow([r["row"], f"0x{r['rva']:08X}", r["size"],
                            r["source"], r["pin"], r["verdict"], r["files"]])
        print(f"wrote {p.relative_to(ROOT)}")


if __name__ == "__main__":
    main()
