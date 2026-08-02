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

class HideShowSubObjInfoAllocateAndCopyShim
{
public:
	ModelConditionInfo::HideShowSubObjInfo *allocate_and_copy(unsigned int n, const ModelConditionInfo::HideShowSubObjInfo *first, const ModelConditionInfo::HideShowSubObjInfo *last);
};

template <class Type, class Allocator>
template <class Iterator>
Type *vector<Type, Allocator>::_M_allocate_and_copy(unsigned int n, Iterator first, Iterator last)
{
	return (Type *)((HideShowSubObjInfoAllocateAndCopyShim *)this)->allocate_and_copy(
		n,
		(const ModelConditionInfo::HideShowSubObjInfo *)first,
		(const ModelConditionInfo::HideShowSubObjInfo *)last);
}

template ModelConditionInfo::HideShowSubObjInfo *vector<
	ModelConditionInfo::HideShowSubObjInfo,
	allocator<ModelConditionInfo::HideShowSubObjInfo>
>::_M_allocate_and_copy<ModelConditionInfo::HideShowSubObjInfo const *>(
	unsigned int, ModelConditionInfo::HideShowSubObjInfo const *,
	ModelConditionInfo::HideShowSubObjInfo const *);
}
