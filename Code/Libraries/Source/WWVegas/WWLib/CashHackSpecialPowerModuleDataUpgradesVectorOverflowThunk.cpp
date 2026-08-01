struct CashHackSpecialPowerModuleData
{
	struct Upgrades
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

	__declspec(naked) void vector<CashHackSpecialPowerModuleData::Upgrades, allocator<CashHackSpecialPowerModuleData::Upgrades> >::_M_insert_overflow(
		CashHackSpecialPowerModuleData::Upgrades *, const CashHackSpecialPowerModuleData::Upgrades &, const __false_type &, unsigned int, bool)
	{
		__asm {
			_emit 0E9h
			_emit 0DAh
			_emit 09Ch
			_emit 024h
			_emit 000h
		}
	}
}
