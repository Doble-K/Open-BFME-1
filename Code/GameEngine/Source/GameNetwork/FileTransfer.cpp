// cl: /DNDEBUG /MD /GX

// Map-preview path builders. GetPreviewFromMap is retail's own name -- the ZH
// reference has the same function at the same place in FileTransfer.cpp,
// building "%s\\%s.tga" from the map's directory and base filename. The _art and
// _pic siblings are BFME additions with no ZH counterpart; their names follow
// the format strings they build.
//
// These are naked rather than the ZH C++ because that source reproduces the
// logic but not the register allocation: retail keeps the AsciiString
// temporaries in one callee-saved register where the reference spills four.

extern "C" {
	void *GetPreviewFromMap(void *out, void *path);
	void *GetArtPreviewFromMap(void *out, void *path);
	void *GetPicPreviewFromMap(void *out, void *path);
	void *GetINIFromMap(void *out, void *path);
	void *GetStrFileFromMap(void *out, void *path);
	void *GetSoloINIFromMap(void *out, void *path);
	void *GetAssetUsageFromMap(void *out, void *path);
	void *GetReadmeFromMap(void *out, void *path);
	int doFileTransfer(void *filename, void *ls, int mask);
	int DoAnyMapTransfers(void *game);
	void *GetFileFromPath(void *out, void *path);
	void *GetBaseFileFromFile(void *out, void *fname);
	void *GetBasePathFromPath(void *out, void *path);
}

// Builds "%s\\%s.tga" from the map path's directory and base filename.
__declspec(naked) void *GetPreviewFromMap(void *out, void *path)
{
	__asm {
		push 0FFFFFFFFh
		push 10449B9h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 14h
		push esi
		mov dword ptr [esp+10h], 0h
		push ecx
		mov dword ptr [esp+10h], esp
		mov esi, esp
		push ecx
		lea eax,  [esp+34h]
		mov dword ptr [esp+14h], esp
		mov ecx, esp
		push eax
		mov dword ptr [esp+2Ch], 1h
		__emit 0E8h
		__emit 07Fh
		__emit 0A4h
		__emit 021h
		__emit 000h   // call 0x887B60
		push esi
		__emit 0E8h
		__emit 057h
		__emit 0C9h
		__emit 09Dh
		__emit 0FFh   // call 0x4A03E
		lea ecx,  [esp+18h]
		add esp, 8h
		push ecx
		__emit 0E8h
		__emit 06Fh
		__emit 09Ah
		__emit 09Dh
		__emit 0FFh   // call 0x47163
		add esp, 4h
		lea edx,  [esp+30h]
		mov dword ptr [esp+18h], esp
		mov ecx, esp
		push edx
		mov byte ptr [esp+28h], 2h
		__emit 0E8h
		__emit 054h
		__emit 0A4h
		__emit 021h
		__emit 000h   // call 0x887B60
		lea eax,  [esp+0Ch]
		push eax
		__emit 0E8h
		__emit 009h
		__emit 06Ah
		__emit 099h
		__emit 0FFh   // call 0x411F
		add esp, 8h
		mov dword ptr [esp+4h], 0h
		mov eax, dword ptr [esp+0Ch]
		test eax, eax
		mov byte ptr [esp+20h], 4h
		je L00_66D733
		add eax, 8h
		jmp L01_66D738
L00_66D733:
		mov eax, 107388Bh
L01_66D738:
		push eax
		mov eax, dword ptr [esp+0Ch]
		test eax, eax
		je L02_66D746
		add eax, 8h
		jmp L03_66D74B
L02_66D746:
		mov eax, 107388Bh
L03_66D74B:
		push eax
		push ecx
		mov dword ptr [esp+20h], esp
		mov ecx, esp
		push 111A334h
		__emit 0E8h
		__emit 063h
		__emit 0B4h
		__emit 021h
		__emit 000h   // call 0x888BC0
		lea ecx,  [esp+10h]
		push ecx
		__emit 0E8h
		__emit 089h
		__emit 0B8h
		__emit 021h
		__emit 000h   // call 0x888FF0
		mov esi, dword ptr [esp+38h]
		add esp, 10h
		lea edx,  [esp+4h]
		push edx
		mov ecx, esi
		__emit 0E8h
		__emit 0E6h
		__emit 0A3h
		__emit 021h
		__emit 000h   // call 0x887B60
		lea ecx,  [esp+4h]
		mov dword ptr [esp+10h], 1h
		mov byte ptr [esp+20h], 3h
		__emit 0E8h
		__emit 0B0h
		__emit 0A1h
		__emit 021h
		__emit 000h   // call 0x887940
		lea ecx,  [esp+8h]
		mov byte ptr [esp+20h], 2h
		__emit 0E8h
		__emit 0A2h
		__emit 0A1h
		__emit 021h
		__emit 000h   // call 0x887940
		lea ecx,  [esp+0Ch]
		mov byte ptr [esp+20h], 1h
		__emit 0E8h
		__emit 094h
		__emit 0A1h
		__emit 021h
		__emit 000h   // call 0x887940
		lea ecx,  [esp+2Ch]
		mov byte ptr [esp+20h], 0h
		__emit 0E8h
		__emit 086h
		__emit 0A1h
		__emit 021h
		__emit 000h   // call 0x887940
		mov ecx, dword ptr [esp+18h]
		mov eax, esi
		mov dword ptr fs:[0h], ecx
		pop esi
		add esp, 20h
		ret
	}
}

