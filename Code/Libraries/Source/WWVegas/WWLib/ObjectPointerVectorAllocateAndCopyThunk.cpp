class Object
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
			_emit 0C0h
			_emit 0ACh
			_emit 045h
			_emit 000h
		}
	}

	template Object **vector<Object *, allocator<Object *> >::_M_allocate_and_copy<Object * const *>(
		unsigned int, Object * const *, Object * const *);
}
