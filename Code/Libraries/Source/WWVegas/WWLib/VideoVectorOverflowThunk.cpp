struct Video
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

	__declspec(naked) void vector<Video, allocator<Video> >::_M_insert_overflow(
		Video *, const Video &, const __false_type &, unsigned int, bool)
	{
		__asm {
			_emit 0E9h
			_emit 008h
			_emit 04Eh
			_emit 06Ch
			_emit 000h
		}
	}
}