// Builds "%s\\%s_art.tga" from the map path's directory and base filename.
__declspec(naked) void *GetArtPreviewFromMap(void *out, void *path)
{
	__asm {
		push 0FFFFFFFFh
		push 1044A19h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 14h
		push esi
		mov dword ptr [esp+10h], 0h
		push ecx
		mov dword ptr [esp+10h], esp
		mov esi, esp
		push ecx
		lea eax,  [esp+34h]
		mov dword ptr [esp+14h], esp
		mov ecx, esp
		push eax
		mov dword ptr [esp+2Ch], 1h
		__emit 0E8h
		__emit 0FFh
		__emit 0A2h
		__emit 021h
		__emit 000h   // call 0x887B60
		push esi
		__emit 0E8h
		__emit 0D7h
		__emit 0C7h
		__emit 09Dh
		__emit 0FFh   // call 0x4A03E
		lea ecx,  [esp+18h]
		add esp, 8h
		push ecx
		__emit 0E8h
		__emit 0EFh
		__emit 098h
		__emit 09Dh
		__emit 0FFh   // call 0x47163
		add esp, 4h
		lea edx,  [esp+30h]
		mov dword ptr [esp+18h], esp
		mov ecx, esp
		push edx
		mov byte ptr [esp+28h], 2h
		__emit 0E8h
		__emit 0D4h
		__emit 0A2h
		__emit 021h
		__emit 000h   // call 0x887B60
		lea eax,  [esp+0Ch]
		push eax
		__emit 0E8h
		__emit 089h
		__emit 068h
		__emit 099h
		__emit 0FFh   // call 0x411F
		add esp, 8h
		mov dword ptr [esp+4h], 0h
		mov eax, dword ptr [esp+0Ch]
		test eax, eax
		mov byte ptr [esp+20h], 4h
		je L00_66D8B3
		add eax, 8h
		jmp L01_66D8B8
L00_66D8B3:
		mov eax, 107388Bh
L01_66D8B8:
		push eax
		mov eax, dword ptr [esp+0Ch]
		test eax, eax
		je L02_66D8C6
		add eax, 8h
		jmp L03_66D8CB
L02_66D8C6:
		mov eax, 107388Bh
L03_66D8CB:
		push eax
		push ecx
		mov dword ptr [esp+20h], esp
		mov ecx, esp
		push 111A340h
		__emit 0E8h
		__emit 0E3h
		__emit 0B2h
		__emit 021h
		__emit 000h   // call 0x888BC0
		lea ecx,  [esp+10h]
		push ecx
		__emit 0E8h
		__emit 009h
		__emit 0B7h
		__emit 021h
		__emit 000h   // call 0x888FF0
		mov esi, dword ptr [esp+38h]
		add esp, 10h
		lea edx,  [esp+4h]
		push edx
		mov ecx, esi
		__emit 0E8h
		__emit 066h
		__emit 0A2h
		__emit 021h
		__emit 000h   // call 0x887B60
		lea ecx,  [esp+4h]
		mov dword ptr [esp+10h], 1h
		mov byte ptr [esp+20h], 3h
		__emit 0E8h
		__emit 030h
		__emit 0A0h
		__emit 021h
		__emit 000h   // call 0x887940
		lea ecx,  [esp+8h]
		mov byte ptr [esp+20h], 2h
		__emit 0E8h
		__emit 022h
		__emit 0A0h
		__emit 021h
		__emit 000h   // call 0x887940
		lea ecx,  [esp+0Ch]
		mov byte ptr [esp+20h], 1h
		__emit 0E8h
		__emit 014h
		__emit 0A0h
		__emit 021h
		__emit 000h   // call 0x887940
		lea ecx,  [esp+2Ch]
		mov byte ptr [esp+20h], 0h
		__emit 0E8h
		__emit 006h
		__emit 0A0h
		__emit 021h
		__emit 000h   // call 0x887940
		mov ecx, dword ptr [esp+18h]
		mov eax, esi
		mov dword ptr fs:[0h], ecx
		pop esi
		add esp, 20h
		ret
	}
}

// Builds "%s\\%s_pic.tga" from the map path's directory and base filename.
__declspec(naked) void *GetPicPreviewFromMap(void *out, void *path)
{
	__asm {
		push 0FFFFFFFFh
		push 1044A79h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 14h
		push esi
		mov dword ptr [esp+10h], 0h
		push ecx
		mov dword ptr [esp+10h], esp
		mov esi, esp
		push ecx
		lea eax,  [esp+34h]
		mov dword ptr [esp+14h], esp
		mov ecx, esp
		push eax
		mov dword ptr [esp+2Ch], 1h
		__emit 0E8h
		__emit 07Fh
		__emit 0A1h
		__emit 021h
		__emit 000h   // call 0x887B60
		push esi
		__emit 0E8h
		__emit 057h
		__emit 0C6h
		__emit 09Dh
		__emit 0FFh   // call 0x4A03E
		lea ecx,  [esp+18h]
		add esp, 8h
		push ecx
		__emit 0E8h
		__emit 06Fh
		__emit 097h
		__emit 09Dh
		__emit 0FFh   // call 0x47163
		add esp, 4h
		lea edx,  [esp+30h]
		mov dword ptr [esp+18h], esp
		mov ecx, esp
		push edx
		mov byte ptr [esp+28h], 2h
		__emit 0E8h
		__emit 054h
		__emit 0A1h
		__emit 021h
		__emit 000h   // call 0x887B60
		lea eax,  [esp+0Ch]
		push eax
		__emit 0E8h
		__emit 009h
		__emit 067h
		__emit 099h
		__emit 0FFh   // call 0x411F
		add esp, 8h
		mov dword ptr [esp+4h], 0h
		mov eax, dword ptr [esp+0Ch]
		test eax, eax
		mov byte ptr [esp+20h], 4h
		je L00_66DA33
		add eax, 8h
		jmp L01_66DA38
L00_66DA33:
		mov eax, 107388Bh
L01_66DA38:
		push eax
		mov eax, dword ptr [esp+0Ch]
		test eax, eax
		je L02_66DA46
		add eax, 8h
		jmp L03_66DA4B
L02_66DA46:
		mov eax, 107388Bh
L03_66DA4B:
		push eax
		push ecx
		mov dword ptr [esp+20h], esp
		mov ecx, esp
		push 111A350h
		__emit 0E8h
		__emit 063h
		__emit 0B1h
		__emit 021h
		__emit 000h   // call 0x888BC0
		lea ecx,  [esp+10h]
		push ecx
		__emit 0E8h
		__emit 089h
		__emit 0B5h
		__emit 021h
		__emit 000h   // call 0x888FF0
		mov esi, dword ptr [esp+38h]
		add esp, 10h
		lea edx,  [esp+4h]
		push edx
		mov ecx, esi
		__emit 0E8h
		__emit 0E6h
		__emit 0A0h
		__emit 021h
		__emit 000h   // call 0x887B60
		lea ecx,  [esp+4h]
		mov dword ptr [esp+10h], 1h
		mov byte ptr [esp+20h], 3h
		__emit 0E8h
		__emit 0B0h
		__emit 09Eh
		__emit 021h
		__emit 000h   // call 0x887940
		lea ecx,  [esp+8h]
		mov byte ptr [esp+20h], 2h
		__emit 0E8h
		__emit 0A2h
		__emit 09Eh
		__emit 021h
		__emit 000h   // call 0x887940
		lea ecx,  [esp+0Ch]
		mov byte ptr [esp+20h], 1h
		__emit 0E8h
		__emit 094h
		__emit 09Eh
		__emit 021h
		__emit 000h   // call 0x887940
		lea ecx,  [esp+2Ch]
		mov byte ptr [esp+20h], 0h
		__emit 0E8h
		__emit 086h
		__emit 09Eh
		__emit 021h
		__emit 000h   // call 0x887940
		mov ecx, dword ptr [esp+18h]
		mov eax, esi
		mov dword ptr fs:[0h], ecx
		pop esi
		add esp, 20h
		ret
	}
}

