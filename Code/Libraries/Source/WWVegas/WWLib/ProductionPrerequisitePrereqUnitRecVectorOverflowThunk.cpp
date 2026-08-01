struct ProductionPrerequisite
{
	struct PrereqUnitRec
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
	};

	__declspec(naked) void vector<ProductionPrerequisite::PrereqUnitRec, allocator<ProductionPrerequisite::PrereqUnitRec> >::_M_insert_overflow(
		ProductionPrerequisite::PrereqUnitRec *, const ProductionPrerequisite::PrereqUnitRec &, const __false_type &, unsigned int, bool)
	{
		__asm {
			_emit 0E9h
			_emit 0D4h
			_emit 053h
			_emit 057h
			_emit 000h
		}
	}
}
