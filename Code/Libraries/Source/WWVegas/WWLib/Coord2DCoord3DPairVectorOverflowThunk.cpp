struct ICoord2D
{
};

struct Coord3D
{
};

namespace _STL
{
	template <class First, class Second>
	struct pair
	{
	};

	template <class Type>
	class allocator
	{
	};

	struct __false_type
	{
	};

	template <class Type, class Allocator>
	class vector
	{
	protected:
		void _M_insert_overflow(Type *, const Type &, const __false_type &, unsigned int, bool);
	};

	__declspec(naked) void vector<pair<ICoord2D, Coord3D>, allocator<pair<ICoord2D, Coord3D> > >::_M_insert_overflow(
		pair<ICoord2D, Coord3D> *, const pair<ICoord2D, Coord3D> &, const __false_type &, unsigned int, bool)
	{
		__asm {
			_emit 0E9h
			_emit 019h
			_emit 027h
			_emit 02Eh
			_emit 000h
		}
	}
}
