// cl: /DNDEBUG /MD /GX

// EA's DirtySock middleware -- see commudp.cpp for why this directory name is an
// inference. Every function name here is retail's own: each body logs it.
// Parameter lists are not recovered yet; these are naked bodies and the
// extern "C" __cdecl name does not encode them.

extern "C" {
	int NetGameUtilControl();
}

// The 'advf', 'minp', 'mout' and 'mwid' control selectors, each of which logs
// "NetGameUtilControl: setting '<sel>' to %d".
__declspec(naked) int NetGameUtilControl()
{
	__asm {
		push ebp
		mov ebp, esp
		cmp dword ptr [ebp+0Ch], 6D776964h
		jne L00_80E62E
		cmp dword ptr [ebp+10h], 200h
		jg L01_80E61D
		mov eax, dword ptr [ebp+10h]
		add eax, 0Eh
		mov ecx, dword ptr [ebp+8h]
		mov dword ptr [ecx+80h], eax
		mov edx, dword ptr [ebp+8h]
		mov eax, dword ptr [edx+80h]
		push eax
		push 12C47A8h
		__emit 0E8h
		__emit 068h
		__emit 001h
		__emit 0FFh
		__emit 0FFh   // call 0x7FE780
		add esp, 8h
		jmp L00_80E62E
L01_80E61D:
		mov ecx, dword ptr [ebp+10h]
		push ecx
		push 12C47D4h
		__emit 0E8h
		__emit 055h
		__emit 001h
		__emit 0FFh
		__emit 0FFh   // call 0x7FE780
		add esp, 8h
L00_80E62E:
		cmp dword ptr [ebp+0Ch], 6D696E70h
		jne L02_80E65A
		mov edx, dword ptr [ebp+8h]
		mov eax, dword ptr [ebp+10h]
		mov dword ptr [edx+88h], eax
		mov ecx, dword ptr [ebp+8h]
		mov edx, dword ptr [ecx+88h]
		push edx
		push 12C480Ch
		__emit 0E8h
		__emit 029h
		__emit 001h
		__emit 0FFh
		__emit 0FFh   // call 0x7FE780
		add esp, 8h
L02_80E65A:
		cmp dword ptr [ebp+0Ch], 6D6F7574h
		jne L03_80E686
		mov eax, dword ptr [ebp+8h]
		mov ecx, dword ptr [ebp+10h]
		mov dword ptr [eax+84h], ecx
		mov edx, dword ptr [ebp+8h]
		mov eax, dword ptr [edx+84h]
		push eax
		push 12C4838h
		__emit 0E8h
		__emit 0FDh
		__emit 000h
		__emit 0FFh
		__emit 0FFh   // call 0x7FE780
		add esp, 8h
L03_80E686:
		cmp dword ptr [ebp+0Ch], 61647666h
		jne L04_80E6B2
		mov ecx, dword ptr [ebp+8h]
		mov edx, dword ptr [ebp+10h]
		mov dword ptr [ecx+8Ch], edx
		mov eax, dword ptr [ebp+8h]
		mov ecx, dword ptr [eax+8Ch]
		push ecx
		push 12C4864h
		__emit 0E8h
		__emit 0D1h
		__emit 000h
		__emit 0FFh
		__emit 0FFh   // call 0x7FE780
		add esp, 8h
L04_80E6B2:
		cmp ebp, esp
		__emit 0E8h
		__emit 049h
		__emit 08Eh
		__emit 01Eh
		__emit 000h   // call 0x9F7502
		pop ebp
		ret
	}
}
