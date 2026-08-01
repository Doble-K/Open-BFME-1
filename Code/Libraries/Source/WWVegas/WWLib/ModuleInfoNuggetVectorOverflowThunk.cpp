struct ModuleInfo
{
	struct Nugget
	{
	};
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
		void _M_clear();
	};

	__declspec(naked) void vector<ModuleInfo::Nugget, allocator<ModuleInfo::Nugget> >::_M_insert_overflow(
		ModuleInfo::Nugget *, const ModuleInfo::Nugget &, const __false_type &, unsigned int, bool)
	{
		__asm {
			_emit 0E9h
			_emit 0E0h
			_emit 000h
			_emit 076h
			_emit 000h
		}
	}

	__declspec(naked) void vector<ModuleInfo::Nugget, allocator<ModuleInfo::Nugget> >::_M_clear()
	{
		__asm {
			_emit 0E9h
			_emit 012h
			_emit 09Bh
			_emit 072h
			_emit 000h
		}
	}
}
