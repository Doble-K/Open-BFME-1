// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME registry Render_Obj_Exists by name — retail 0x009EBB80 size 28
// Global registry @ 0x134FAAC; used by Load_Asset_Catalog and type registers.

bool Render_Obj_Exists(const char *name);

// ?Render_Obj_Exists@@YA_NPBD@Z
__declspec(naked) bool Render_Obj_Exists(const char *name)
{
__asm {
		_emit 08Bh
		_emit 044h
		_emit 024h
		_emit 004h
		_emit 085h
		_emit 0C0h
		_emit 074h
		_emit 011h
		_emit 08Bh
		_emit 00Dh
		_emit 0ACh
		_emit 0FAh
		_emit 034h
		_emit 001h
		_emit 085h
		_emit 0C9h
		_emit 074h
		_emit 007h
		_emit 050h
		_emit 0E8h
		_emit 018h
		_emit 030h
		_emit 000h
		_emit 000h
		_emit 0C3h
		_emit 032h
		_emit 0C0h
		_emit 0C3h
	}
}