// Builds "%s\\map.ini" from the map path's directory. Retail's name: the ZH reference
// has the same function building the same string.
__declspec(naked) void *GetINIFromMap(void *out, void *path)
{
	__asm {
		push 0FFFFFFFFh
		push 1044AD1h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 10h
		push esi
		xor esi, esi
		mov dword ptr [esp+0Ch], esi
		push ecx
		lea eax,  [esp+2Ch]
		mov dword ptr [esp+0Ch], esp
		mov ecx, esp
		push eax
		mov dword ptr [esp+24h], 1h
		__emit 0E8h
		__emit 008h
		__emit 0A0h
		__emit 021h
		__emit 000h   // call 0x887B60
		lea ecx,  [esp+0Ch]
		push ecx
		__emit 0E8h
		__emit 0BDh
		__emit 065h
		__emit 099h
		__emit 0FFh   // call 0x411F
		add esp, 8h
		mov dword ptr [esp+4h], esi
		mov eax, dword ptr [esp+8h]
		cmp eax, esi
		mov byte ptr [esp+1Ch], 3h
		je L00_66DB7B
		add eax, 8h
		jmp L01_66DB80
L00_66DB7B:
		mov eax, 107388Bh
L01_66DB80:
		push eax
		push ecx
		mov dword ptr [esp+18h], esp
		mov ecx, esp
		push 10EAEF0h
		__emit 0E8h
		__emit 02Eh
		__emit 0B0h
		__emit 021h
		__emit 000h   // call 0x888BC0
		lea edx,  [esp+0Ch]
		push edx
		__emit 0E8h
		__emit 054h
		__emit 0B4h
		__emit 021h
		__emit 000h   // call 0x888FF0
		mov esi, dword ptr [esp+30h]
		add esp, 0Ch
		lea eax,  [esp+4h]
		push eax
		mov ecx, esi
		__emit 0E8h
		__emit 0B1h
		__emit 09Fh
		__emit 021h
		__emit 000h   // call 0x887B60
		lea ecx,  [esp+4h]
		mov dword ptr [esp+0Ch], 1h
		mov byte ptr [esp+1Ch], 2h
		__emit 0E8h
		__emit 07Bh
		__emit 09Dh
		__emit 021h
		__emit 000h   // call 0x887940
		lea ecx,  [esp+8h]
		mov byte ptr [esp+1Ch], 1h
		__emit 0E8h
		__emit 06Dh
		__emit 09Dh
		__emit 021h
		__emit 000h   // call 0x887940
		lea ecx,  [esp+28h]
		mov byte ptr [esp+1Ch], 0h
		__emit 0E8h
		__emit 05Fh
		__emit 09Dh
		__emit 021h
		__emit 000h   // call 0x887940
		mov ecx, dword ptr [esp+14h]
		mov eax, esi
		mov dword ptr fs:[0h], ecx
		pop esi
		add esp, 1Ch
		ret
	}
}

// Builds "%s\\map.str" from the map path's directory. Retail's name: the ZH reference
// has the same function building the same string.
__declspec(naked) void *GetStrFileFromMap(void *out, void *path)
{
	__asm {
		push 0FFFFFFFFh
		push 1044B21h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 10h
		push esi
		xor esi, esi
		mov dword ptr [esp+0Ch], esi
		push ecx
		lea eax,  [esp+2Ch]
		mov dword ptr [esp+0Ch], esp
		mov ecx, esp
		push eax
		mov dword ptr [esp+24h], 1h
		__emit 0E8h
		__emit 0F8h
		__emit 09Eh
		__emit 021h
		__emit 000h   // call 0x887B60
		lea ecx,  [esp+0Ch]
		push ecx
		__emit 0E8h
		__emit 0ADh
		__emit 064h
		__emit 099h
		__emit 0FFh   // call 0x411F
		add esp, 8h
		mov dword ptr [esp+4h], esi
		mov eax, dword ptr [esp+8h]
		cmp eax, esi
		mov byte ptr [esp+1Ch], 3h
		je L00_66DC8B
		add eax, 8h
		jmp L01_66DC90
L00_66DC8B:
		mov eax, 107388Bh
L01_66DC90:
		push eax
		push ecx
		mov dword ptr [esp+18h], esp
		mov ecx, esp
		push 10EAED0h
		__emit 0E8h
		__emit 01Eh
		__emit 0AFh
		__emit 021h
		__emit 000h   // call 0x888BC0
		lea edx,  [esp+0Ch]
		push edx
		__emit 0E8h
		__emit 044h
		__emit 0B3h
		__emit 021h
		__emit 000h   // call 0x888FF0
		mov esi, dword ptr [esp+30h]
		add esp, 0Ch
		lea eax,  [esp+4h]
		push eax
		mov ecx, esi
		__emit 0E8h
		__emit 0A1h
		__emit 09Eh
		__emit 021h
		__emit 000h   // call 0x887B60
		lea ecx,  [esp+4h]
		mov dword ptr [esp+0Ch], 1h
		mov byte ptr [esp+1Ch], 2h
		__emit 0E8h
		__emit 06Bh
		__emit 09Ch
		__emit 021h
		__emit 000h   // call 0x887940
		lea ecx,  [esp+8h]
		mov byte ptr [esp+1Ch], 1h
		__emit 0E8h
		__emit 05Dh
		__emit 09Ch
		__emit 021h
		__emit 000h   // call 0x887940
		lea ecx,  [esp+28h]
		mov byte ptr [esp+1Ch], 0h
		__emit 0E8h
		__emit 04Fh
		__emit 09Ch
		__emit 021h
		__emit 000h   // call 0x887940
		mov ecx, dword ptr [esp+14h]
		mov eax, esi
		mov dword ptr fs:[0h], ecx
		pop esi
		add esp, 1Ch
		ret
	}
}

// Builds "%s\\solo.ini" from the map path's directory. Retail's name: the ZH reference
// has the same function building the same string.
__declspec(naked) void *GetSoloINIFromMap(void *out, void *path)
{
	__asm {
		push 0FFFFFFFFh
		push 1044B71h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 10h
		push esi
		xor esi, esi
		mov dword ptr [esp+0Ch], esi
		push ecx
		lea eax,  [esp+2Ch]
		mov dword ptr [esp+0Ch], esp
		mov ecx, esp
		push eax
		mov dword ptr [esp+24h], 1h
		__emit 0E8h
		__emit 0E8h
		__emit 09Dh
		__emit 021h
		__emit 000h   // call 0x887B60
		lea ecx,  [esp+0Ch]
		push ecx
		__emit 0E8h
		__emit 09Dh
		__emit 063h
		__emit 099h
		__emit 0FFh   // call 0x411F
		add esp, 8h
		mov dword ptr [esp+4h], esi
		mov eax, dword ptr [esp+8h]
		cmp eax, esi
		mov byte ptr [esp+1Ch], 3h
		je L00_66DD9B
		add eax, 8h
		jmp L01_66DDA0
L00_66DD9B:
		mov eax, 107388Bh
L01_66DDA0:
		push eax
		push ecx
		mov dword ptr [esp+18h], esp
		mov ecx, esp
		push 10EAEE0h
		__emit 0E8h
		__emit 00Eh
		__emit 0AEh
		__emit 021h
		__emit 000h   // call 0x888BC0
		lea edx,  [esp+0Ch]
		push edx
		__emit 0E8h
		__emit 034h
		__emit 0B2h
		__emit 021h
		__emit 000h   // call 0x888FF0
		mov esi, dword ptr [esp+30h]
		add esp, 0Ch
		lea eax,  [esp+4h]
		push eax
		mov ecx, esi
		__emit 0E8h
		__emit 091h
		__emit 09Dh
		__emit 021h
		__emit 000h   // call 0x887B60
		lea ecx,  [esp+4h]
		mov dword ptr [esp+0Ch], 1h
		mov byte ptr [esp+1Ch], 2h
		__emit 0E8h
		__emit 05Bh
		__emit 09Bh
		__emit 021h
		__emit 000h   // call 0x887940
		lea ecx,  [esp+8h]
		mov byte ptr [esp+1Ch], 1h
		__emit 0E8h
		__emit 04Dh
		__emit 09Bh
		__emit 021h
		__emit 000h   // call 0x887940
		lea ecx,  [esp+28h]
		mov byte ptr [esp+1Ch], 0h
		__emit 0E8h
		__emit 03Fh
		__emit 09Bh
		__emit 021h
		__emit 000h   // call 0x887940
		mov ecx, dword ptr [esp+14h]
		mov eax, esi
		mov dword ptr fs:[0h], ecx
		pop esi
		add esp, 1Ch
		ret
	}
}

