// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class ModuleInfo
{
public:
	struct Nugget;
};

namespace _STL
{
	struct random_access_iterator_tag;

	template <class In, class Out, class Distance>
	__declspec(naked) Out __copy(In, In, Out, const random_access_iterator_tag &, Distance *)
	{
		__asm {
			_emit 0E9h
			_emit 0E3h
			_emit 064h
			_emit 072h
			_emit 000h
		}
	}

	template ModuleInfo::Nugget *__copy<const ModuleInfo::Nugget *, ModuleInfo::Nugget *, int>(const ModuleInfo::Nugget *, const ModuleInfo::Nugget *, ModuleInfo::Nugget *, const random_access_iterator_tag &, int *);
}
