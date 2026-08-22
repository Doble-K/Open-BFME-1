// The 30 byte-identical 33-byte wrapper constructors of BFME's
// single-inheritance functor-bind family.
//
// Companion to FunctorBindWrapperCtors.cpp, which lands the same constructor
// for the multiple-inheritance family; read that header and
// FunctorBindSingleInvokers.cpp first.  Retail:
//
//     mov eax,ecx / mov ecx,[esp+4]
//     mov [eax+4],0 / mov [eax],<vftable>
//     mov edx,[ecx] / mov [eax+8],edx
//     mov ecx,[ecx+4] / mov [eax+0xC],ecx / ret 4
//
// The same function as the 49-byte one with the bound sub-object collapsed
// from four dwords to two: `mov eax,ecx` with no other use of eax is a
// __thiscall constructor returning `this`, one dword argument and `ret 4`, a
// vftable to +0x00, zero to +0x04, and EIGHT bytes copied out of the argument
// into +0x08.  Eight bytes is {object, code} -- a 4-byte single-inheritance
// pointer-to-member bound to an object, exactly what the family's own invoker
// dispatches through: 0x0058D110 and its 23 twins in
// FunctorBindSingleInvokers.cpp are `mov eax,ecx / mov ecx,[eax+8] /
// jmp [eax+0xC]`, object at wrapper +0x08 and code at +0x0C with no delta
// added.  The source is read at +0x00 and +0x04, from the argument's own base
// rather than from +0x08, so the argument is the binding and not another
// wrapper -- the shape the 24 initialisers in FunctorBindSingleInit.cpp fill
// in.
//
// The leading two dwords are a base for the reason FunctorBindInvokers.cpp
// measured and FunctorBindSingleInvokers.cpp repeats; here it also gives the
// vftable this constructor writes somewhere real to live.  The base zeroes the
// unmodelled dword and MSVC drops the base's own vftable store as dead, which
// is why retail writes +0x04 before +0x00.
//
// Unlike the 49-byte family the two copied dwords are stored straight off
// `this` instead of through a `lea ecx,[eax+8]`: with only two dwords MSVC 7.1
// inlines the sub-object copy without materialising its address.  Same source
// shape, different inlining.
//
// WHY THE COPIES ARE NOT FOLDED, AND WHY THE NAMES ARE ADDRESS-DERIVED: as in
// FunctorBindConstructors.cpp.  30 distinct addresses, 30 separate template
// instantiations, and no surviving name for the class -- the only RTTI
// descriptor the framework leaves in the image is `.?AVFunctorNotSet@@`.

class __single_inheritance FunctorTargetSingle;

typedef void (FunctorTargetSingle::*FunctorMethodSingle)(void);

struct FunctorBindingSingle
{
	FunctorTargetSingle *m_target;
	FunctorMethodSingle  m_method;
};

class FunctorSingleWrapperHead
{
public:
	FunctorSingleWrapperHead() : m_unmodelled_04( 0 ) {}

	virtual void functorSingleWrapperAnchor();

	unsigned int m_unmodelled_04;
};

#define BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( NAME )                              \
	class NAME : public FunctorSingleWrapperHead                              \
	{                                                                         \
	public:                                                                   \
		NAME( const FunctorBindingSingle &binding );                          \
                                                                              \
		FunctorBindingSingle m_binding;                                       \
	};                                                                        \
	NAME::NAME( const FunctorBindingSingle &binding ) : m_binding( binding ) {}

BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0049A120FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva005102A0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0051BDE0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva00520AB0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva00520AF0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva00522570FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva00525A30FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0052E240FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0052E280FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva00546510FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva00546550FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva00546590FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0054D870FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0054D8B0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva005542A0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva005542E0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva00558E00FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva00558E40FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva00558E80FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva00566A60FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva00582470FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0058CF10FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0058CF50FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0058CF80FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0058CFD0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0058D030FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0058D070FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0058D0A0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0058D0E0FunctorSingleWrapper )
BFME_FUNCTOR_SINGLE_WRAPPER_CTOR( Rva0058D1E0FunctorSingleWrapper )