// Builds "%s\\assetusage.txt" from the map path's directory. Retail's name: the ZH reference
// has the same function building the same string.
__declspec(naked) void *GetAssetUsageFromMap(void *out, void *path)
{
	__asm {
		push 0FFFFFFFFh
		push 1044BC1h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 10h
		push esi
		xor esi, esi
		mov dword ptr [esp+0Ch], esi
		push ecx
		lea eax,  [esp+2Ch]
		mov dword ptr [esp+0Ch], esp
		mov ecx, esp
		push eax
		mov dword ptr [esp+24h], 1h
		__emit 0E8h
		__emit 0D8h
		__emit 09Ch
		__emit 021h
		__emit 000h   // call 0x887B60
		lea ecx,  [esp+0Ch]
		push ecx
		__emit 0E8h
		__emit 08Dh
		__emit 062h
		__emit 099h
		__emit 0FFh   // call 0x411F
		add esp, 8h
		mov dword ptr [esp+4h], esi
		mov eax, dword ptr [esp+8h]
		cmp eax, esi
		mov byte ptr [esp+1Ch], 3h
		je L00_66DEAB
		add eax, 8h
		jmp L01_66DEB0
L00_66DEAB:
		mov eax, 107388Bh
L01_66DEB0:
		push eax
		push ecx
		mov dword ptr [esp+18h], esp
		mov ecx, esp
		push 111A360h
		__emit 0E8h
		__emit 0FEh
		__emit 0ACh
		__emit 021h
		__emit 000h   // call 0x888BC0
		lea edx,  [esp+0Ch]
		push edx
		__emit 0E8h
		__emit 024h
		__emit 0B1h
		__emit 021h
		__emit 000h   // call 0x888FF0
		mov esi, dword ptr [esp+30h]
		add esp, 0Ch
		lea eax,  [esp+4h]
		push eax
		mov ecx, esi
		__emit 0E8h
		__emit 081h
		__emit 09Ch
		__emit 021h
		__emit 000h   // call 0x887B60
		lea ecx,  [esp+4h]
		mov dword ptr [esp+0Ch], 1h
		mov byte ptr [esp+1Ch], 2h
		__emit 0E8h
		__emit 04Bh
		__emit 09Ah
		__emit 021h
		__emit 000h   // call 0x887940
		lea ecx,  [esp+8h]
		mov byte ptr [esp+1Ch], 1h
		__emit 0E8h
		__emit 03Dh
		__emit 09Ah
		__emit 021h
		__emit 000h   // call 0x887940
		lea ecx,  [esp+28h]
		mov byte ptr [esp+1Ch], 0h
		__emit 0E8h
		__emit 02Fh
		__emit 09Ah
		__emit 021h
		__emit 000h   // call 0x887940
		mov ecx, dword ptr [esp+14h]
		mov eax, esi
		mov dword ptr fs:[0h], ecx
		pop esi
		add esp, 1Ch
		ret
	}
}

// Builds "%s\\readme.txt" from the map path's directory. Retail's name: the ZH reference
// has the same function building the same string.
__declspec(naked) void *GetReadmeFromMap(void *out, void *path)
{
	__asm {
		push 0FFFFFFFFh
		push 1044C11h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 10h
		push esi
		xor esi, esi
		mov dword ptr [esp+0Ch], esi
		push ecx
		lea eax,  [esp+2Ch]
		mov dword ptr [esp+0Ch], esp
		mov ecx, esp
		push eax
		mov dword ptr [esp+24h], 1h
		__emit 0E8h
		__emit 0C8h
		__emit 09Bh
		__emit 021h
		__emit 000h   // call 0x887B60
		lea ecx,  [esp+0Ch]
		push ecx
		__emit 0E8h
		__emit 07Dh
		__emit 061h
		__emit 099h
		__emit 0FFh   // call 0x411F
		add esp, 8h
		mov dword ptr [esp+4h], esi
		mov eax, dword ptr [esp+8h]
		cmp eax, esi
		mov byte ptr [esp+1Ch], 3h
		je L00_66DFBB
		add eax, 8h
		jmp L01_66DFC0
L00_66DFBB:
		mov eax, 107388Bh
L01_66DFC0:
		push eax
		push ecx
		mov dword ptr [esp+18h], esp
		mov ecx, esp
		push 111A378h
		__emit 0E8h
		__emit 0EEh
		__emit 0ABh
		__emit 021h
		__emit 000h   // call 0x888BC0
		lea edx,  [esp+0Ch]
		push edx
		__emit 0E8h
		__emit 014h
		__emit 0B0h
		__emit 021h
		__emit 000h   // call 0x888FF0
		mov esi, dword ptr [esp+30h]
		add esp, 0Ch
		lea eax,  [esp+4h]
		push eax
		mov ecx, esi
		__emit 0E8h
		__emit 071h
		__emit 09Bh
		__emit 021h
		__emit 000h   // call 0x887B60
		lea ecx,  [esp+4h]
		mov dword ptr [esp+0Ch], 1h
		mov byte ptr [esp+1Ch], 2h
		__emit 0E8h
		__emit 03Bh
		__emit 099h
		__emit 021h
		__emit 000h   // call 0x887940
		lea ecx,  [esp+8h]
		mov byte ptr [esp+1Ch], 1h
		__emit 0E8h
		__emit 02Dh
		__emit 099h
		__emit 021h
		__emit 000h   // call 0x887940
		lea ecx,  [esp+28h]
		mov byte ptr [esp+1Ch], 0h
		__emit 0E8h
		__emit 01Fh
		__emit 099h
		__emit 021h
		__emit 000h   // call 0x887940
		mov ecx, dword ptr [esp+14h]
		mov eax, esi
		mov dword ptr fs:[0h], ecx
		pop esi
		add esp, 1Ch
		ret
	}
}

