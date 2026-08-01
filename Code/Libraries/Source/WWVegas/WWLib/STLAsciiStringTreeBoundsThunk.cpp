class AsciiString
{
};

namespace _STL
{
template<class T> struct _Identity { };
template<class T> struct less { };
template<class T> class allocator { };
template<class Value> struct _Rb_tree_node { };

template<class Key, class Value, class Select, class Less, class Alloc>
class _Rb_tree
{
	_Rb_tree_node<Value> *_M_lower_bound(const Key &) const;
	_Rb_tree_node<Value> *_M_upper_bound(const Key &) const;
};

template<class Key, class Value, class Select, class Less, class Alloc>
__declspec(naked) _Rb_tree_node<Value> *_Rb_tree<Key, Value, Select, Less, Alloc>::_M_lower_bound(const Key &) const
{
	__asm {
		_emit 0E9h
		_emit 0F5h
		_emit 0BBh
		_emit 062h
		_emit 000h
	}
}
}

typedef _STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>, _STL::less<AsciiString>, _STL::allocator<AsciiString> > AsciiTree;
template __declspec(naked) _STL::_Rb_tree_node<AsciiString> *AsciiTree::_M_lower_bound(const AsciiString &) const;

namespace _STL
{
template<class Key, class Value, class Select, class Less, class Alloc>
__declspec(naked) _Rb_tree_node<Value> *_Rb_tree<Key, Value, Select, Less, Alloc>::_M_upper_bound(const Key &) const
{
	__asm {
		_emit 0E9h
		_emit 0EDh
		_emit 079h
		_emit 006h
		_emit 000h
	}
}
}

template __declspec(naked) _STL::_Rb_tree_node<AsciiString> *AsciiTree::_M_upper_bound(const AsciiString &) const;
