* When hand-declaring a class just to carry a naked body's decorated name, the access specifier is part of the name: MSVC encodes public as Q, protected as I and private as A in the third character (`??0X@@QAE@XZ` vs `??0X@@IAE@XZ`). Declaring DisconnectManager's constructor under `protected:` produced ??0DisconnectManager@@IAE@XZ and the build failed with "symbol not found in object" rather than a byte mismatch, which is the tell. Match the reference header's section, not just the signature.

* A byte-exact function needs every call site to resolve, so a big function's
  cost is set by its least-known callee, not by its size. GameEngine::init is
  7123 bytes with 165 distinct call targets: 92 are named, 73 are not. Of those
  73, sixteen are the 154-byte initSubsystem bodies that cannot be claimed until
  their T is proven, and only seven reference a string that could anchor a name
  -- the other fifty have no evidence attached to them at all. So init is not
  blocked on effort or on codegen, it is blocked on roughly fifty independent
  naming problems, and counting them is cheaper than discovering them one
  mismatch at a time. Run the same count before committing to any large
  function: for each call, deref the thunk chain and check functions.csv plus
  symbols.csv. Applied to the 96 INI block parsers the same count sorts them
  into four with no blockers, eleven with exactly one, and the rest with two or
  more, which is a work queue rather than a list.

* A MASM dump byte-matches at any length you give it, because it is the retail
  bytes. That makes an over-long dump row invisible to the verifier in a way an
  over-long C++ row is not: ?parse@DataChunkInput@@QAE_NPAX@Z claimed 1006 bytes
  where the function is 231, ran past its ret 0x10 and the int3 padding after it,
  and silently swallowed three later functions -- one of which, LocalFile's
  constructor, then could not be claimed because its address was already inside
  somebody else's range. tools/audit_short_rows.py looks for the opposite
  mistake. Check a dump row's size against a real disassembly before trusting
  it, especially when a claim inside its range mysteriously will not land.


## A mangled name can encode an argument list the body does not have

`?queueSend@Transport@@QAE_NIGPBEH@Z` mangles four parameters
(`UnsignedInt, UnsignedShort, const UnsignedByte *, Int`), so a `__thiscall`
body would end in `ret 0x10`. BFME's body at 0x00683830 ends in `ret 0xc`, and
the caller (`NAT::sendAProbe`, 0x00671020) builds a local
`{ UnsignedInt ip; UnsignedShort port; }` on the stack and passes its address --
the callee reads `[ecx]` and `[ecx+4]` off it. BFME merged the reference's first
two scalars into one struct-by-pointer, so the name in the ledger cannot be the
name retail's linker emitted, and the struct's type name is not recoverable
from a POD with no RTTI.

The row is harmless as long as it only claims the 5-byte thunk, which is what it
does, but it will silently mislead anyone who trusts the name to write the body.
Check `ret imm16` against the mangled parameter list before writing a body from
a thunk-claimed name: the stack-pop is free evidence and it disagrees loudly.

## Compilers pick an induction base by a tie-break you cannot see from the source

`Transport::Transport` clears two 128-element arrays in one loop, and every
candidate base address gives the same instruction count and the same total
length. Retail anchors on `&m_inBuffer[i].length`; writing the out buffer first
anchors on `&m_outBuffer[i].length`, writing the in buffer first anchors on
`&m_inBuffer[i].data`. All three are 182 bytes of the same instructions. When a
body reaches the right length with the right instructions and differs only in
which base register displacement scheme was chosen, source-order permutations
are unlikely to be the lever; stop permuting and mark it present-unmatched.
