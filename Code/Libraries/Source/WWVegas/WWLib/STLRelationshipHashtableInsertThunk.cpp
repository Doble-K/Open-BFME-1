enum Relationship
{
};

namespace _STL
{
template <class First, class Second>
struct pair
{
};

template <class T>
struct hash
{
};

template <class T>
struct _Select1st
{
};

template <class T>
struct equal_to
{
};

template <class T>
class allocator
{
};

template <class Value, class Key, class Hash, class Extract, class Equal, class Alloc>
class hashtable
{
public:
	Value &_M_insert(const Value &);
};

class RelationshipHashtableInsertShim
{
public:
	pair<const int, Relationship> &insert(const pair<const int, Relationship> &v);
};

template <class Value, class Key, class Hash, class Extract, class Equal, class Alloc>
Value &hashtable<Value, Key, Hash, Extract, Equal, Alloc>::_M_insert(const Value &v)
{
	return (Value &)((RelationshipHashtableInsertShim *)this)->insert((const pair<const int, Relationship> &)v);
}
}

typedef _STL::pair<const int, Relationship> RelationshipPair;
typedef _STL::hashtable<RelationshipPair, int, _STL::hash<int>, _STL::_Select1st<RelationshipPair>, _STL::equal_to<int>, _STL::allocator<RelationshipPair> > RelationshipHashtable;
template RelationshipPair &RelationshipHashtable::_M_insert(const RelationshipPair &);
