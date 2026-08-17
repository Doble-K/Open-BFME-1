// cl: /DNDEBUG /MD /EHs-c-

// FILE: PeerThreadClearPlayerStats.cpp ///////////////////////////////////////
//
// PeerThreadClass::clearPlayerStats, retail 0x0064C640, and its neighbour
// clearServers, retail 0x006ABC00 -- the same inlined _Rb_tree::clear() on a
// third map, kept here because it is blocked on the same thing.
//
// PeerThread.cpp compiles this at 73 of 75 bytes; the two disagreements are the
// two member offsets, +0x94 and +0xa0 against the port's +0x98 and +0xa4.
// Everything ahead of the stats maps is four bytes wider there.  That is not
// fixable inside PeerThread.cpp: it owns 44 matched rows, and the drift is not
// uniform -- clearServers at 0x006ABC00 wants m_stagingServers at +0x1b8 where
// the same port puts it at +0x1fc, sixty-eight bytes out, so at least one more
// member disagreement sits between the two.  Only the two offsets this body
// proves are spelled here; the head is opaque filler.
//
// The map is STLport's _Rb_tree spelled out far enough to inline clear(): a
// header node pointer, a node count and an empty comparator, twelve bytes,
// which is exactly the stride between the two members.  The template arguments
// are carried in full because _M_erase is resolved by mangled name against
// reverse/symbols.csv, where it already sits at 0x0003120F.
//
///////////////////////////////////////////////////////////////////////////////

namespace _STL
{

template <class Type> class allocator {};
// A class and not a struct: the pinned _M_erase spells it V?$char_traits@D@,
// and U would be a different symbol.
template <class Type> class char_traits {};
template <class Char, class Traits, class Alloc> class basic_string {};
template <class First, class Second> struct pair {};
template <class Pair> struct _Select1st {};
template <class Type> struct less {};

struct _Rb_tree_node_base
{
	int _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};

template <class Value>
struct _Rb_tree_node : public _Rb_tree_node_base
{
	Value _M_value_field;
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:

	// STLport's clear().  The guard is on the count, and the three header links
	// are re-read through _M_header each time because _M_erase may have moved
	// nothing the compiler can prove.
	void clear()
	{
		if (_M_node_count != 0)
		{
			_M_erase((_Node *)(void *)_M_root());
			_M_leftmost() = _M_header;
			_M_root() = 0;
			_M_rightmost() = _M_header;
			_M_node_count = 0;
		}
	}

private:

	typedef _Rb_tree_node<Value> _Node;

	_Rb_tree_node_base *&_M_root() const { return _M_header->_M_parent; }
	_Rb_tree_node_base *&_M_leftmost() const { return _M_header->_M_left; }
	_Rb_tree_node_base *&_M_rightmost() const { return _M_header->_M_right; }

	// Declared, never defined: only the .obj is produced.
	void _M_erase(_Node *x);

	_Rb_tree_node_base *_M_header;
	unsigned int _M_node_count;
	Compare _M_key_compare;

};

}

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > BfmeStdString;
typedef _STL::pair<const BfmeStdString, int> BfmeStatPair;

typedef _STL::_Rb_tree<BfmeStdString,
											 BfmeStatPair,
											 _STL::_Select1st<BfmeStatPair>,
											 _STL::less<BfmeStdString>,
											 _STL::allocator<BfmeStatPair> > PlayerStatMap;

struct _SBServer;
typedef _STL::pair<const int, _SBServer *> BfmeServerPair;

typedef _STL::_Rb_tree<int,
											 BfmeServerPair,
											 _STL::_Select1st<BfmeServerPair>,
											 _STL::less<int>,
											 _STL::allocator<BfmeServerPair> > StagingServerMap;

// GroupRoom is 1 and StagingRoom is 2: retail decrements the argument once for
// the first arm and once more for the second.
enum RoomType { UnknownRoom, GroupRoom, StagingRoom };

class PeerThreadClass
{
public:

	void clearPlayerStats( RoomType roomType );
	void clearServers( void );

private:

	char m_bfmeHead[0x94];
	PlayerStatMap m_groupRoomStats;					// @0x94
	PlayerStatMap m_stagingRoomStats;				// @0xa0
	char m_bfmeMiddle[0x1b8 - 0xac];
	StagingServerMap m_stagingServers;			// @0x1b8

};

void PeerThreadClass::clearPlayerStats( RoomType roomType )
{
	switch (roomType)
	{
		case GroupRoom:
			m_groupRoomStats.clear();
			break;
		case StagingRoom:
			m_stagingRoomStats.clear();
			break;
	}
}

// Retail 0x006ABC00.  The same clear(), on a map<Int, SBServer> at +0x1b8 --
// sixty-eight bytes ahead of where PeerThread.cpp's own layout puts it, which
// is the second, independent drift that keeps both of these out of that file.
void PeerThreadClass::clearServers( void )
{
	m_stagingServers.clear();
}
