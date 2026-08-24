// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport _Rb_tree<K,V>::insert_unique(const value_type &), the
// unsigned-keyed shape, 23 bodies of 145 bytes each.  Every one of them
// carried only a machine byte-dump row.
//
// insert_unique walks from the root taking the left child while the incoming
// key compares below the node's own and the right child otherwise, remembers
// the last node it went left from, then re-compares against that node's
// predecessor to decide whether the key is already present.  Only on a miss
// does it hand the position pair to _M_insert, which is where the node is
// allocated -- so nothing in these 145 bytes depends on the mapped type or on
// the node width.  The one axis the bytes DO fix is the signedness of the key
// comparison: retail emits `setb` here, so the key is an unsigned 32-bit
// scalar (or a pointer).
// The signed shape lives in RvaTreeInsertUniqueSigned.cpp.
//
// Identity is not recoverable from a body that touches only the key.  The key
// is modelled as the plain unsigned int the comparison proves it to be, and the
// mapped type -- which the bytes never read -- is named for the address of the
// body so each instantiation gets its own decorated name.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

struct Rva00076190Value
{
	int m_body;
};

typedef _STL::pair<const unsigned int, Rva00076190Value> Rva00076190Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva00076190Pair,
	_STL::_Select1st<Rva00076190Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva00076190Pair> > Rva00076190Tree;

template _STL::pair<Rva00076190Tree::iterator, bool>
Rva00076190Tree::insert_unique( const Rva00076190Pair & );

struct Rva00076F80Value
{
	int m_body;
};

typedef _STL::pair<const unsigned int, Rva00076F80Value> Rva00076F80Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva00076F80Pair,
	_STL::_Select1st<Rva00076F80Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva00076F80Pair> > Rva00076F80Tree;

template _STL::pair<Rva00076F80Tree::iterator, bool>
Rva00076F80Tree::insert_unique( const Rva00076F80Pair & );

struct Rva00077040Value
{
	int m_body;
};

typedef _STL::pair<const unsigned int, Rva00077040Value> Rva00077040Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva00077040Pair,
	_STL::_Select1st<Rva00077040Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva00077040Pair> > Rva00077040Tree;

template _STL::pair<Rva00077040Tree::iterator, bool>
Rva00077040Tree::insert_unique( const Rva00077040Pair & );

struct Rva000E9850Value
{
	int m_body;
};

typedef _STL::pair<const unsigned int, Rva000E9850Value> Rva000E9850Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva000E9850Pair,
	_STL::_Select1st<Rva000E9850Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva000E9850Pair> > Rva000E9850Tree;

template _STL::pair<Rva000E9850Tree::iterator, bool>
Rva000E9850Tree::insert_unique( const Rva000E9850Pair & );

struct Rva0013FA60Value
{
	int m_body;
};

typedef _STL::pair<const unsigned int, Rva0013FA60Value> Rva0013FA60Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva0013FA60Pair,
	_STL::_Select1st<Rva0013FA60Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva0013FA60Pair> > Rva0013FA60Tree;

template _STL::pair<Rva0013FA60Tree::iterator, bool>
Rva0013FA60Tree::insert_unique( const Rva0013FA60Pair & );

struct Rva0021BE20Value
{
	int m_body;
};

typedef _STL::pair<const unsigned int, Rva0021BE20Value> Rva0021BE20Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva0021BE20Pair,
	_STL::_Select1st<Rva0021BE20Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva0021BE20Pair> > Rva0021BE20Tree;

template _STL::pair<Rva0021BE20Tree::iterator, bool>
Rva0021BE20Tree::insert_unique( const Rva0021BE20Pair & );

struct Rva00223FA0Value
{
	int m_body;
};

typedef _STL::pair<const unsigned int, Rva00223FA0Value> Rva00223FA0Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva00223FA0Pair,
	_STL::_Select1st<Rva00223FA0Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva00223FA0Pair> > Rva00223FA0Tree;

template _STL::pair<Rva00223FA0Tree::iterator, bool>
Rva00223FA0Tree::insert_unique( const Rva00223FA0Pair & );

struct Rva0025BD30Value
{
	int m_body;
};

typedef _STL::pair<const unsigned int, Rva0025BD30Value> Rva0025BD30Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva0025BD30Pair,
	_STL::_Select1st<Rva0025BD30Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva0025BD30Pair> > Rva0025BD30Tree;

template _STL::pair<Rva0025BD30Tree::iterator, bool>
Rva0025BD30Tree::insert_unique( const Rva0025BD30Pair & );

struct Rva00296ED0Value
{
	int m_body;
};

typedef _STL::pair<const unsigned int, Rva00296ED0Value> Rva00296ED0Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva00296ED0Pair,
	_STL::_Select1st<Rva00296ED0Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva00296ED0Pair> > Rva00296ED0Tree;

template _STL::pair<Rva00296ED0Tree::iterator, bool>
Rva00296ED0Tree::insert_unique( const Rva00296ED0Pair & );

struct Rva002A1E90Value
{
	int m_body;
};

typedef _STL::pair<const unsigned int, Rva002A1E90Value> Rva002A1E90Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva002A1E90Pair,
	_STL::_Select1st<Rva002A1E90Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva002A1E90Pair> > Rva002A1E90Tree;

template _STL::pair<Rva002A1E90Tree::iterator, bool>
Rva002A1E90Tree::insert_unique( const Rva002A1E90Pair & );

struct Rva0036ED40Value
{
	int m_body;
};

typedef _STL::pair<const unsigned int, Rva0036ED40Value> Rva0036ED40Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva0036ED40Pair,
	_STL::_Select1st<Rva0036ED40Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva0036ED40Pair> > Rva0036ED40Tree;

