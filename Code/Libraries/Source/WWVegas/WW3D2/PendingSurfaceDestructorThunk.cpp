// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Render2DSentenceClass
{
	struct PendingSurfaceStruct
	{
		~PendingSurfaceStruct();
	};
};

__declspec(naked) Render2DSentenceClass::PendingSurfaceStruct::~PendingSurfaceStruct()
{
	__asm {
		_emit 0E9h
		_emit 045h
		_emit 0A2h
		_emit 05Dh
		_emit 000h
	}
}
