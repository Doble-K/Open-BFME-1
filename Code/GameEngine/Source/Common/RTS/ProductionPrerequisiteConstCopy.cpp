// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class ProductionPrerequisite;

namespace _STL
{
	struct random_access_iterator_tag;

	template <class In, class Out, class Distance>
	__declspec(naked) Out __copy(In, In, Out, const random_access_iterator_tag &, Distance *)
	{
		__asm {
			_emit 0E9h
			_emit 014h
			_emit 0E8h
			_emit 03Ah
			_emit 000h
		}
	}

	template ProductionPrerequisite *__copy<const ProductionPrerequisite *, ProductionPrerequisite *, int>(const ProductionPrerequisite *, const ProductionPrerequisite *, ProductionPrerequisite *, const random_access_iterator_tag &, int *);
}
