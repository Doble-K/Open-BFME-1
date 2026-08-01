// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

__declspec(naked) void HideInGameChat()
{
	__asm {
		_emit 0E9h
		_emit 0E8h
		_emit 090h
		_emit 04Fh
		_emit 000h
	}
}
