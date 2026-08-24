// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: STLport vector<T>::push_back, 27 bodies of 62 bytes.  Every one
// carried only a machine byte-dump row; the same shape is already converted at
// 0x000BD360 and appears many times over in the ZH reference translation units.
//
// Two paths and nothing else.  With room left it constructs at the finish
// pointer and steps that pointer by the element width; with none it hands the
// whole thing to _M_insert_overflow with a fill length of one and the at-end
// flag set.  Retail reloads the finish pointer from the object after the
// construct call rather than reusing the copy it already had, which is what a
// plain `++_M_finish` on a member produces.
//
// The element width is the `add eax, N` that steps the finish pointer, and it
// is the only thing that varies across the 27: 20, 28, 36, 44, 56, 88, 92, 96, 108, 120, 140, 180, 184, 188, 220, 296, 496, 528.  Nothing else about the
// element is knowable -- the copy is a call -- so each is a byte array named
// for the address of its body.
//
// The empty dispatch tag is aliased onto the value parameter's own stack slot,
// the same trick the _M_insert_overflow family uses on its trailing bool.

struct Rva000FB210Element
{
	char m_body[ 96 ];
};

struct Rva00146FD0Element
{
	char m_body[ 36 ];
};

struct Rva001999C0Element
{
	char m_body[ 140 ];
};

struct Rva001D28F0Element
{
	char m_body[ 92 ];
};

struct Rva00244A80Element
{
	char m_body[ 28 ];
};

struct Rva00253630Element
{
	char m_body[ 44 ];
};

struct Rva00365020Element
{
	char m_body[ 180 ];
};

struct Rva00366890Element
{
	char m_body[ 88 ];
};

struct Rva003A35A0Element
{
	char m_body[ 184 ];
};

struct Rva003AC170Element
{
	char m_body[ 220 ];
};

struct Rva003B1230Element
{
	char m_body[ 20 ];
};

struct Rva003B2380Element
{
	char m_body[ 36 ];
};

struct Rva003BB540Element
{
	char m_body[ 20 ];
};

struct Rva00426C00Element
{
	char m_body[ 28 ];
};

struct Rva00607770Element
{
	char m_body[ 496 ];
};

struct Rva00608FE0Element
{
	char m_body[ 528 ];
};

struct Rva0061B4B0Element
{
	char m_body[ 36 ];
};

struct Rva006AACB0Element
{
	char m_body[ 120 ];
};

struct Rva006F2C70Element
{
	char m_body[ 56 ];
};

struct Rva00774090Element
{
	char m_body[ 56 ];
};

struct Rva00775FE0Element
{
	char m_body[ 20 ];
};

struct Rva00776030Element
{
	char m_body[ 20 ];
};

struct Rva00777E40Element
{
	char m_body[ 44 ];
};

struct Rva0077BFB0Element
{
	char m_body[ 108 ];
};

struct Rva0077C670Element
{
	char m_body[ 296 ];
};

struct Rva0077CC10Element
{
	char m_body[ 188 ];
};

struct Rva0081D280Element
{
	char m_body[ 28 ];
};

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type>
void __cdecl BfmeElementConstruct( Type *destination, const Type &value );

template <class Type, class Allocator>
class vector
{
public:
	void push_back( const Type *value );

protected:
	void _M_insert_overflow( Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd );

	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};

template <class Type, class Allocator>
void vector<Type, Allocator>::push_back( const Type *value )
{
	if ( _M_finish != _M_end_of_storage )
	{
		BfmeElementConstruct( _M_finish, *value );
		++_M_finish;
	}
	else
	{
		_M_insert_overflow( _M_finish, *value, reinterpret_cast<const __false_type &>( value ), 1, true );
	}
}

// retail 0x000FB210, a 96-byte element
template class vector<Rva000FB210Element, allocator<Rva000FB210Element> >;

// retail 0x00146FD0, a 36-byte element
template class vector<Rva00146FD0Element, allocator<Rva00146FD0Element> >;

// retail 0x001999C0, a 140-byte element
template class vector<Rva001999C0Element, allocator<Rva001999C0Element> >;

// retail 0x001D28F0, a 92-byte element
template class vector<Rva001D28F0Element, allocator<Rva001D28F0Element> >;

// retail 0x00244A80, a 28-byte element
template class vector<Rva00244A80Element, allocator<Rva00244A80Element> >;

// retail 0x00253630, a 44-byte element
template class vector<Rva00253630Element, allocator<Rva00253630Element> >;

// retail 0x00365020, a 180-byte element
template class vector<Rva00365020Element, allocator<Rva00365020Element> >;

// retail 0x00366890, a 88-byte element
template class vector<Rva00366890Element, allocator<Rva00366890Element> >;

// retail 0x003A35A0, a 184-byte element
template class vector<Rva003A35A0Element, allocator<Rva003A35A0Element> >;

// retail 0x003AC170, a 220-byte element
template class vector<Rva003AC170Element, allocator<Rva003AC170Element> >;

// retail 0x003B1230, a 20-byte element
template class vector<Rva003B1230Element, allocator<Rva003B1230Element> >;

// retail 0x003B2380, a 36-byte element
template class vector<Rva003B2380Element, allocator<Rva003B2380Element> >;

// retail 0x003BB540, a 20-byte element
template class vector<Rva003BB540Element, allocator<Rva003BB540Element> >;

// retail 0x00426C00, a 28-byte element
template class vector<Rva00426C00Element, allocator<Rva00426C00Element> >;

// retail 0x00607770, a 496-byte element
template class vector<Rva00607770Element, allocator<Rva00607770Element> >;

// retail 0x00608FE0, a 528-byte element
template class vector<Rva00608FE0Element, allocator<Rva00608FE0Element> >;

// retail 0x0061B4B0, a 36-byte element
template class vector<Rva0061B4B0Element, allocator<Rva0061B4B0Element> >;

// retail 0x006AACB0, a 120-byte element
template class vector<Rva006AACB0Element, allocator<Rva006AACB0Element> >;

// retail 0x006F2C70, a 56-byte element
template class vector<Rva006F2C70Element, allocator<Rva006F2C70Element> >;

// retail 0x00774090, a 56-byte element
template class vector<Rva00774090Element, allocator<Rva00774090Element> >;

// retail 0x00775FE0, a 20-byte element
template class vector<Rva00775FE0Element, allocator<Rva00775FE0Element> >;

// retail 0x00776030, a 20-byte element
template class vector<Rva00776030Element, allocator<Rva00776030Element> >;

// retail 0x00777E40, a 44-byte element
template class vector<Rva00777E40Element, allocator<Rva00777E40Element> >;

// retail 0x0077BFB0, a 108-byte element
template class vector<Rva0077BFB0Element, allocator<Rva0077BFB0Element> >;

// retail 0x0077C670, a 296-byte element
template class vector<Rva0077C670Element, allocator<Rva0077C670Element> >;

// retail 0x0077CC10, a 188-byte element
template class vector<Rva0077CC10Element, allocator<Rva0077CC10Element> >;

// retail 0x0081D280, a 28-byte element
template class vector<Rva0081D280Element, allocator<Rva0081D280Element> >;

}
