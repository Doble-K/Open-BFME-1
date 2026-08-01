// cl: /DNDEBUG /MD /GX

// EA's DirtySock CommUDP transport, which BFME uses for its GameSpy/online
// traffic. It has no counterpart in the vendored Zero Hour reference, and no
// __FILE__ string for it survives in the executable, so the directory name here
// is inferred from the module prefixes retail logs -- commudp, commtcp,
// protoadvt, NetGameUtil -- and from the sibling EA middleware that already
// lives under Code/Libraries/Source (Compression/EAC). Move it if better
// evidence turns up; only the `source` column of these rows has to follow.
//
// The function names are NOT invented: each of these bodies logs its own name.
// They are declared extern "C" because DirtySock is a C library.
//
// The lockstep path does not run through here -- that is SAGE's own udp.cpp.

extern "C" {
	int CommUDPWrite(void *ref, void *buffer, int length);
	int CommUDPConnect(void *ref, const char *addr, int bind, int peer);
	int CommUDPResolve(void *ref, const char *addr, char *buffer, int length, char divider);
}

// Always fails: it logs "CommUDPResolve: Resolve functionality not supported by
// CommUDP" and returns the error.
__declspec(naked) int CommUDPResolve(void *ref, const char *addr, char *buffer, int length, char divider)
{
	__asm {
		push ebp
		mov ebp, esp
		push 12C4F90h
		__emit 0E8h
		__emit 063h
		__emit 075h
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 4h
		or eax, 0FFFFFFFFh
		cmp ebp, esp
		__emit 0E8h
		__emit 0D8h
		__emit 002h
		__emit 01Eh
		__emit 000h   // call 0x9F7502
		pop ebp
		ret
	}
}

// Hands a datagram to the socket layer, logging "CommUDPWrite: SocketSendto
// returned %d" on the way out.
__declspec(naked) int CommUDPWrite(void *ref, void *buffer, int length)
{
	__asm {
		push ebp
		mov ebp, esp
		sub esp, 8h
		mov dword ptr [ebp-8h], 0CCCCCCCCh
		mov dword ptr [ebp-4h], 0CCCCCCCCh
		mov eax, dword ptr [ebp+0Ch]
		mov ecx, dword ptr [eax]
		add ecx, 8h
		mov dword ptr [ebp-8h], ecx
		push 10h
		mov edx, dword ptr [ebp+8h]
		add edx, 80h
		push edx
		push 0h
		mov eax, dword ptr [ebp-8h]
		push eax
		mov ecx, dword ptr [ebp+0Ch]
		add ecx, 8h
		push ecx
		mov edx, dword ptr [ebp+8h]
		mov eax, dword ptr [edx+7Ch]
		push eax
		__emit 0E8h
		__emit 0ACh
		__emit 068h
		__emit 0FEh
		__emit 0FFh   // call 0x7FD920
		add esp, 18h
		mov dword ptr [ebp-4h], eax
		mov ecx, dword ptr [ebp-4h]
		cmp ecx, dword ptr [ebp-8h]
		jne L00_8170C6
		__emit 0E8h
		__emit 079h
		__emit 079h
		__emit 0FEh
		__emit 0FFh   // call 0x7FEA00
		mov edx, dword ptr [ebp+8h]
		mov dword ptr [edx+0D8h], eax
		mov eax, dword ptr [ebp+8h]
		mov ecx, dword ptr [eax+5Ch]
		add ecx, dword ptr [ebp-8h]
		mov edx, dword ptr [ebp+8h]
		mov dword ptr [edx+5Ch], ecx
		mov eax, dword ptr [ebp+8h]
		mov ecx, dword ptr [eax+64h]
		add ecx, 1h
		mov edx, dword ptr [ebp+8h]
		mov dword ptr [edx+64h], ecx
		mov eax, dword ptr [ebp+0Ch]
		cmp dword ptr [eax+8h], 6h
		je L01_8170C4
		mov ecx, dword ptr [ebp+8h]
		mov dword ptr [ecx+0B4h], 0h
L01_8170C4:
		jmp L02_8170EA
L00_8170C6:
		mov edx, dword ptr [ebp-4h]
		push edx
		push 12C4D74h
		__emit 0E8h
		__emit 0ACh
		__emit 076h
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 8h
		mov eax, dword ptr [ebp+8h]
		mov ecx, dword ptr [ebp-4h]
		mov dword ptr [eax+0D4h], ecx
		mov dword ptr [ebp-4h], 0FFFFFFFFh
L02_8170EA:
		mov eax, dword ptr [ebp-4h]
		add esp, 8h
		cmp ebp, esp
		__emit 0E8h
		__emit 00Bh
		__emit 004h
		__emit 01Eh
		__emit 000h   // call 0x9F7502
		mov esp, ebp
		pop ebp
		ret
	}
}

