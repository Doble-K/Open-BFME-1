class AsciiString
{
};
class ParticleSystemTemplate
{
};

namespace _STL
{
template <class First, class Second>
struct pair
{
};
template <class Value>
struct _Hashtable_node
{
};
template <class T>
struct _Select1st
{
};
template <class T>
class allocator
{
};

template <class Value, class Key, class Hash, class Select, class Equal, class Alloc>
class hashtable
{
	template <class SearchKey>
	_Hashtable_node<Value> *_M_find(SearchKey const &) const;
};

class ParticleSystemHashtableFindShim
{
public:
	_Hashtable_node<pair<const AsciiString, ParticleSystemTemplate *> > *find(AsciiString const &k) const;
};

template <class Value, class Key, class Hash, class Select, class Equal, class Alloc>
template <class SearchKey>
_Hashtable_node<Value> *hashtable<Value, Key, Hash, Select, Equal, Alloc>::_M_find(SearchKey const &k) const
{
	return (_Hashtable_node<Value> *)((ParticleSystemHashtableFindShim const *)this)->find((AsciiString const &)k);
}
}

namespace rts
{
template <class T>
struct hash
{
};
template <class T>
struct equal_to
{
};
}

typedef _STL::pair<const AsciiString, ParticleSystemTemplate *> ParticleSystemPair;
typedef _STL::hashtable<ParticleSystemPair, AsciiString, rts::hash<AsciiString>, _STL::_Select1st<ParticleSystemPair>, rts::equal_to<AsciiString>, _STL::allocator<ParticleSystemPair> > ParticleSystemHashtable;
template _STL::_Hashtable_node<ParticleSystemPair> *ParticleSystemHashtable::_M_find<AsciiString>(AsciiString const &) const;
