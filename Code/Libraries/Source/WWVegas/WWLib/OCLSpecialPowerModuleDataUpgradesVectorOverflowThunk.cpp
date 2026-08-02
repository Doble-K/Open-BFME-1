struct OCLSpecialPowerModuleData
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

class OCLSpecialPowerModuleDataUpgradesInsertOverflowShim
{
public:
	void insert_overflow(OCLSpecialPowerModuleData::Upgrades *pos, const OCLSpecialPowerModuleData::Upgrades &x, const __false_type &tag, unsigned int fill_len, bool at_end);
};

void vector<OCLSpecialPowerModuleData::Upgrades, allocator<OCLSpecialPowerModuleData::Upgrades> >::_M_insert_overflow(
	OCLSpecialPowerModuleData::Upgrades *pos, const OCLSpecialPowerModuleData::Upgrades &x, const __false_type &tag, unsigned int fill_len, bool at_end)
{
	((OCLSpecialPowerModuleDataUpgradesInsertOverflowShim *)this)->insert_overflow(pos, x, tag, fill_len, at_end);
}
}