// Opens the port. Logs "CommUdpConnect: addr=%08x, bind=%d, peer=%d
// connident=0x%08x" on entry and "CommUDPConnect: bind to %d failed with %d"
// when the bind is refused, then retries with port 0.
__declspec(naked) int CommUDPConnect(void *ref, const char *addr, int bind, int peer)
{
	__asm {
		push ebp
		mov ebp, esp
		sub esp, 64h
		push edi
		lea edi,  [ebp-64h]
		mov ecx, 19h
		mov eax, 0CCCCCCCCh
		rep stosd
		__emit 0A1h
		__emit 0B0h
		__emit 0BDh
		__emit 02Dh
		__emit 001h   // mov eax, dword ptr [0x12dbdb0]
		mov dword ptr [ebp-4h], eax
		mov word ptr [ebp-5Ch], 2h
		mov word ptr [ebp-5Ah], 0h
		mov dword ptr [ebp-58h], 0h
		mov dword ptr [ebp-54h], 0h
		mov dword ptr [ebp-50h], 0h
		mov word ptr [ebp-44h], 2h
		mov word ptr [ebp-42h], 0h
		mov dword ptr [ebp-40h], 0h
		mov dword ptr [ebp-3Ch], 0h
		mov dword ptr [ebp-38h], 0h
		mov eax, dword ptr [ebp+0Ch]
		push eax
		lea ecx,  [ebp-10h]
		push ecx
		lea edx,  [ebp-1Ch]
		push edx
		lea eax,  [ebp-28h]
		push eax
		__emit 0E8h
		__emit 05Bh
		__emit 06Ah
		__emit 0FEh
		__emit 0FFh   // call 0x7FFDD0
		add esp, 10h
		mov dword ptr [ebp-8h], eax
		mov ecx, dword ptr [ebp-8h]
		and ecx, 3h
		cmp ecx, 3h
		je L00_819390
		mov eax, 0FFFFFFFDh
		jmp L01_8194E8
L00_819390:
		cmp dword ptr [ebp-10h], 0h
		jne L02_8193A5
		mov edx, dword ptr [ebp-1Ch]
		mov dword ptr [ebp-10h], edx
		mov eax, dword ptr [ebp-1Ch]
		add eax, 1h
		mov dword ptr [ebp-1Ch], eax
L02_8193A5:
		mov ecx, dword ptr [ebp+0Ch]
		push ecx
		mov edx, dword ptr [ebp+8h]
		push edx
		__emit 0E8h
		__emit 03Eh
		__emit 0FCh
		__emit 0FFh
		__emit 0FFh   // call 0x818FF0
		add esp, 8h
		mov eax, dword ptr [ebp+8h]
		mov ecx, dword ptr [eax+94h]
		push ecx
		mov edx, dword ptr [ebp-10h]
		push edx
		mov eax, dword ptr [ebp-1Ch]
		push eax
		mov ecx, dword ptr [ebp-28h]
		push ecx
		push 12C5050h
		__emit 0E8h
		__emit 0ABh
		__emit 053h
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 14h
		push 0h
		push 2h
		push 2h
		__emit 0E8h
		__emit 0EDh
		__emit 03Eh
		__emit 0FEh
		__emit 0FFh   // call 0x7FD2D0
		add esp, 0Ch
		mov dword ptr [ebp-30h], eax
		cmp dword ptr [ebp-30h], 0h
		jne L03_8193F9
		mov eax, 0FFFFFFFCh
		jmp L01_8194E8
L03_8193F9:
		mov edx, dword ptr [ebp-1Ch]
		sar edx, 8h
		mov byte ptr [ebp-42h], dl
		mov al, byte ptr [ebp-1Ch]
		mov byte ptr [ebp-41h], al
		push 10h
		lea ecx,  [ebp-44h]
		push ecx
		mov edx, dword ptr [ebp-30h]
		push edx
		__emit 0E8h
		__emit 0F9h
		__emit 040h
		__emit 0FEh
		__emit 0FFh   // call 0x7FD510
		add esp, 0Ch
		mov dword ptr [ebp-8h], eax
		cmp dword ptr [ebp-8h], 0h
		jge L04_819466
		mov eax, dword ptr [ebp-8h]
		push eax
		mov ecx, dword ptr [ebp-1Ch]
		push ecx
		push 12C5090h
		__emit 0E8h
		__emit 04Bh
		__emit 053h
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 0Ch
		mov byte ptr [ebp-42h], 0h
		mov byte ptr [ebp-41h], 0h
		push 10h
		lea edx,  [ebp-44h]
		push edx
		mov eax, dword ptr [ebp-30h]
		push eax
		__emit 0E8h
		__emit 0C1h
		__emit 040h
		__emit 0FEh
		__emit 0FFh   // call 0x7FD510
		add esp, 0Ch
		mov dword ptr [ebp-8h], eax
		mov ecx, dword ptr [ebp-8h]
		push ecx
		push 12C50BCh
		__emit 0E8h
		__emit 01Dh
		__emit 053h
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 8h
L04_819466:
		cmp dword ptr [ebp-8h], 0h
		jge L05_81947F
		mov edx, dword ptr [ebp-30h]
		push edx
		__emit 0E8h
		__emit 07Bh
		__emit 03Fh
		__emit 0FEh
		__emit 0FFh   // call 0x7FD3F0
		add esp, 4h
		mov eax, 0FFFFFFFBh
		jmp L01_8194E8
L05_81947F:
		mov eax, dword ptr [ebp-28h]
		mov dword ptr [ebp-64h], eax
		mov cl, byte ptr [ebp-64h]
		mov byte ptr [ebp-55h], cl
		mov edx, dword ptr [ebp-64h]
		shr edx, 8h
		mov dword ptr [ebp-64h], edx
		mov al, byte ptr [ebp-64h]
		mov byte ptr [ebp-56h], al
		mov ecx, dword ptr [ebp-64h]
		shr ecx, 8h
		mov dword ptr [ebp-64h], ecx
		mov dl, byte ptr [ebp-64h]
		mov byte ptr [ebp-57h], dl
		mov eax, dword ptr [ebp-64h]
		shr eax, 8h
		mov dword ptr [ebp-64h], eax
		mov cl, byte ptr [ebp-64h]
		mov byte ptr [ebp-58h], cl
		mov edx, dword ptr [ebp-10h]
		sar edx, 8h
		mov byte ptr [ebp-5Ah], dl
		mov al, byte ptr [ebp-10h]
		mov byte ptr [ebp-59h], al
		mov ecx, dword ptr [ebp+8h]
		mov dword ptr [ecx+0D4h], 0h
		lea edx,  [ebp-5Ch]
		push edx
		mov eax, dword ptr [ebp-30h]
		push eax
		mov ecx, dword ptr [ebp+8h]
		push ecx
		__emit 0E8h
		__emit 0ABh
		__emit 000h
		__emit 000h
		__emit 000h   // call 0x819590
		add esp, 0Ch
L01_8194E8:
		push edx
		mov ecx, ebp
		push eax
		__emit 08Dh
		__emit 015h
		__emit 010h
		__emit 095h
		__emit 0C1h
		__emit 000h   // lea edx, [0xc19510]
		__emit 0E8h
		__emit 02Eh
		__emit 0E0h
		__emit 01Dh
		__emit 000h   // call 0x9F7525
		pop eax
		pop edx
		mov ecx, dword ptr [ebp-4h]
		__emit 0E8h
		__emit 0F3h
		__emit 0DFh
		__emit 01Dh
		__emit 000h   // call 0x9F74F4
		pop edi
		add esp, 64h
		cmp ebp, esp
		__emit 0E8h
		__emit 0F6h
		__emit 0DFh
		__emit 01Dh
		__emit 000h   // call 0x9F7502
		mov esp, ebp
		pop ebp
		ret
	}
}
