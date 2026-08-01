struct ModelConditionInfo
{
	struct HideShowSubObjInfo
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
			_emit 012h
			_emit 03Fh
			_emit 038h
			_emit 000h
		}
	}

	template ModelConditionInfo::HideShowSubObjInfo *vector<
		ModelConditionInfo::HideShowSubObjInfo,
		allocator<ModelConditionInfo::HideShowSubObjInfo>
	>::_M_allocate_and_copy<ModelConditionInfo::HideShowSubObjInfo const *>(
		unsigned int, ModelConditionInfo::HideShowSubObjInfo const *,
		ModelConditionInfo::HideShowSubObjInfo const *);
}
