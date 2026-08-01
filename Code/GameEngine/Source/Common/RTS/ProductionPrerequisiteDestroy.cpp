// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class ProductionPrerequisite;

namespace _STL
{
	template <class T>
	__declspec(naked) void _Destroy(T, T)
	{
		__asm {
			_emit 0E9h
			_emit 0C4h
			_emit 072h
			_emit 039h
			_emit 000h
		}
	}

	template void _Destroy<ProductionPrerequisite *>(ProductionPrerequisite *, ProductionPrerequisite *);
}
