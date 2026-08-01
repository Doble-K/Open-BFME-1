class ProductionPrerequisite
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
			_emit 0FAh
			_emit 01Ah
			_emit 03Ah
			_emit 000h
		}
	}

	template ProductionPrerequisite *vector<ProductionPrerequisite,
		allocator<ProductionPrerequisite> >::_M_allocate_and_copy<ProductionPrerequisite const *>(
		unsigned int, ProductionPrerequisite const *, ProductionPrerequisite const *);
}
