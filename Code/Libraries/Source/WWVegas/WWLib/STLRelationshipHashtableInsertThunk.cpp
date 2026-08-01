enum Relationship
{
};

namespace _STL
{
template<class First, class Second>
struct pair
{
};

template<class T>
struct hash
{
};

template<class T>
struct _Select1st
{
};

template<class T>
struct equal_to
{
};

template<class T>
class allocator
{
};

template<class Value, class Key, class Hash, class Extract, class Equal, class Alloc>
class hashtable
{
public:
	Value &_M_insert(const Value &);
};

template<class Value, class Key, class Hash, class Extract, class Equal, class Alloc>
__declspec(naked) Value &hashtable<Value, Key, Hash, Extract, Equal, Alloc>::_M_insert(const Value &)
{
	__asm {
		_emit 0E9h
		_emit 053h
		_emit 05Dh
		_emit 078h
		_emit 000h
	}
}
}

typedef _STL::pair<const int, Relationship> RelationshipPair;
typedef _STL::hashtable<RelationshipPair, int, _STL::hash<int>, _STL::_Select1st<RelationshipPair>, _STL::equal_to<int>, _STL::allocator<RelationshipPair> > RelationshipHashtable;
template __declspec(naked) RelationshipPair &RelationshipHashtable::_M_insert(const RelationshipPair &);
