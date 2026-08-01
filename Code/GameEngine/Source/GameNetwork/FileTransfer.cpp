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
