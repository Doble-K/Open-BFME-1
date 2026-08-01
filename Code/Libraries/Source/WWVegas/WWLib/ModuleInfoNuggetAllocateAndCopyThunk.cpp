struct ModuleInfo
{
	struct Nugget
	{
	};
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
			_emit 0FDh
			_emit 09Fh
			_emit 073h
			_emit 000h
		}
	}

	template ModuleInfo::Nugget *vector<ModuleInfo::Nugget,
		allocator<ModuleInfo::Nugget> >::_M_allocate_and_copy<ModuleInfo::Nugget const *>(
		unsigned int, ModuleInfo::Nugget const *, ModuleInfo::Nugget const *);
}
