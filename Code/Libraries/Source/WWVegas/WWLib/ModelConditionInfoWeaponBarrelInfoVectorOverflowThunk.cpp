struct ModelConditionInfo
{
	struct WeaponBarrelInfo
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

class ModelConditionInfoWeaponBarrelInfoInsertOverflowShim
{
public:
	void insert_overflow(ModelConditionInfo::WeaponBarrelInfo *pos, const ModelConditionInfo::WeaponBarrelInfo &x, const __false_type &tag, unsigned int fill_len, bool at_end);
};

void vector<ModelConditionInfo::WeaponBarrelInfo, allocator<ModelConditionInfo::WeaponBarrelInfo> >::_M_insert_overflow(
	ModelConditionInfo::WeaponBarrelInfo *pos, const ModelConditionInfo::WeaponBarrelInfo &x, const __false_type &tag, unsigned int fill_len, bool at_end)
{
	((ModelConditionInfoWeaponBarrelInfoInsertOverflowShim *)this)->insert_overflow(pos, x, tag, fill_len, at_end);
}
}
