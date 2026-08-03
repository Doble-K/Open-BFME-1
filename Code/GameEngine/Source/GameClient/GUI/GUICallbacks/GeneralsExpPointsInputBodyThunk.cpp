// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class GameWindow
{
};

enum WindowMsgHandledType
{
	WINDOW_MSG_HANDLED = 1
};

__declspec(naked) WindowMsgHandledType GeneralsExpPointsInputBodyThunk(GameWindow *, unsigned int, unsigned int, unsigned int)
{
	__asm {
		_emit 08Bh
		_emit 044h
		_emit 024h
		_emit 008h
		_emit 083h
		_emit 0F8h
		_emit 011h
		_emit 074h
		_emit 01Eh
		_emit 083h
		_emit 0F8h
		_emit 015h
		_emit 075h
		_emit 02Fh
		_emit 00Fh
		_emit 0B6h
		_emit 044h
		_emit 024h
		_emit 00Ch
		_emit 048h
		_emit 075h
		_emit 027h
		_emit 08Bh
		_emit 00Dh
		_emit 0F8h
		_emit 033h
		_emit 02Fh
		_emit 001h
		_emit 0E8h
		_emit 066h
		_emit 0BAh
		_emit 0B5h
		_emit 0FFh
		_emit 0B8h
		_emit 001h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 0C3h
		_emit 08Bh
		_emit 00Dh
		_emit 08Ch
		_emit 014h
		_emit 02Fh
		_emit 001h
		_emit 085h
		_emit 0C9h
		_emit 074h
		_emit 00Ch
		_emit 08Bh
		_emit 001h
		_emit 06Ah
		_emit 000h
		_emit 06Ah
		_emit 000h
		_emit 0FFh
		_emit 090h
		_emit 0C0h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 0B8h
		_emit 001h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 0C3h
	}
}
