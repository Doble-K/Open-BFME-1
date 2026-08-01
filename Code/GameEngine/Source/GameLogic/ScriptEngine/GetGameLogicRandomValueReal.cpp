// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

__declspec(naked) float GetGameLogicRandomValueReal(float, float, char *, int)
{
	__asm {
		_emit 0E9h
		_emit 026h
		_emit 0A1h
		_emit 006h
		_emit 000h
	}
}
