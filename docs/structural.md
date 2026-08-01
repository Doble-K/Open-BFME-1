# Structural reconciliation — the manual-RE workflow

For drift rows classed `structural`/`register-swap`, the source exists but
compiles to differently-shaped code. Expect 30-60 minutes per function.

## The loop for ONE function

1. Run `python3 tools/next_work.py --tier structural`; it selects one candidate
   randomly from the highest-quality band.
2. `python3 tools/explain_mismatch.py '<sym>' --rva <candidate_rva> --size <size> --source <src>`
   Read the classification line first, then the side-by-side disasm.
3. Fix in dependency order — earlier classes mask later ones:
   a. **unresolved REL32 call** — resolve callees FIRST:
      `python3 tools/decode_calls.py <src> --rva <candidate_rva>` prints the
      symbols.csv pins. Add them, re-explain; the real diff often shrinks
      or vanishes.
   b. **misplaced candidate** — if the first target bytes look like another
      function's tail (`ret`/`int3` within a few bytes), the drift vote is
      shifted. Find the true start in `reverse/ghidra_functions.csv`; trust a
      `ret` boundary plus export evidence when Ghidra merges functions.
   c. **field-offset diffs** (`[reg+0xNN]` vs `[reg+0xMM]`, same instruction
      shape): BFME changed a struct layout — or the retail code has a genuine
      bug. Change the member access, or the header layout only when verified
      siblings permit it, then byte-verify the whole file.
   d. **literal diffs** (immediates, string addresses): fix the constant.
   e. **shape diffs** (branch layout, register choice, inlining): the hard
      class. Try early-return versus nesting, inverted branch arms,
      hoisting/sinking common expressions, declaration order, temp versus
      re-read, and splitting/merging conditions. Do not chase x87 operand
      order or pure register renames beyond two attempts; see the matching
      documentation's negative patterns.
4. If exact, run `python3 tools/add_match.py '<sym>' <rva> <size> <src>` to
   validate, append, strip the marker, and re-verify; then bank the unit.
5. If it did not land, revert the source. Do not retain a nonmatching body or
   per-function failure notes.

An interior-only body is probably inlined; identical already-claimed bytes are
probably ICF-folded. Compiler-only machinery such as SEH array-constructor or
`_initterm` stubs may require the existing naked-assembly precedent. In each
case, verify the evidence, revert the experiment, and take another candidate.

## Escalation beyond drift rows

When this queue thins, use `python3 tools/next_work.py --tier ghidra` for
string-anchored absent functions. Apply the same evidence, verification, and
revert rules.
