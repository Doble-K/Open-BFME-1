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

	__declspec(naked) void vector<ModelConditionInfo::WeaponBarrelInfo, allocator<ModelConditionInfo::WeaponBarrelInfo> >::_M_insert_overflow(
		ModelConditionInfo::WeaponBarrelInfo *, const ModelConditionInfo::WeaponBarrelInfo &, const __false_type &, unsigned int, bool)
	{
		__asm {
			_emit 0E9h
			_emit 0C9h
			_emit 0FBh
			_emit 072h
			_emit 000h
		}
	}
}
