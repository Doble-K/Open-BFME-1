struct ParticleSysBoneInfo
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
	protected:
		template <class Iterator>
		Type *_M_allocate_and_copy(unsigned int, Iterator, Iterator);
		void _M_clear();
	};

	template <class Type, class Allocator>
	template <class Iterator>
	__declspec(naked) Type *vector<Type, Allocator>::_M_allocate_and_copy(
		unsigned int, Iterator, Iterator)
	{
		__asm {
			_emit 0E9h
			_emit 051h
			_emit 0F7h
			_emit 007h
			_emit 000h
		}
	}

	template ParticleSysBoneInfo *vector<ParticleSysBoneInfo,
		allocator<ParticleSysBoneInfo> >::_M_allocate_and_copy<ParticleSysBoneInfo const *>(
		unsigned int, ParticleSysBoneInfo const *, ParticleSysBoneInfo const *);

	__declspec(naked) void vector<ParticleSysBoneInfo, allocator<ParticleSysBoneInfo> >::_M_clear()
	{
		__asm {
			_emit 0E9h
			_emit 02Dh
			_emit 0F1h
			_emit 009h
			_emit 000h
		}
	}
}
