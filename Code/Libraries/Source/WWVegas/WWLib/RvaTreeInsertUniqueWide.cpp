// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport _Rb_tree<StringBase<unsigned short>, V>::insert_unique
// for the two wide-string-keyed trees, plain and hinted -- four bodies that
// carried only a machine byte-dump row.
//
// Same construction as the AsciiString-keyed files next to this one: the tree
// spelling comes from the four-argument _M_insert each body calls, which states
// the key by the compare it reaches and the mapped width by the node it
// allocates, so the mapped types are named for the _M_insert's address.
//
// The comparison is the wide sibling of AsciiString::compare and it does not
// use memcmp: it walks the two buffers a halfword at a time and takes the first
// differing character's difference, with the length difference as the tiebreak.
// Both hinted bodies call it out of line at 0x0005FFA0 at every one of their
// comparison sites, which is what this file reproduces.
//
// The two PLAIN bodies at 0x0054F000 and 0x0068FBE0 are NOT landed here.  They
// are the same shape plus one expansion of that comparison, inlined at the
// comparison inside the descent loop and called at the one after it -- 328
// bytes against the 193 this file emits.  MSVC 7.1 will not inline a function
// containing a loop: neither `inline`, an in-class definition nor
// __forceinline gets the expansion, and hand-inlining it puts the expansion at
// both sites.  Whatever spelling retail used, it is not a call to this
// function, and the two rows stay byte-dumps until it is found.
//
// StringBase is spelled here rather than included, because the shim's copy
// keeps its constructors private for AsciiString's benefit and the key of a
// tree has to be constructible.  Only the layout matters to these bodies: the
// header pointer at +0, the length as a halfword at +4 of the header and the
// characters at +8.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

template <typename T>
class StringBase
{
public:
	StringBase();
	StringBase( const StringBase<T> &src );
	~StringBase();

	int compare( const StringBase<T> &str ) const
	{
		int thatLen = str.m_data ? str.m_data->length : 0;
		const T *thatData = str.m_data ? &str.m_data->data[ 0 ] : (const T *)L"";
		int thisLen = m_data ? m_data->length : 0;
		const T *thisData = m_data ? &m_data->data[ 0 ] : (const T *)L"";
		int n = thisLen < thatLen ? thisLen : thatLen;
		int c = 0;
		while ( n > 0 )
		{
			if ( *thisData != *thatData )
			{
				c = *thisData - *thatData;
				break;
			}
			++thisData;
			++thatData;
			--n;
		}
		if ( c != 0 )
			return c;
		return thisLen - thatLen;
	}

	struct Header
	{
		int ref_count;					// +0x00
		unsigned short length;			// +0x04
		unsigned short capacity;		// +0x06
		T data[ 1 ];					// +0x08
	};

	Header *m_data;						// +0x00
};

typedef StringBase<unsigned short> BfmeWideString;

namespace _STL
{
template <> struct less<BfmeWideString>
{
	bool operator()( const BfmeWideString &left, const BfmeWideString &right ) const
	{
		return left.compare( right ) < 0;
	}
};
}

struct Rva0054EF10Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const BfmeWideString, Rva0054EF10Value> Rva0054EF10Pair;

typedef _STL::_Rb_tree<BfmeWideString, Rva0054EF10Pair, _STL::_Select1st<Rva0054EF10Pair>,
	_STL::less<BfmeWideString>, _STL::allocator<Rva0054EF10Pair> > Rva0054EF10Tree;

// retail 0x0054F000, inserting through the _M_insert at 0x0054EF10
template _STL::pair<Rva0054EF10Tree::iterator, bool>
Rva0054EF10Tree::insert_unique( const Rva0054EF10Pair & );

// retail 0x0054F3F0, hinting into the same _M_insert
template Rva0054EF10Tree::iterator
Rva0054EF10Tree::insert_unique( Rva0054EF10Tree::iterator, const Rva0054EF10Pair & );

struct Rva0068FAF0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const BfmeWideString, Rva0068FAF0Value> Rva0068FAF0Pair;

typedef _STL::_Rb_tree<BfmeWideString, Rva0068FAF0Pair, _STL::_Select1st<Rva0068FAF0Pair>,
	_STL::less<BfmeWideString>, _STL::allocator<Rva0068FAF0Pair> > Rva0068FAF0Tree;

// retail 0x0068FBE0, inserting through the _M_insert at 0x0068FAF0
template _STL::pair<Rva0068FAF0Tree::iterator, bool>
Rva0068FAF0Tree::insert_unique( const Rva0068FAF0Pair & );

// retail 0x0068FF60, hinting into the same _M_insert
template Rva0068FAF0Tree::iterator
Rva0068FAF0Tree::insert_unique( Rva0068FAF0Tree::iterator, const Rva0068FAF0Pair & );
