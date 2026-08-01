class W3DAnimationInfo
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
	};

	template <class Type, class Allocator>
	template <class Iterator>
	__declspec(naked) Type *vector<Type, Allocator>::_M_allocate_and_copy(
		unsigned int, Iterator, Iterator)
	{
		__asm {
			_emit 0E9h
			_emit 036h
			_emit 07Ch
			_emit 037h
			_emit 000h
		}
	}

	template W3DAnimationInfo *vector<W3DAnimationInfo,
		allocator<W3DAnimationInfo> >::_M_allocate_and_copy<W3DAnimationInfo const *>(
		unsigned int, W3DAnimationInfo const *, W3DAnimationInfo const *);
}
