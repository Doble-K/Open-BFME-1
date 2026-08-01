class W3DAnimationInfo
{
};

namespace _STL
{
	struct __false_type
	{
	};

	template <class Type>
	class allocator
	{
	};

	template <class Type, class Allocator>
	class vector
	{
	protected:
		void _M_insert_overflow(Type *, const Type &, const __false_type &, unsigned int, bool);
	};

	__declspec(naked) void vector<W3DAnimationInfo, allocator<W3DAnimationInfo> >::_M_insert_overflow(
		W3DAnimationInfo *, const W3DAnimationInfo &, const __false_type &, unsigned int, bool)
	{
		__asm {
			_emit 0E9h
			_emit 007h
			_emit 010h
			_emit 075h
			_emit 000h
		}
	}
}
