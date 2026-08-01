struct ModelConditionInfo
{
	struct HideShowSubObjInfo
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

	__declspec(naked) void vector<ModelConditionInfo::HideShowSubObjInfo, allocator<ModelConditionInfo::HideShowSubObjInfo> >::_M_insert_overflow(
		ModelConditionInfo::HideShowSubObjInfo *, const ModelConditionInfo::HideShowSubObjInfo &, const __false_type &, unsigned int, bool)
	{
		__asm {
			_emit 0E9h
			_emit 0DBh
			_emit 0EBh
			_emit 067h
			_emit 000h
		}
	}

	__declspec(naked) void vector<ModelConditionInfo::HideShowSubObjInfo, allocator<ModelConditionInfo::HideShowSubObjInfo> >::_M_clear()
	{
		__asm {
			_emit 0E9h
			_emit 0D3h
			_emit 0A8h
			_emit 039h
			_emit 000h
		}
	}
}
