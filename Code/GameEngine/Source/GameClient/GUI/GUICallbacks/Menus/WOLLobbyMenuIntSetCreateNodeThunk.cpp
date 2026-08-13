// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: _Rb_tree<int,int,_Identity<int>,less<int>,allocator<int>>::_M_create_node
// (std::set<int>::_M_create_node, as instantiated from WOLLobbyMenu.cpp)
// Retail: operator new(0x14); construct int value at +0x10; return node.

void *__cdecl operator new(unsigned int);
inline void *__cdecl operator new(unsigned int, void *p) { return p; }

namespace _STL
{
template <class Type>
class allocator
{
};

template <class Type>
struct _Identity
{
};

template <class Type>
struct less
{
};

template <class Type>
struct _Rb_tree_node
{
	int color;
	void *parent;
	void *left;
	void *right;
	Type value;
};

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
class _Rb_tree
{
protected:
	_Rb_tree_node<Value> *_M_create_node(Value const &);
};

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
_Rb_tree_node<Value> *_Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::_M_create_node(Value const &x)
{
	_Rb_tree_node<Value> *node =
		(_Rb_tree_node<Value> *)operator new(sizeof(_Rb_tree_node<Value>));
	::new (&node->value) Value(x);
	return node;
}

template _Rb_tree_node<int> *_Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> >::_M_create_node(int const &);
}
