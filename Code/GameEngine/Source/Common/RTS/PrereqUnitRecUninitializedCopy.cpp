// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

namespace ProductionPrerequisite
{
	struct PrereqUnitRec;
}

namespace _STL
{
	struct __false_type;

	template <class In, class Out>
	__declspec(naked) Out __uninitialized_copy(In, In, Out, const __false_type &)
	{
		__asm {
			_emit 0E9h
			_emit 0E7h
			_emit 03Eh
			_emit 039h
			_emit 000h
		}
	}

	template ProductionPrerequisite::PrereqUnitRec *__uninitialized_copy<const ProductionPrerequisite::PrereqUnitRec *, ProductionPrerequisite::PrereqUnitRec *>(const ProductionPrerequisite::PrereqUnitRec *, const ProductionPrerequisite::PrereqUnitRec *, ProductionPrerequisite::PrereqUnitRec *, const __false_type &);
}