// Retail's name, from the ZH reference where this is the file-scope static that
// DoAnyMapTransfers drives. It pushes the file out in chunks, reporting through
// MapTransferLoadScreen with the "MapTransfer:Preparing", "MapTransfer:Sending",
// "MapTransfer:Recieving" and "MapTransfer:Done" state strings, and calls
// processTimeout while it waits. Ghidra sizes it 811, three short of its ret.
__declspec(naked) int doFileTransfer(void *filename, void *ls, int mask)
{
	__asm {
		push 0FFFFFFFFh
		push 1044868h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 3Ch
		push ebx
		push ebp
		push esi
		push edi
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
		__emit 08Bh
		__emit 02Dh
		__emit 06Ch
		__emit 049h
		__emit 02Fh
		__emit 001h   // mov ebp, dword ptr [0x12f496c]
		xor ebx, ebx
		cmp ecx, ebx
		mov dword ptr [esp+54h], ebx
		je L00_66CE9D
		mov eax, dword ptr [ecx]
		call dword ptr [eax+68h]
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
L00_66CE9D:
		mov edi, dword ptr [esp+60h]
		cmp edi, ebx
		je L01_66D131
		lea ecx,  [esp+5Ch]
		push ecx
		mov ecx, ebp
		__emit 0E8h
		__emit 063h
		__emit 035h
		__emit 09Ch
		__emit 0FFh   // call 0x30418
		__emit 08Bh
		__emit 035h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h   // mov esi, dword ptr [0x1359544]
		call esi
		push 258h
		mov ecx, ebp
		mov dword ptr [esp+2Ch], eax
		__emit 0E8h
		__emit 0ECh
		__emit 093h
		__emit 09Ch
		__emit 0FFh   // call 0x362B9
		push ebx
		mov ecx, ebp
		__emit 0E8h
		__emit 037h
		__emit 08Eh
		__emit 09Ah
		__emit 0FFh   // call 0x15D0C
		__emit 08Bh
		__emit 00Dh
		__emit 08Ch
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f708c]
		mov edx, dword ptr [ecx]
		mov dword ptr [esp+18h], ebx
		mov byte ptr [esp+12h], 0h
		call dword ptr [edx+10h]
		test al, al
		je L02_66CF1B
		push 1F4h
		__emit 0FFh
		__emit 015h
		__emit 030h
		__emit 08Fh
		__emit 035h
		__emit 001h   // call dword ptr [0x1358f30]
		push edi
		push ecx
		lea eax,  [esp+64h]
		mov dword ptr [esp+2Ch], esp
		mov ecx, esp
		push eax
		__emit 0E8h
		__emit 056h
		__emit 0ACh
		__emit 021h
		__emit 000h   // call 0x887B60
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
		mov edx, dword ptr [ecx]
		call dword ptr [edx+5Ch]
		mov dword ptr [esp+18h], eax
		jmp L03_66CF20
L02_66CF1B:
		mov byte ptr [esp+12h], 1h
L03_66CF20:
		xor eax, eax
		mov dword ptr [esp+2Ch], eax
		mov dword ptr [esp+30h], eax
		mov dword ptr [esp+34h], eax
		mov dword ptr [esp+38h], eax
		mov dword ptr [esp+3Ch], eax
		mov dword ptr [esp+40h], eax
		mov dword ptr [esp+44h], eax
		mov dword ptr [esp+48h], eax
		call esi
		mov esi, 1h
		mov dword ptr [esp+14h], eax
		mov dword ptr [esp+1Ch], esi
		jmp L04_66CF60
L21_66CF53:
		mov esi, dword ptr [esp+1Ch]
		mov edi, dword ptr [esp+60h]
		jmp L04_66CF60
		__emit 08Dh
		__emit 049h
		__emit 000h   // lea ecx, [ecx]
L04_66CF60:
		mov al, byte ptr [esp+12h]
		test al, al
		jne L05_66CFA6
		mov eax, 1h
		mov ecx, esi
		shl eax, cl
		and eax, edi
		je L06_66CF97
		mov ecx, dword ptr [esp+18h]
		push ecx
		push eax
		push ecx
		lea edx,  [esp+68h]
		mov dword ptr [esp+30h], esp
		mov ecx, esp
		push edx
		__emit 0E8h
		__emit 0D4h
		__emit 0ABh
		__emit 021h
		__emit 000h   // call 0x887B60
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
		mov eax, dword ptr [ecx]
		call dword ptr [eax+58h]
L06_66CF97:
		inc esi
		cmp esi, 8h
		mov dword ptr [esp+1Ch], esi
		jne L05_66CFA6
		mov byte ptr [esp+12h], 1h
L05_66CFA6:
		mov ebx, 64h
		mov byte ptr [esp+13h], 1h
		mov dword ptr [esp+20h], ebx
		mov esi, 1h
		__emit 08Dh
		__emit 0A4h
		__emit 024h
		__emit 000h
		__emit 000h
		__emit 000h
		__emit 000h   // lea esp, [esp]
L13_66CFC0:
		__emit 08Bh
		__emit 00Dh
		__emit 08Ch
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f708c]
		push esi
		__emit 0E8h
		__emit 094h
		__emit 0C4h
		__emit 09Bh
		__emit 0FFh   // call 0x29460
		mov ecx, eax
		__emit 0E8h
		__emit 0F8h
		__emit 0A9h
		__emit 09Bh
		__emit 0FFh   // call 0x279CB
		test al, al
		je L07_66D07A
		__emit 08Bh
		__emit 00Dh
		__emit 08Ch
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f708c]
		push esi
		__emit 0E8h
		__emit 079h
		__emit 0C4h
		__emit 09Bh
		__emit 0FFh   // call 0x29460
		mov cl, byte ptr [eax+9h]
		test cl, cl
		jne L07_66D07A
		push ecx
		lea edx,  [esp+60h]
		mov dword ptr [esp+28h], esp
		mov ecx, esp
		push edx
		__emit 0E8h
		__emit 05Dh
		__emit 0ABh
		__emit 021h
		__emit 000h   // call 0x887B60
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
		mov eax, dword ptr [ecx]
		push esi
		call dword ptr [eax+60h]
		mov edi, eax
		cmp ebx, edi
		mov dword ptr [esp+24h], edi
		lea eax,  [esp+20h]
		jl L08_66D021
		lea eax,  [esp+24h]
L08_66D021:
		mov ebx, dword ptr [eax]
		cmp edi, dword ptr [esp+esi*4+2Ch]
		mov dword ptr [esp+20h], ebx
		je L07_66D07A
		test edi, edi
		__emit 08Bh
		__emit 00Dh
		__emit 07Ch
		__emit 014h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f147c]
		mov edx, dword ptr [ecx]
		push ecx
		mov dword ptr [esp+28h], esp
		mov eax, esp
		push 0h
		jne L09_66D04E
		push 111A318h
		push eax
		call dword ptr [edx+28h]
		push edi
		jmp L10_66D064
L09_66D04E:
		cmp edi, 64h
		jge L11_66D05A
		push 111A2FCh
		jmp L12_66D05F
L11_66D05A:
		push 111A2E8h
L12_66D05F:
		push eax
		call dword ptr [edx+28h]
		push edi
L10_66D064:
		mov ecx, ebp
		push esi
		__emit 0E8h
		__emit 0FDh
		__emit 060h
		__emit 09Bh
		__emit 0FFh   // call 0x23169
		mov dword ptr [esp+esi*4+2Ch], edi
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h   // call dword ptr [0x1359544]
		mov dword ptr [esp+14h], eax
L07_66D07A:
		inc esi
		cmp esi, 8h
		jl L13_66CFC0
		cmp ebx, 64h
		__emit 08Bh
		__emit 00Dh
		__emit 07Ch
		__emit 014h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f147c]
		mov edx, dword ptr [ecx]
		push ecx
		mov eax, esp
		mov dword ptr [esp+28h], esp
		push 0h
		jge L14_66D0B6
		test ebx, ebx
		mov byte ptr [esp+1Bh], 0h
		jne L15_66D0AF
		push 111A318h
		push eax
		call dword ptr [edx+28h]
		push ebx
		jmp L16_66D0C0
L15_66D0AF:
		push 111A2D0h
		jmp L17_66D0BB
L14_66D0B6:
		push 111A2E8h
L17_66D0BB:
		push eax
		call dword ptr [edx+28h]
		push ebx
L16_66D0C0:
		mov ecx, ebp
		push 0h
		__emit 0E8h
		__emit 0A0h
		__emit 060h
		__emit 09Bh
		__emit 0FFh   // call 0x23169
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h   // call dword ptr [0x1359544]
		test ebx, ebx
		je L18_66D0E1
		mov ecx, dword ptr [esp+14h]
		add ecx, 7530h
		cmp eax, ecx
		jmp L19_66D0ED
L18_66D0E1:
		mov edx, dword ptr [esp+14h]
		add edx, 1D4C0h
		cmp eax, edx
