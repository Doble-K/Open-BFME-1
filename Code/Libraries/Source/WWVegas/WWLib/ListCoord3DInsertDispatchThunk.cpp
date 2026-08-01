struct Coord3D
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
			_emit 0D4h
			_emit 0D3h
			_emit 00Ah
			_emit 000h
		}
	}
}

template __declspec(naked) void _STL::list<Coord3D, _STL::allocator<Coord3D> >::_M_insert_dispatch<_STL::_List_iterator<Coord3D, _STL::_Const_traits<Coord3D> > >(_STL::_List_iterator<Coord3D, _STL::_Nonconst_traits<Coord3D> >, _STL::_List_iterator<Coord3D, _STL::_Const_traits<Coord3D> >, _STL::_List_iterator<Coord3D, _STL::_Const_traits<Coord3D> >, const _STL::__false_type &);
