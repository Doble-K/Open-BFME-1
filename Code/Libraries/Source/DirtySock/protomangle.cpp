// cl: /DNDEBUG /MD /GX

// EA's DirtySock ProtoMangle -- see commudp.cpp for why this directory name is
// an inference. Both names here are retail's own: each body logs it.
// Parameter lists are not recovered; these are naked bodies and the
// extern "C" __cdecl name does not encode them.

extern "C" {
	int ProtoMangleCreate();
	int ProtoMangleDestroy();
}

// The public entry: it logs its whole argument list as
// "ProtoMangleCreate: Server:%s Port:%d GameID:%s LKey:%s" and calls the buffer
// allocator at 0x008042B0, which is why this one carries the name -- that helper
// logs under it too, so its own name stays unknown.
__declspec(naked) int ProtoMangleCreate()
{
	__asm {
		push ebp
		mov ebp, esp
		push ecx
		mov dword ptr [ebp-4h], 0CCCCCCCCh
		mov eax, dword ptr [ebp+14h]
		push eax
		mov ecx, dword ptr [ebp+10h]
		push ecx
		mov edx, dword ptr [ebp+0Ch]
		push edx
		mov eax, dword ptr [ebp+8h]
		push eax
		push 12C4218h
		__emit 0E8h
		__emit 00Bh
		__emit 0A6h
		__emit 0FFh
		__emit 0FFh   // call 0x7FE780
		add esp, 14h
		push 214h
		__emit 0E8h
		__emit 07Eh
		__emit 0BEh
		__emit 0FEh
		__emit 0FFh   // call 0x7F0000
		add esp, 4h
		mov dword ptr [ebp-4h], eax
		push 214h
		push 0h
		mov ecx, dword ptr [ebp-4h]
		push ecx
		__emit 0E8h
		__emit 02Ch
		__emit 034h
		__emit 01Fh
		__emit 000h   // call 0x9F75C4
		add esp, 0Ch
		push 400h
		mov edx, dword ptr [ebp-4h]
		add edx, 0C0h
		push edx
		__emit 0E8h
		__emit 001h
		__emit 001h
		__emit 000h
		__emit 000h   // call 0x8042B0
		add esp, 8h
		test eax, eax
		jg L00_8041C9
		mov eax, dword ptr [ebp-4h]
		push eax
		__emit 0E8h
		__emit 071h
		__emit 0BEh
		__emit 0FEh
		__emit 0FFh   // call 0x7F0030
		add esp, 4h
		mov dword ptr [ebp-4h], 0h
L00_8041C9:
		__emit 0E8h
		__emit 032h
		__emit 0A8h
		__emit 0FFh
		__emit 0FFh   // call 0x7FEA00
		xor edx, edx
		mov ecx, 1F40h
		div ecx
		add edx, 7D0h
		mov eax, dword ptr [ebp-4h]
		mov dword ptr [eax+20Ch], edx
		push 20h
		mov ecx, dword ptr [ebp+8h]
		push ecx
		mov edx, dword ptr [ebp-4h]
		add edx, 98h
		push edx
		__emit 0E8h
		__emit 055h
		__emit 000h
		__emit 000h
		__emit 000h   // call 0x804250
		add esp, 0Ch
		mov eax, dword ptr [ebp-4h]
		mov ecx, dword ptr [ebp+0Ch]
		mov dword ptr [eax+0B8h], ecx
		push 20h
		mov edx, dword ptr [ebp+10h]
		push edx
		mov eax, dword ptr [ebp-4h]
		add eax, 38h
		push eax
		__emit 0E8h
		__emit 034h
		__emit 000h
		__emit 000h
		__emit 000h   // call 0x804250
		add esp, 0Ch
		push 40h
		mov ecx, dword ptr [ebp+14h]
		push ecx
		mov edx, dword ptr [ebp-4h]
		add edx, 58h
		push edx
		__emit 0E8h
		__emit 01Fh
		__emit 000h
		__emit 000h
		__emit 000h   // call 0x804250
		add esp, 0Ch
		mov eax, dword ptr [ebp-4h]
		add esp, 4h
		cmp ebp, esp
		__emit 0E8h
		__emit 0C1h
		__emit 032h
		__emit 01Fh
		__emit 000h   // call 0x9F7502
		mov esp, ebp
		pop ebp
		ret
	}
}

// Logs "ProtoMangleDestroy: Shutting down" and releases the module.
__declspec(naked) int ProtoMangleDestroy()
{
	__asm {
		push ebp
		mov ebp, esp
		push 12C4250h
		__emit 0E8h
		__emit 043h
		__emit 0A4h
		__emit 0FFh
		__emit 0FFh   // call 0x7FE780
		add esp, 4h
		mov eax, dword ptr [ebp+8h]
		mov ecx, dword ptr [ebp+8h]
		mov edx, dword ptr [eax]
		cmp edx, dword ptr [ecx+4h]
		je L00_804359
		mov eax, dword ptr [ebp+8h]
		push eax
		__emit 0E8h
		__emit 02Ah
		__emit 000h
		__emit 000h
		__emit 000h   // call 0x804380
		add esp, 4h
L00_804359:
		mov ecx, dword ptr [ebp+8h]
		add ecx, 0C0h
		push ecx
		__emit 0E8h
		__emit 058h
		__emit 000h
		__emit 000h
		__emit 000h   // call 0x8043C0
		add esp, 4h
		mov edx, dword ptr [ebp+8h]
		push edx
		__emit 0E8h
		__emit 0BCh
		__emit 0BCh
		__emit 0FEh
		__emit 0FFh   // call 0x7F0030
		add esp, 4h
		cmp ebp, esp
		__emit 0E8h
		__emit 084h
		__emit 031h
		__emit 01Fh
		__emit 000h   // call 0x9F7502
		pop ebp
		ret
	}
}