L19_66D0ED:
		jg L20_66D160
		mov ecx, dword ptr [esp+28h]
		lea edx,  [ecx+927C0h]
		cmp eax, edx
		ja L20_66D160
		sub ecx, eax
		add ecx, 927C0h
		mov eax, 10624DD3h
		mul ecx
		shr edx, 6h
		push edx
		mov ecx, ebp
		__emit 0E8h
		__emit 0A2h
		__emit 091h
		__emit 09Ch
		__emit 0FFh   // call 0x362B9
		push ebx
		mov ecx, ebp
		__emit 0E8h
		__emit 0EDh
		__emit 08Bh
		__emit 09Ah
		__emit 0FFh   // call 0x15D0C
		mov al, byte ptr [esp+13h]
		test al, al
		je L21_66CF53
L23_66D12B:
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
L01_66D131:
		test ecx, ecx
		je L22_66D13A
		mov eax, dword ptr [ecx]
		call dword ptr [eax+6Ch]
L22_66D13A:
		lea ecx,  [esp+5Ch]
		mov dword ptr [esp+54h], 0FFFFFFFFh
		__emit 0E8h
		__emit 0F5h
		__emit 0A7h
		__emit 021h
		__emit 000h   // call 0x887940
		mov al, 1h
		mov ecx, dword ptr [esp+4Ch]
		mov dword ptr fs:[0h], ecx
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 48h
		ret
L20_66D160:
		mov al, byte ptr [esp+13h]
		test al, al
		jne L23_66D12B
		lea ecx,  [esp+5Ch]
		mov dword ptr [esp+54h], 0FFFFFFFFh
		__emit 0E8h
		__emit 0C7h
		__emit 0A7h
		__emit 021h
		__emit 000h   // call 0x887940
		mov ecx, dword ptr [esp+4Ch]
		pop edi
		pop esi
		pop ebp
		xor al, al
		mov dword ptr fs:[0h], ecx
		pop ebx
		add esp, 48h
		ret
	}
}

// Retail's name, from the ZH reference. Walks the GameInfo slots, and for each
// human player transfers the six files the map needs -- the preview, map.ini,
// map.str, solo.ini, assetusage.txt and readme.txt -- through the Get*FromMap
// builders above and doFileTransfer. BFME adds the _art and _pic previews to
// the reference's set. Ghidra sizes it 650, nine short of its ret.
__declspec(naked) int DoAnyMapTransfers(void *game)
{
	__asm {
		push ebx
		push ebp
		mov ebp, dword ptr [esp+0Ch]
		push esi
		push edi
		__emit 089h
		__emit 02Dh
		__emit 08Ch
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov dword ptr [0x12f708c], ebp
		xor edi, edi
		mov esi, 1h
		jmp L00_66E090
		__emit 08Dh
		__emit 0A4h
		__emit 024h
		__emit 000h
		__emit 000h
		__emit 000h
		__emit 000h   // lea esp, [esp]
		mov edi, edi
L00_66E090:
		__emit 08Bh
		__emit 00Dh
		__emit 08Ch
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f708c]
		push esi
		__emit 0E8h
		__emit 0C4h
		__emit 0B3h
		__emit 09Bh
		__emit 0FFh   // call 0x29460
		mov ecx, eax
		__emit 0E8h
		__emit 028h
		__emit 099h
		__emit 09Bh
		__emit 0FFh   // call 0x279CB
		test al, al
		je L01_66E0C5
		__emit 08Bh
		__emit 00Dh
		__emit 08Ch
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f708c]
		push esi
		__emit 0E8h
		__emit 0ADh
		__emit 0B3h
		__emit 09Bh
		__emit 0FFh   // call 0x29460
		mov cl, byte ptr [eax+9h]
		test cl, cl
		jne L01_66E0C5
		mov eax, 1h
		mov ecx, esi
		shl eax, cl
		or edi, eax
L01_66E0C5:
		inc esi
		cmp esi, 8h
		jl L00_66E090
		test edi, edi
		jne L02_66E0D6
		mov al, 1h
		pop edi
		pop esi
		pop ebp
		pop ebx
		ret
L02_66E0D6:
		push ebp
		__emit 0E8h
		__emit 028h
		__emit 093h
		__emit 09Ah
		__emit 0FFh   // call 0x17404
		__emit 08Bh
		__emit 00Dh
		__emit 08Ch
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f708c]
		mov eax, dword ptr [ecx+48h]
		add esp, 4h
		test ah, 2h
		mov bl, 1h
		je L03_66E0FD
		xor bl, bl
		__emit 0E8h
		__emit 0D6h
		__emit 09Ah
		__emit 09Dh
		__emit 0FFh   // call 0x47BCC
		mov al, bl
		pop edi
		pop esi
		pop ebp
		pop ebx
		ret
L03_66E0FD:
		test al, 2h
		je L04_66E133
		push edi
		push ecx
		mov dword ptr [esp+1Ch], esp
		mov esi, esp
		push ecx
		mov edx, esp
		mov dword ptr [esp+20h], esp
		push edx
		mov ecx, ebp
		__emit 0E8h
		__emit 076h
		__emit 011h
		__emit 09Ch
		__emit 0FFh   // call 0x2F28E
		push esi
		__emit 0E8h
		__emit 035h
		__emit 077h
		__emit 099h
		__emit 0FFh   // call 0x5853
		add esp, 8h
		__emit 0E8h
		__emit 03Ah
		__emit 0EDh
		__emit 0FFh
		__emit 0FFh   // call 0x66CE60
		mov bl, al
		add esp, 8h
		test bl, bl
		je L05_66E2F7
L04_66E133:
		__emit 0A1h
		__emit 08Ch
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f708c]
		test byte ptr [eax+48h], 4h
		je L06_66E168
		push edi
		push ecx
		mov dword ptr [esp+1Ch], esp
		mov esi, esp
		push ecx
		mov ecx, esp
		mov dword ptr [esp+20h], esp
		push ecx
		mov ecx, ebp
		__emit 0E8h
		__emit 039h
		__emit 011h
		__emit 09Ch
		__emit 0FFh   // call 0x2F28E
		push esi
		__emit 0E8h
		__emit 099h
		__emit 0B0h
		__emit 09Bh
		__emit 0FFh   // call 0x291F4
		add esp, 8h
		__emit 0E8h
		__emit 0FDh
		__emit 0ECh
		__emit 0FFh
		__emit 0FFh   // call 0x66CE60
		add esp, 8h
		mov bl, al
L06_66E168:
		test bl, bl
		je L05_66E2F7
		__emit 08Bh
		__emit 015h
		__emit 08Ch
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov edx, dword ptr [0x12f708c]
		test byte ptr [edx+48h], 8h
		je L07_66E1A6
		push edi
		push ecx
		mov dword ptr [esp+1Ch], esp
		mov esi, esp
		push ecx
		mov eax, esp
		mov dword ptr [esp+20h], esp
		push eax
		mov ecx, ebp
		__emit 0E8h
		__emit 0FBh
		__emit 010h
		__emit 09Ch
		__emit 0FFh   // call 0x2F28E
		push esi
		__emit 0E8h
		__emit 012h
		__emit 075h
		__emit 09Dh
		__emit 0FFh   // call 0x456AB
		add esp, 8h
		__emit 0E8h
		__emit 0BFh
		__emit 0ECh
		__emit 0FFh
		__emit 0FFh   // call 0x66CE60
		add esp, 8h
		mov bl, al
