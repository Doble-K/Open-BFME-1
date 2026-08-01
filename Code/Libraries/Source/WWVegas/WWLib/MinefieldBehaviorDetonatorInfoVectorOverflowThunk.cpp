struct MinefieldBehavior
{
	struct DetonatorInfo
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

	__declspec(naked) void vector<MinefieldBehavior::DetonatorInfo, allocator<MinefieldBehavior::DetonatorInfo> >::_M_insert_overflow(
		MinefieldBehavior::DetonatorInfo *, const MinefieldBehavior::DetonatorInfo &, const __false_type &, unsigned int, bool)
	{
		__asm {
			_emit 0E9h
			_emit 098h
			_emit 0F4h
			_emit 074h
			_emit 000h
		}
	}
}
