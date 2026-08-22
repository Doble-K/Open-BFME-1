// The 41 byte-identical 49-byte wrapper constructors of BFME's
// functor-binding family.
//
// Companion to FunctorBindConstructors.cpp and FunctorBindInvokers.cpp; read
// those headers first for how the family's layout was recovered.  Retail:
//
//     mov edx,[esp+4] / mov eax,ecx / push esi
//     mov [eax+4],0 / mov [eax],<vftable>
//     mov esi,[edx] / lea ecx,[eax+8] / mov [ecx],esi
//     mov esi,[edx+4] / mov [ecx+4],esi / mov esi,[edx+8] / mov [ecx+8],esi
//     mov edx,[edx+0xC] / mov [ecx+0xC],edx / pop esi / ret 4
//
// WHAT THE BODY IS.  `mov eax,ecx` with no other use of eax is a __thiscall
// constructor returning `this`; one dword argument and `ret 4`.  A vftable
// goes to +0x00, zero to +0x04, and sixteen bytes are copied out of the
// argument into +0x08.
//
// WHY THE ARGUMENT IS A BINDING AND NOT ANOTHER WRAPPER.  The source is read
// at +0x00, +0x04, +0x08 and +0x0C -- from the argument's own base, not from
// +0x08 -- so it is not a copy constructor taking `const Wrapper &`.  It is the
// wrapper being built around a bound-method object of exactly the shape the 82
// constructors in FunctorBindConstructors.cpp produce: {object at +0x00,
// unmodelled +0x04, code +0x08, delta +0x0C}, sixteen bytes.  The destination
// is the same sub-object the invoker at 0x0050DB20 dispatches through --
// `mov ecx,[eax+0x14] / add ecx,[eax+8] / jmp [eax+0x10]`, i.e. object +0x08,
// code +0x10, delta +0x14 in wrapper coordinates -- so the binding lands at
// wrapper +0x08 and the four dwords line up one for one.
//
// WHY THE LEADING TWO DWORDS ARE A BASE.  FunctorBindInvokers.cpp records the
// measurement: MSVC 7.1 places a sub-object holding a `__multiple_inheritance`
// pointer-to-member eight bytes further along than the naive count when the
// enclosing class declares its own first virtual, which emits [eax+0x1C] and
// [eax+0x18] instead of retail's [eax+0x14] and [eax+0x10].  Splitting the
// vftable slot and the unmodelled dword into a base fixes the layout, and this
// constructor is what gives that base a body: the base zeroes the unmodelled
// dword, and the derived vftable store that follows is the one that survives
// -- MSVC drops the base's own vftable store as dead, which is why retail
// writes +0x04 before +0x00.
//
// WHY THE MEMBER COPY GOES THROUGH ecx.  `lea ecx,[eax+8]` followed by stores
// based on ecx is an inlined __thiscall copy constructor for the binding
// sub-object, not a memberwise store sequence off `this`; writing the member
// initialiser as `m_binding( binding )` reproduces it, and the four dwords move
// in declaration order.
//
// WHY THE COPIES ARE NOT FOLDED, AND WHY THE NAMES ARE ADDRESS-DERIVED: as in
// FunctorBindConstructors.cpp.  41 distinct addresses, 41 separate template
// instantiations, and no surviving name for the class -- the only RTTI
// descriptor the framework leaves in the image is `.?AVFunctorNotSet@@`.

class __multiple_inheritance FunctorTarget;

typedef void (FunctorTarget::*FunctorMethod)(void);

struct FunctorBinding
{
	FunctorTarget *m_target;
	unsigned int   m_unmodelled_04;
	FunctorMethod  m_method;
};

class FunctorWrapperHead
{
public:
	FunctorWrapperHead() : m_unmodelled_04( 0 ) {}

	virtual void functorWrapperAnchor();

	unsigned int m_unmodelled_04;
};

#define BFME_FUNCTOR_WRAPPER_CTOR( NAME )                                     \
	class NAME : public FunctorWrapperHead                                    \
	{                                                                         \
	public:                                                                   \
		NAME( const FunctorBinding &binding );                                \
                                                                              \
		FunctorBinding m_binding;                                             \
	};                                                                        \
	NAME::NAME( const FunctorBinding &binding ) : m_binding( binding ) {}

BFME_FUNCTOR_WRAPPER_CTOR( Rva0050DAE0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0050DB30FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0050DB80FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0050E8B0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0050E900FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0050E950FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva005119A0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva005119F0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva00511A40FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva005179D0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva00517A20FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0051E3E0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0051E430FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0051E480FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0051E4D0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0051E520FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0052B6E0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0052B730FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0052B780FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva00538B80FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva00538BD0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0055C5F0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0055C640FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0055EDB0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0055EE00FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0055EE50FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva00569C30FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva00569C80FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0056C9A0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0056C9F0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0056CA40FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0056CA90FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva00571730FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva00571780FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva005717D0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0057A020FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0057A070FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0057A0C0FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0058D220FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva0058D270FunctorWrapper )
BFME_FUNCTOR_WRAPPER_CTOR( Rva00599630FunctorWrapper )
