class Drawable
{
};

namespace _STL
{
	template<class T> class allocator { };
	template<class T> struct _Const_traits { };
	template<class T> struct _Nonconst_traits { };
	template<class T, class Traits> struct _List_iterator { };
	struct __false_type { };

	template<class Type, class Allocator>
	class list
	{
	public:
		template<class InputIterator>
		void _M_insert_dispatch(_List_iterator<Type, _Nonconst_traits<Type> >, InputIterator, InputIterator, const __false_type &);
	};

	template<class Type, class Allocator>
	template<class InputIterator>
	__declspec(naked) void list<Type, Allocator>::_M_insert_dispatch(_List_iterator<Type, _Nonconst_traits<Type> >, InputIterator, InputIterator, const __false_type &)
	{
		__asm {
			_emit 0E9h
			_emit 0AFh
			_emit 003h
			_emit 01Ch
			_emit 000h
		}
	}
}

template __declspec(naked) void _STL::list<Drawable *, _STL::allocator<Drawable *> >::_M_insert_dispatch<_STL::_List_iterator<Drawable *, _STL::_Const_traits<Drawable *> > >(_STL::_List_iterator<Drawable *, _STL::_Nonconst_traits<Drawable *> >, _STL::_List_iterator<Drawable *, _STL::_Const_traits<Drawable *> >, _STL::_List_iterator<Drawable *, _STL::_Const_traits<Drawable *> >, const _STL::__false_type &);