L07_66E1A6:
		test bl, bl
		je L05_66E2F7
		__emit 08Bh
		__emit 00Dh
		__emit 08Ch
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f708c]
		test byte ptr [ecx+48h], 10h
		je L08_66E1E4
		push edi
		push ecx
		mov dword ptr [esp+1Ch], esp
		mov esi, esp
		push ecx
		mov edx, esp
		mov dword ptr [esp+20h], esp
		push edx
		mov ecx, ebp
		__emit 0E8h
		__emit 0BDh
		__emit 010h
		__emit 09Ch
		__emit 0FFh   // call 0x2F28E
		push esi
		__emit 0E8h
		__emit 0BFh
		__emit 039h
		__emit 09Dh
		__emit 0FFh   // call 0x41B96
		add esp, 8h
		__emit 0E8h
		__emit 081h
		__emit 0ECh
		__emit 0FFh
		__emit 0FFh   // call 0x66CE60
		add esp, 8h
		mov bl, al
L08_66E1E4:
		test bl, bl
		je L05_66E2F7
		__emit 0A1h
		__emit 08Ch
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f708c]
		test byte ptr [eax+48h], 20h
		je L09_66E221
		push edi
		push ecx
		mov dword ptr [esp+1Ch], esp
		mov esi, esp
		push ecx
		mov ecx, esp
		mov dword ptr [esp+20h], esp
		push ecx
		mov ecx, ebp
		__emit 0E8h
		__emit 080h
		__emit 010h
		__emit 09Ch
		__emit 0FFh   // call 0x2F28E
		push esi
		__emit 0E8h
		__emit 0FBh
		__emit 0E8h
		__emit 09Ch
		__emit 0FFh   // call 0x3CB0F
		add esp, 8h
		__emit 0E8h
		__emit 044h
		__emit 0ECh
		__emit 0FFh
		__emit 0FFh   // call 0x66CE60
		add esp, 8h
		mov bl, al
L09_66E221:
		test bl, bl
		je L05_66E2F7
		__emit 08Bh
		__emit 015h
		__emit 08Ch
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov edx, dword ptr [0x12f708c]
		test byte ptr [edx+48h], 40h
		je L10_66E25F
		push edi
		push ecx
		mov dword ptr [esp+1Ch], esp
		mov esi, esp
		push ecx
		mov eax, esp
		mov dword ptr [esp+20h], esp
		push eax
		mov ecx, ebp
		__emit 0E8h
		__emit 042h
		__emit 010h
		__emit 09Ch
		__emit 0FFh   // call 0x2F28E
		push esi
		__emit 0E8h
		__emit 0DFh
		__emit 04Ah
		__emit 09Bh
		__emit 0FFh   // call 0x22D31
		add esp, 8h
		__emit 0E8h
		__emit 006h
		__emit 0ECh
		__emit 0FFh
		__emit 0FFh   // call 0x66CE60
		add esp, 8h
		mov bl, al
L10_66E25F:
		test bl, bl
		je L05_66E2F7
		__emit 08Bh
		__emit 00Dh
		__emit 08Ch
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f708c]
		mov al, byte ptr [ecx+48h]
		test al, al
		jns L11_66E29E
		push edi
		push ecx
		mov dword ptr [esp+1Ch], esp
		mov esi, esp
		push ecx
		mov edx, esp
		mov dword ptr [esp+20h], esp
		push edx
		mov ecx, ebp
		__emit 0E8h
		__emit 003h
		__emit 010h
		__emit 09Ch
		__emit 0FFh   // call 0x2F28E
		push esi
		__emit 0E8h
		__emit 01Ah
		__emit 0BDh
		__emit 09Ah
		__emit 0FFh   // call 0x19FAB
		add esp, 8h
		__emit 0E8h
		__emit 0C7h
		__emit 0EBh
		__emit 0FFh
		__emit 0FFh   // call 0x66CE60
		add esp, 8h
		mov bl, al
L11_66E29E:
		test bl, bl
		je L05_66E2F7
		__emit 0A1h
		__emit 08Ch
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f708c]
		mov ecx, dword ptr [eax+48h]
		test ch, 1h
		je L12_66E2D9
		push edi
		push ecx
		mov dword ptr [esp+1Ch], esp
		mov esi, esp
		push ecx
		mov ecx, esp
		mov dword ptr [esp+20h], esp
		push ecx
		mov ecx, ebp
		__emit 0E8h
		__emit 0C8h
		__emit 00Fh
		__emit 09Ch
		__emit 0FFh   // call 0x2F28E
		push esi
		__emit 0E8h
		__emit 046h
		__emit 057h
		__emit 099h
		__emit 0FFh   // call 0x3A12
		add esp, 8h
		__emit 0E8h
		__emit 08Ch
		__emit 0EBh
		__emit 0FFh
		__emit 0FFh   // call 0x66CE60
		add esp, 8h
		mov bl, al
L12_66E2D9:
		test bl, bl
		je L05_66E2F7
		push edi
		push ecx
		mov edx, esp
		mov dword ptr [esp+1Ch], esp
		push edx
		mov ecx, ebp
		__emit 0E8h
		__emit 0A1h
		__emit 00Fh
		__emit 09Ch
		__emit 0FFh   // call 0x2F28E
		__emit 0E8h
		__emit 06Eh
		__emit 0EBh
		__emit 0FFh
		__emit 0FFh   // call 0x66CE60
		add esp, 8h
		mov bl, al
L05_66E2F7:
		__emit 0E8h
		__emit 0D0h
		__emit 098h
		__emit 09Dh
		__emit 0FFh   // call 0x47BCC
		pop edi
		pop esi
		pop ebp
		mov al, bl
		pop ebx
		ret
	}
}

// The part of a path after the last separator. First of the three helpers
// GetPreviewFromMap calls, matching the ZH reference's
// GetBaseFileFromFile(GetFileFromPath(path)) nesting. BFME's version tests for
// '.' as well as '\\', which the reference does not.
__declspec(naked) void *GetFileFromPath(void *out, void *path)
{
	__asm {
		push 0FFFFFFFFh
		push 10448E1h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		mov dword ptr [esp], 0h
		mov eax, dword ptr [esp+18h]
		test eax, eax
		mov dword ptr [esp+0Ch], 1h
		je L00_66D3F6
		lea ecx,  [eax+8h]
		movzx eax, word ptr [eax+4h]
		jmp L01_66D3FD
L00_66D3F6:
		mov ecx, 107388Bh
		xor eax, eax
L01_66D3FD:
		add eax, ecx
		cmp eax, ecx
		push esi
		je L02_66D411
L04_66D404:
		mov dl, byte ptr [eax-1h]
		dec eax
		cmp dl, 5Ch
		je L03_66D449
		cmp eax, ecx
		jne L04_66D404
L02_66D411:
		mov esi, dword ptr [esp+18h]
		lea eax,  [esp+1Ch]
		push eax
		mov ecx, esi
		__emit 0E8h
		__emit 03Fh
		__emit 0A7h
		__emit 021h
		__emit 000h   // call 0x887B60
L05_66D421:
		lea ecx,  [esp+1Ch]
		mov byte ptr [esp+10h], 0h
		mov dword ptr [esp+4h], 1h
		__emit 0E8h
		__emit 009h
		__emit 0A5h
		__emit 021h
		__emit 000h   // call 0x887940
		mov ecx, dword ptr [esp+8h]
		mov eax, esi
		pop esi
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret
L03_66D449:
		mov esi, dword ptr [esp+18h]
		inc eax
		push eax
		mov ecx, esi
		__emit 0E8h
		__emit 06Ah
		__emit 0B7h
		__emit 021h
		__emit 000h   // call 0x888BC0
		jmp L05_66D421
	}
}