template _STL::pair<Rva0036ED40Tree::iterator, bool>
Rva0036ED40Tree::insert_unique( const Rva0036ED40Pair & );

struct Rva003DBF80Value
{
	int m_body;
};

typedef _STL::pair<const unsigned int, Rva003DBF80Value> Rva003DBF80Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva003DBF80Pair,
	_STL::_Select1st<Rva003DBF80Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva003DBF80Pair> > Rva003DBF80Tree;

template _STL::pair<Rva003DBF80Tree::iterator, bool>
Rva003DBF80Tree::insert_unique( const Rva003DBF80Pair & );

struct Rva003FF8D0Value
{
	int m_body;
};

typedef _STL::pair<const unsigned int, Rva003FF8D0Value> Rva003FF8D0Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva003FF8D0Pair,
	_STL::_Select1st<Rva003FF8D0Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva003FF8D0Pair> > Rva003FF8D0Tree;

template _STL::pair<Rva003FF8D0Tree::iterator, bool>
Rva003FF8D0Tree::insert_unique( const Rva003FF8D0Pair & );

struct Rva00405DB0Value
{
	int m_body;
};

typedef _STL::pair<const unsigned int, Rva00405DB0Value> Rva00405DB0Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva00405DB0Pair,
	_STL::_Select1st<Rva00405DB0Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva00405DB0Pair> > Rva00405DB0Tree;

template _STL::pair<Rva00405DB0Tree::iterator, bool>
Rva00405DB0Tree::insert_unique( const Rva00405DB0Pair & );

struct Rva0040AAD0Value
{
	int m_body;
};

typedef _STL::pair<const unsigned int, Rva0040AAD0Value> Rva0040AAD0Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva0040AAD0Pair,
	_STL::_Select1st<Rva0040AAD0Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva0040AAD0Pair> > Rva0040AAD0Tree;

template _STL::pair<Rva0040AAD0Tree::iterator, bool>
Rva0040AAD0Tree::insert_unique( const Rva0040AAD0Pair & );

struct Rva00442AB0Value
{
	int m_body;
};

typedef _STL::pair<const unsigned int, Rva00442AB0Value> Rva00442AB0Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva00442AB0Pair,
	_STL::_Select1st<Rva00442AB0Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva00442AB0Pair> > Rva00442AB0Tree;

template _STL::pair<Rva00442AB0Tree::iterator, bool>
Rva00442AB0Tree::insert_unique( const Rva00442AB0Pair & );

struct Rva004B0C80Value
{
	int m_body;
};

typedef _STL::pair<const unsigned int, Rva004B0C80Value> Rva004B0C80Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva004B0C80Pair,
	_STL::_Select1st<Rva004B0C80Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva004B0C80Pair> > Rva004B0C80Tree;

template _STL::pair<Rva004B0C80Tree::iterator, bool>
Rva004B0C80Tree::insert_unique( const Rva004B0C80Pair & );

struct Rva00586710Value
{
	int m_body;
};

typedef _STL::pair<const unsigned int, Rva00586710Value> Rva00586710Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva00586710Pair,
	_STL::_Select1st<Rva00586710Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva00586710Pair> > Rva00586710Tree;

template _STL::pair<Rva00586710Tree::iterator, bool>
Rva00586710Tree::insert_unique( const Rva00586710Pair & );

struct Rva005D2B10Value
{
	int m_body;
};

typedef _STL::pair<const unsigned int, Rva005D2B10Value> Rva005D2B10Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva005D2B10Pair,
	_STL::_Select1st<Rva005D2B10Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva005D2B10Pair> > Rva005D2B10Tree;

template _STL::pair<Rva005D2B10Tree::iterator, bool>
Rva005D2B10Tree::insert_unique( const Rva005D2B10Pair & );

struct Rva006A4630Value
{
	int m_body;
};

typedef _STL::pair<const unsigned int, Rva006A4630Value> Rva006A4630Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva006A4630Pair,
	_STL::_Select1st<Rva006A4630Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva006A4630Pair> > Rva006A4630Tree;

template _STL::pair<Rva006A4630Tree::iterator, bool>
Rva006A4630Tree::insert_unique( const Rva006A4630Pair & );

struct Rva006DE9B0Value
{
	int m_body;
};

typedef _STL::pair<const unsigned int, Rva006DE9B0Value> Rva006DE9B0Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva006DE9B0Pair,
	_STL::_Select1st<Rva006DE9B0Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva006DE9B0Pair> > Rva006DE9B0Tree;

template _STL::pair<Rva006DE9B0Tree::iterator, bool>
Rva006DE9B0Tree::insert_unique( const Rva006DE9B0Pair & );

struct Rva008FFE90Value
{
	int m_body;
};

typedef _STL::pair<const unsigned int, Rva008FFE90Value> Rva008FFE90Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva008FFE90Pair,
	_STL::_Select1st<Rva008FFE90Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva008FFE90Pair> > Rva008FFE90Tree;

template _STL::pair<Rva008FFE90Tree::iterator, bool>
Rva008FFE90Tree::insert_unique( const Rva008FFE90Pair & );

struct Rva0094CCF0Value
{
	int m_body;
};

typedef _STL::pair<const unsigned int, Rva0094CCF0Value> Rva0094CCF0Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva0094CCF0Pair,
	_STL::_Select1st<Rva0094CCF0Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva0094CCF0Pair> > Rva0094CCF0Tree;

template _STL::pair<Rva0094CCF0Tree::iterator, bool>
Rva0094CCF0Tree::insert_unique( const Rva0094CCF0Pair & );

