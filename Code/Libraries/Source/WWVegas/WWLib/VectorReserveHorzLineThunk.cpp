struct HorzLine
{
};

struct ICoord2D
{
};

namespace _STL
{
	template <class Type>
	class allocator
	{
	};

	template <class Type, class Allocator>
	class vector
	{
	public:
		void reserve(unsigned int);
		void resize(unsigned int);
	};

	template <class Type, class Allocator>
	__declspec(naked) void vector<Type, Allocator>::reserve(unsigned int)
	{
		__asm {
			_emit 0E9h
			_emit 006h
			_emit 0B1h
			_emit 005h
			_emit 000h
		}
	}

	template __declspec(naked) void vector<HorzLine, allocator<HorzLine> >::reserve(unsigned int);

	template <class Type, class Allocator>
	__declspec(naked) void vector<Type, Allocator>::resize(unsigned int)
	{
		__asm {
			_emit 0E9h
			_emit 080h
			_emit 007h
			_emit 045h
			_emit 000h
		}
	}

	template __declspec(naked) void vector<ICoord2D, allocator<ICoord2D> >::resize(unsigned int);
}
