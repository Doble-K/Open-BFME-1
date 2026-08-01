// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class ModuleInfo
{
public:
	struct Nugget;
};

namespace _STL
{
	struct __false_type;

	template <class In, class Out>
	__declspec(naked) Out __uninitialized_copy(In, In, Out, const __false_type &)
	{
		__asm {
			_emit 0E9h
			_emit 06Fh
			_emit 02Eh
			_emit 075h
			_emit 000h
		}
	}

	template ModuleInfo::Nugget *__uninitialized_copy<const ModuleInfo::Nugget *, ModuleInfo::Nugget *>(const ModuleInfo::Nugget *, const ModuleInfo::Nugget *, ModuleInfo::Nugget *, const __false_type &);
}
