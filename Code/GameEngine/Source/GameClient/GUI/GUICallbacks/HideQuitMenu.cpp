// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

__declspec(naked) void HideQuitMenu()
{
	__asm {
		_emit 0A1h
		_emit 0D4h
		_emit 04Ah
		_emit 02Fh
		_emit 001h
		_emit 085h
		_emit 0C0h
		_emit 074h
		_emit 00Bh
		_emit 08Bh
		_emit 00Dh
		_emit 0E8h
		_emit 019h
		_emit 02Fh
		_emit 001h
		_emit 0E9h
		_emit 03Eh
		_emit 0B5h
		_emit 0ACh
		_emit 0FFh
		_emit 0C3h
	}
}