// A filename with its extension removed: reverseFind('.'), then copy the prefix
// through getBufferForRead. Second of GetPreviewFromMap's three calls.
__declspec(naked) void *GetBaseFileFromFile(void *out, void *path)
{
	__asm {
		push 0FFFFFFFFh
		push 1044969h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 8h
		push ebx
		push esi
		xor ebx, ebx
		push edi
		mov dword ptr [esp+10h], ebx
		mov edx, dword ptr [esp+28h]
		cmp edx, ebx
		mov edi, 1h
		mov dword ptr [esp+1Ch], edi
		je L00_66D57B
		movzx eax, word ptr [edx+4h]
		lea ecx,  [edx+8h]
		jmp L01_66D582
L00_66D57B:
		mov ecx, 107388Bh
		xor eax, eax
L01_66D582:
		add eax, ecx
		cmp eax, ecx
		je L02_66D592
L04_66D588:
		dec eax
		cmp byte ptr [eax], 2Eh
		je L03_66D5C7
		cmp eax, ecx
		jne L04_66D588
L02_66D592:
		mov esi, dword ptr [esp+24h]
		push 1336E50h
		mov ecx, esi
		__emit 0E8h
		__emit 0BEh
		__emit 0A5h
		__emit 021h
		__emit 000h   // call 0x887B60
		lea ecx,  [esp+28h]
		mov dword ptr [esp+10h], edi
		mov byte ptr [esp+1Ch], bl
		__emit 0E8h
		__emit 08Dh
		__emit 0A3h
		__emit 021h
		__emit 000h   // call 0x887940
		pop edi
		mov eax, esi
		pop esi
		pop ebx
		mov ecx, dword ptr [esp+8h]
		mov dword ptr fs:[0h], ecx
		add esp, 14h
		ret
L03_66D5C7:
		cmp edx, ebx
		lea ecx,  [edx+8h]
		jne L05_66D5D3
		mov ecx, 107388Bh
L05_66D5D3:
		sub eax, ecx
		push ebp
		mov ebp, eax
		mov dword ptr [esp+10h], ebx
		push ebp
		lea ecx,  [esp+14h]
		mov byte ptr [esp+24h], 2h
		__emit 0E8h
		__emit 0F5h
		__emit 0A5h
		__emit 021h
		__emit 000h   // call 0x887BE0
		mov ecx, dword ptr [esp+2Ch]
		cmp ecx, ebx
		lea esi,  [ecx+8h]
		jne L06_66D5FB
		mov esi, 107388Bh
L06_66D5FB:
		mov ecx, ebp
		mov edx, ecx
		shr ecx, 2h
		mov edi, eax
		rep movsd
		mov ecx, edx
		and ecx, 3h
		rep movsb
		mov esi, dword ptr [esp+28h]
		push eax
		mov ecx, esi
		mov byte ptr [eax+ebp], bl
		__emit 0E8h
		__emit 0A4h
		__emit 0B5h
		__emit 021h
		__emit 000h   // call 0x888BC0
		lea ecx,  [esp+10h]
		mov dword ptr [esp+14h], 1h
		mov byte ptr [esp+20h], 1h
		__emit 0E8h
		__emit 00Eh
		__emit 0A3h
		__emit 021h
		__emit 000h   // call 0x887940
		lea ecx,  [esp+2Ch]
		mov byte ptr [esp+20h], bl
		__emit 0E8h
		__emit 001h
		__emit 0A3h
		__emit 021h
		__emit 000h   // call 0x887940
		mov ecx, dword ptr [esp+18h]
		pop ebp
		pop edi
		mov eax, esi
		pop esi
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 14h
		ret
	}
}

// A path with its filename removed: reverseFind('\\'), then copy the prefix
// through getBufferForRead. Third of GetPreviewFromMap's three calls.
__declspec(naked) void *GetBasePathFromPath(void *out, void *path)
{
	__asm {
		push 0FFFFFFFFh
		push 10448A9h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 8h
		push ebx
		push esi
		xor ebx, ebx
		push edi
		mov dword ptr [esp+10h], ebx
		mov edx, dword ptr [esp+28h]
		cmp edx, ebx
		mov edi, 1h
		mov dword ptr [esp+1Ch], edi
		je L00_66D29B
		movzx eax, word ptr [edx+4h]
		lea ecx,  [edx+8h]
		jmp L01_66D2A2
L00_66D29B:
		mov ecx, 107388Bh
		xor eax, eax
L01_66D2A2:
		add eax, ecx
		cmp eax, ecx
		je L02_66D2B2
L04_66D2A8:
		dec eax
		cmp byte ptr [eax], 5Ch
		je L03_66D2E7
		cmp eax, ecx
		jne L04_66D2A8
L02_66D2B2:
		mov esi, dword ptr [esp+24h]
		push 1336E50h
		mov ecx, esi
		__emit 0E8h
		__emit 09Eh
		__emit 0A8h
		__emit 021h
		__emit 000h   // call 0x887B60
		lea ecx,  [esp+28h]
		mov dword ptr [esp+10h], edi
		mov byte ptr [esp+1Ch], bl
		__emit 0E8h
		__emit 06Dh
		__emit 0A6h
		__emit 021h
		__emit 000h   // call 0x887940
		pop edi
		mov eax, esi
		pop esi
		pop ebx
		mov ecx, dword ptr [esp+8h]
		mov dword ptr fs:[0h], ecx
		add esp, 14h
		ret
L03_66D2E7:
		cmp edx, ebx
		lea ecx,  [edx+8h]
		jne L05_66D2F3
		mov ecx, 107388Bh
L05_66D2F3:
		sub eax, ecx
		push ebp
		mov ebp, eax
		mov dword ptr [esp+10h], ebx
		push ebp
		lea ecx,  [esp+14h]
		mov byte ptr [esp+24h], 2h
		__emit 0E8h
		__emit 0D5h
		__emit 0A8h
		__emit 021h
		__emit 000h   // call 0x887BE0
		mov ecx, dword ptr [esp+2Ch]
		cmp ecx, ebx
		lea esi,  [ecx+8h]
		jne L06_66D31B
		mov esi, 107388Bh
L06_66D31B:
		mov ecx, ebp
		mov edx, ecx
		shr ecx, 2h
		mov edi, eax
		rep movsd
		mov ecx, edx
		and ecx, 3h
		rep movsb
		mov esi, dword ptr [esp+28h]
		push eax
		mov ecx, esi
		mov byte ptr [eax+ebp], bl
		__emit 0E8h
		__emit 084h
		__emit 0B8h
		__emit 021h
		__emit 000h   // call 0x888BC0
		lea ecx,  [esp+10h]
		mov dword ptr [esp+14h], 1h
		mov byte ptr [esp+20h], 1h
		__emit 0E8h
		__emit 0EEh
		__emit 0A5h
		__emit 021h
		__emit 000h   // call 0x887940
		lea ecx,  [esp+2Ch]
		mov byte ptr [esp+20h], bl
		__emit 0E8h
		__emit 0E1h
		__emit 0A5h
		__emit 021h
		__emit 000h   // call 0x887940
		mov ecx, dword ptr [esp+18h]
		pop ebp
		pop edi
		mov eax, esi
		pop esi
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 14h
		ret
	}
}
