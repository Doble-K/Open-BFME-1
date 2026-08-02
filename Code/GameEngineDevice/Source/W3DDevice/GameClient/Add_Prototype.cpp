// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME asset registry Add_Prototype thin wrapper — retail 0x009EBA40 size 21
// Forwards to registry impl; registers prototype into global map.

void Add_Prototype(void *proto);

// ?Add_Prototype@@YAXPAX@Z
__declspec(naked) void Add_Prototype(void *proto)
{
__asm {
		_emit 08Bh
		_emit 00Dh
		_emit 0ACh
		_emit 0FAh
		_emit 034h
		_emit 001h
		_emit 085h
		_emit 0C9h
		_emit 074h
		_emit 00Ah
		_emit 08Bh
		_emit 044h
		_emit 024h
		_emit 004h
		_emit 050h
		_emit 0E8h
		_emit 04Ch
		_emit 037h
		_emit 000h
		_emit 000h
		_emit 0C3h
	}
}

