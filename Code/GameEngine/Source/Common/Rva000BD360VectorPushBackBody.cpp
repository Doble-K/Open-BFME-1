// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: STLport vector<T>::push_back over a 112-byte element, retail
// 0x000BD360, 62 bytes. The body carried only a machine byte-dump row and no name.
//
// Two paths and nothing else: with room left it constructs at the finish pointer
// through the ILT at 0x0000A97A and steps the pointer by the element width;
// with none it hands the whole thing to _M_insert_overflow through the ILT at
// 0x00025275 with a fill length of one and the at-end flag set. Retail reloads
// the finish pointer from the object after the construct call rather than
// reusing the copy it already had, which is what a plain `++_M_finish` on a
// member produces.
//
// The empty dispatch tag is aliased onto the value parameter's own stack slot,
// the same trick the _M_insert_overflow family uses on its trailing bool.
//
// Identity is not recovered: the element width is the only axis, so the element
// is named for the address of the body and modelled by width.

struct P5Elem000BD360
{
	char m_body[ 0x70 ];
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

void __cdecl Bfme000BD360Construct( P5Elem000BD360 *destination, const P5Elem000BD360 &value );

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
		Bfme000BD360Construct( _M_finish, *value );
		++_M_finish;
	}
	else
	{
		_M_insert_overflow( _M_finish, *value, reinterpret_cast<const __false_type &>( value ), 1, true );
	}
}

template class vector<P5Elem000BD360, allocator<P5Elem000BD360> >;
}
