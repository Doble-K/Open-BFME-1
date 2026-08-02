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

class ModelConditionInfoHideShowSubObjInfoInsertOverflowShim
{
public:
	void insert_overflow(ModelConditionInfo::HideShowSubObjInfo *pos, const ModelConditionInfo::HideShowSubObjInfo &x, const __false_type &tag, unsigned int fill_len, bool at_end);
	void clear();
};

void vector<ModelConditionInfo::HideShowSubObjInfo, allocator<ModelConditionInfo::HideShowSubObjInfo> >::_M_insert_overflow(
	ModelConditionInfo::HideShowSubObjInfo *pos, const ModelConditionInfo::HideShowSubObjInfo &x, const __false_type &tag, unsigned int fill_len, bool at_end)
{
	((ModelConditionInfoHideShowSubObjInfoInsertOverflowShim *)this)->insert_overflow(pos, x, tag, fill_len, at_end);
}

void vector<ModelConditionInfo::HideShowSubObjInfo, allocator<ModelConditionInfo::HideShowSubObjInfo> >::_M_clear()
{
	((ModelConditionInfoHideShowSubObjInfoInsertOverflowShim *)this)->clear();
}
}
