namespace _STL
{
	template <class First, class Second>
	struct pair
	{
	};

	template <class Value>
	struct _Rb_tree_node
	{
	};

	template <class Value>
	struct _Select1st
	{
	};

	template <class Type>
	struct less
	{
	};

	template <class Type>
	class allocator
	{
	};

	template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	class _Rb_tree
	{
		_Rb_tree_node<Value> *_M_copy(_Rb_tree_node<Value> *, _Rb_tree_node<Value> *);
		void _M_erase(_Rb_tree_node<Value> *);
	};

	template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	__declspec(naked) _Rb_tree_node<Value> *_Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::_M_copy(_Rb_tree_node<Value> *, _Rb_tree_node<Value> *)
	{
		__asm {
			_emit 0E9h
			_emit 0B8h
			_emit 080h
			_emit 006h
			_emit 000h
		}
	}

	typedef pair<int const, unsigned int> IntPair;
	template __declspec(naked) _Rb_tree_node<IntPair> *_Rb_tree<int, IntPair, _Select1st<IntPair>, less<int>, allocator<IntPair> >::_M_copy(_Rb_tree_node<IntPair> *, _Rb_tree_node<IntPair> *);

	template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	__declspec(naked) void _Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::_M_erase(_Rb_tree_node<Value> *)
	{
		__asm {
			_emit 0E9h
			_emit 02Dh
			_emit 01Fh
			_emit 006h
			_emit 000h
		}
	}

	template __declspec(naked) void _Rb_tree<int, IntPair, _Select1st<IntPair>, less<int>, allocator<IntPair> >::_M_erase(_Rb_tree_node<IntPair> *);
}
