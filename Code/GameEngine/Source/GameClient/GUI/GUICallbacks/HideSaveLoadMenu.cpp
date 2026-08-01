// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

__declspec(naked) void HideSaveLoadMenu()
{
	__asm {
		_emit 0A1h
		_emit 040h
		_emit 04Bh
		_emit 02Fh
		_emit 001h
		_emit 085h
		_emit 0C0h
		_emit 074h
		_emit 035h
		_emit 08Ah
		_emit 088h
		_emit 054h
		_emit 002h
		_emit 000h
		_emit 000h
		_emit 084h
		_emit 0C9h
		_emit 075h
		_emit 02Bh
		_emit 0B1h
		_emit 001h
		_emit 088h
		_emit 088h
		_emit 054h
		_emit 002h
		_emit 000h
		_emit 000h
		_emit 0A1h
		_emit 040h
		_emit 04Bh
		_emit 02Fh
		_emit 001h
		_emit 0C7h
		_emit 080h
		_emit 05Ch
		_emit 002h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 08Bh
		_emit 015h
		_emit 058h
		_emit 04Bh
		_emit 02Fh
		_emit 001h
		_emit 088h
		_emit 04Ah
		_emit 050h
		_emit 08Bh
		_emit 00Dh
		_emit 0E8h
		_emit 019h
		_emit 02Fh
		_emit 001h
		_emit 0E9h
		_emit 0C4h
		_emit 0F9h
		_emit 0ABh
		_emit 0FFh
		_emit 0C3h
	}
}

