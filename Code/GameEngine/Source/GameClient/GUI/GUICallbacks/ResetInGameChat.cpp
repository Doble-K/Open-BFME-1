// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

__declspec(naked) void ResetInGameChat()
{
	__asm {
		_emit 051h
		_emit 0A1h
		_emit 088h
		_emit 049h
		_emit 02Fh
		_emit 001h
		_emit 085h
		_emit 0C0h
		_emit 074h
		_emit 02Fh
		_emit 08Bh
		_emit 088h
		_emit 060h
		_emit 002h
		_emit 000h
		_emit 000h
		_emit 085h
		_emit 0C9h
		_emit 074h
		_emit 025h
		_emit 051h
		_emit 089h
		_emit 064h
		_emit 024h
		_emit 004h
		_emit 08Bh
		_emit 0CCh
		_emit 068h
		_emit 054h
		_emit 06Eh
		_emit 033h
		_emit 001h
		_emit 0E8h
		_emit 0DBh
		_emit 064h
		_emit 037h
		_emit 000h
		_emit 0A1h
		_emit 088h
		_emit 049h
		_emit 02Fh
		_emit 001h
		_emit 08Bh
		_emit 088h
		_emit 060h
		_emit 002h
		_emit 000h
		_emit 000h
		_emit 051h
		_emit 0E8h
		_emit 03Eh
		_emit 0A9h
		_emit 0AFh
		_emit 0FFh
		_emit 083h
		_emit 0C4h
		_emit 008h
		_emit 059h
		_emit 0C3h
	}
}
