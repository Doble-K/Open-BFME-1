// ?accepts@Rva2225E0Filter@@QAE_NPAVObject@@PAVPlayer@@@Z
// partial score=0.95 date=2026-08-24
// cl: /DNDEBUG /MD /EHs-c-

// Retail 0x003A04A0, 72 bytes. All three call sites already had names minted
// for them in reverse/symbols.csv when the filtered count at 0x002225E0
// landed, and the function's own name is pinned at ILT 0x0001DA34.
//
// The middle stretch is an override walk that MSVC unrolled one level. Reading
// it as written: the pointer at +0x04 of the object is fetched, and if it is
// null the walk yields null; otherwise its own +0x04 decides. When that is set
// the walk recurses through the ILT, and when it is not the value in eax is
// still the pointer we started from -- which is the walk returning this. That
// leftover is why the else arm assigns the same pointer instead of reloading
// it.
//
// The two results then go to the private test, arguments right to left: the
// query result pushed first, the walked-to override second.

typedef bool Bool;

class Player;

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride(void);		// ILT 0x000022BB

	char m_bfmeHead[0x04];
	BfmeOverridable *m_bfmeNextOverride;			// +0x04
};

class BfmeFilterObject
{
public:
	Bool bfmeQuery(Player *player);				// ILT 0x00020824

	char m_bfmeHead[0x04];
	BfmeOverridable *m_bfmeOverride;			// +0x04
};

class Object : public BfmeFilterObject
{
};

class Rva2225E0Filter
{
public:
	Bool accepts(Object *object, Player *player);

private:
	Bool bfmeTest(BfmeOverridable *override, Bool queried);	// ILT 0x0001B437
};

// ?accepts@Rva2225E0Filter@@QAE_NPAVObject@@PAVPlayer@@@Z
Bool Rva2225E0Filter::accepts(Object *object, Player *player)
{
	if (!object)
		return false;

	BfmeOverridable *override = object->m_bfmeOverride;
	BfmeOverridable *walked;

	if (override == 0)
		walked = 0;
	else if (override->m_bfmeNextOverride)
		walked = override->m_bfmeNextOverride->friend_getFinalOverride();
	else
		walked = override;

	return bfmeTest(walked, object->bfmeQuery(player));
}
