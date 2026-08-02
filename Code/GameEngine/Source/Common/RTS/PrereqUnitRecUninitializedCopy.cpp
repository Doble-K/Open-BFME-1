// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

namespace ProductionPrerequisite
{
	struct PrereqUnitRec;
}

namespace _STL
{
struct __false_type {};

template <class In, class Out>
Out __uninitialized_copy(In, In, Out, const __false_type &);

class PrereqUnitRecUninitializedCopyShim
{
public:
	static void *copy(void *first, void *last, void *result, const __false_type &);
};

template <class In, class Out>
Out __uninitialized_copy(In first, In last, Out result, const __false_type &tag)
{
	return (Out)PrereqUnitRecUninitializedCopyShim::copy((void *)first, (void *)last, (void *)result, tag);
}

template ProductionPrerequisite::PrereqUnitRec *__uninitialized_copy<const ProductionPrerequisite::PrereqUnitRec *, ProductionPrerequisite::PrereqUnitRec *>(const ProductionPrerequisite::PrereqUnitRec *, const ProductionPrerequisite::PrereqUnitRec *, ProductionPrerequisite::PrereqUnitRec *, const __false_type &);
}
