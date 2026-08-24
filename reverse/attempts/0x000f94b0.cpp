// ?bfmeNthEntry@ScriptConditions@@IAEPAXH@Z
// partial score=0.9 date=2026-08-24
// cl: /DNDEBUG /MD /EHs-c-

// Retail 0x000F94B0, 68 bytes. reverse/reloc_names.csv carries this address as
// ?playerFromParam@ScriptConditions@@IAEPAVPlayer@@PAVParameter@@@Z with
// identity=real, but that signature cannot be what compiled: the argument is
// tested with test/jl before anything else, and a Parameter * cannot be
// compared against zero for sign. It is an index, so the name goes in the
// notes and the row gets a shape-honest one.
//
// What the body is: a bounds-checked walk to the index'th element of a
// half-open pointer pair held at +0x04 and +0x08.
//
//   - 0x2AAAAAAB with sar 4 is the signed divide by 96, so the elements are
//     0x60 bytes -- which the add eax,0x60 in the loop confirms.
//   - The bound compare is jae, not jge, so the index is widened to unsigned
//     for it while the sign test stays signed. That is exactly what comparing
//     an Int against an unsigned size gives.
//   - The pair is re-read after the bounds check rather than kept in
//     registers, so begin and end are separate expressions there.

typedef int Int;
typedef unsigned int UnsignedInt;

#define NULL 0

class BfmeScriptConditionEntry
{
public:
	char m_bfmeBody[0x60];
};

class ScriptConditions
{
protected:
	void *bfmeNthEntry(Int index);

private:
	char m_bfmeHead[0x04];
	BfmeScriptConditionEntry *m_bfmeStart;			// +0x04
	BfmeScriptConditionEntry *m_bfmeFinish;			// +0x08
};

// ?bfmeNthEntry@ScriptConditions@@IAEPAXH@Z
void *ScriptConditions::bfmeNthEntry(Int index)
{
	if (index < 0 || (UnsignedInt)index >= (UnsignedInt)(m_bfmeFinish - m_bfmeStart))
		return NULL;

	for (BfmeScriptConditionEntry *entry = m_bfmeStart; entry != m_bfmeFinish; ++entry, --index)
		if (index == 0)
			return entry;

	return NULL;
}
