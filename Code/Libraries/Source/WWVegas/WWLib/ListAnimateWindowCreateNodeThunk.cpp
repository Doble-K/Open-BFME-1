class AnimateWindow
{
};

namespace _STL
{
	template <class Type>
	class allocator
	{
	};

	template <class Type>
	struct _List_node
	{
	};

	template <class Type, class Allocator>
	class list
	{
	protected:
		_List_node<Type> *_M_create_node(Type const &);
	};

	template <class Type, class Allocator>
	__declspec(naked) _List_node<Type> *list<Type, Allocator>::_M_create_node(Type const &)
	{
		__asm {
			_emit 0E9h
			_emit 0A5h
			_emit 0ADh
			_emit 043h
			_emit 000h
		}
	}

	template __declspec(naked) _List_node<AnimateWindow *> *list<AnimateWindow *, allocator<AnimateWindow *> >::_M_create_node(AnimateWindow * const &);
}
