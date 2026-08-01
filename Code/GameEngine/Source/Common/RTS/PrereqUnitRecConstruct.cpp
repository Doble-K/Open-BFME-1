// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

namespace ProductionPrerequisite
{
	struct PrereqUnitRec;
}

namespace _STL
{
	template <class T, class U>
	__declspec(naked) void _Construct(T *, const U &)
	{
		__asm {
			_emit 0E9h
			_emit 0F4h
			_emit 09Dh
			_emit 055h
			_emit 000h
		}
	}

	template void _Construct<ProductionPrerequisite::PrereqUnitRec, ProductionPrerequisite::PrereqUnitRec>(ProductionPrerequisite::PrereqUnitRec *, const ProductionPrerequisite::PrereqUnitRec &);
}
