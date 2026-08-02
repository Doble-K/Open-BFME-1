// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class ModuleInfo
{
public:
	struct Nugget;
};

namespace _STL
{
struct __false_type {};

template <class In, class Out>
Out __uninitialized_copy(In, In, Out, const __false_type &);

class ModuleInfoNuggetUninitializedCopyShim
{
public:
	static void *copy(void *first, void *last, void *result, const __false_type &);
};

template <class In, class Out>
Out __uninitialized_copy(In first, In last, Out result, const __false_type &tag)
{
	return (Out)ModuleInfoNuggetUninitializedCopyShim::copy((void *)first, (void *)last, (void *)result, tag);
}

template ModuleInfo::Nugget *__uninitialized_copy<const ModuleInfo::Nugget *, ModuleInfo::Nugget *>(const ModuleInfo::Nugget *, const ModuleInfo::Nugget *, ModuleInfo::Nugget *, const __false_type &);
}
