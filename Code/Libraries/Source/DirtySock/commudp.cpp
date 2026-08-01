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

extern "C" {
	int CommUdpProcess();
	int CommUdpSetup();
	int CommUdpPoke();
	int CommUdpListen();
	int CommUDPSend();
}

// The CommUDP tick. Logs "CommUdpProcess: got RAW_PACKET_INIT", closes the
// connection on timeout, and handles poke packets -- including retargeting the
// peer when one arrives from an address other than the expected one.
__declspec(naked) int CommUdpProcess()
{
	__asm {
		push ebp
		mov ebp, esp
		sub esp, 44h
		push esi
		push edi
		lea edi,  [ebp-44h]
		mov ecx, 11h
		mov eax, 0CCCCCCCCh
		rep stosd
		__emit 0A1h
		__emit 0B0h
		__emit 0BDh
		__emit 02Dh
		__emit 001h   // mov eax, dword ptr [0x12dbdb0]
		mov dword ptr [ebp-4h], eax
		mov dword ptr [ebp-14h], 0h
		mov dword ptr [ebp-1Ch], 0h
		push 10h
		push 0h
		lea eax,  [ebp-30h]
		push eax
		__emit 0E8h
		__emit 05Ah
		__emit 0FAh
		__emit 01Dh
		__emit 000h   // call 0x9F75C4
		add esp, 0Ch
		__emit 0C7h
		__emit 005h
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 0FFh
		__emit 0FFh
		__emit 0FFh
		__emit 0FFh   // mov dword ptr [0x130ad10], 0xffffffff
		mov dword ptr [ebp-38h], 0h
		__emit 08Bh
		__emit 00Dh
		__emit 088h
		__emit 0B1h
		__emit 030h
		__emit 001h   // mov ecx, dword ptr [0x130b188]
		mov dword ptr [ebp-18h], ecx
		jmp L00_817B92
L05_817B89:
		mov edx, dword ptr [ebp-18h]
		mov eax, dword ptr [edx+78h]
		mov dword ptr [ebp-18h], eax
L00_817B92:
		cmp dword ptr [ebp-18h], 0h
		je L01_817C5D
		mov ecx, dword ptr [ebp-18h]
		cmp dword ptr [ecx+7Ch], 0h
		je L02_817C58
		mov edx, dword ptr [ebp-18h]
		mov eax, dword ptr [edx+7Ch]
		cmp eax, dword ptr [ebp-38h]
		je L02_817C58
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [ecx+7Ch]
		mov dword ptr [ebp-38h], edx
		mov dword ptr [ebp-0Ch], 10h
		lea eax,  [ebp-0Ch]
		push eax
		lea ecx,  [ebp-30h]
		push ecx
		push 0h
		push 220h
		push 130AD18h
		mov edx, dword ptr [ebp-38h]
		push edx
		__emit 0E8h
		__emit 06Bh
		__emit 05Eh
		__emit 0FEh
		__emit 0FFh   // call 0x7FDA50
		add esp, 18h
		mov dword ptr [ebp-0Ch], eax
		cmp dword ptr [ebp-0Ch], 0h
		jle L02_817C58
		mov eax, dword ptr [ebp-0Ch]
		sub eax, 8h
		__emit 0A3h
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov dword ptr [0x130ad10], eax
		movzx ecx, byte ptr [ebp-28h]
		shl ecx, 8h
		movzx edx, byte ptr [ebp-27h]
		or ecx, edx
		shl ecx, 8h
		movzx eax, byte ptr [ebp-26h]
		or ecx, eax
		shl ecx, 8h
		movzx edx, byte ptr [ebp-25h]
		or ecx, edx
		__emit 089h
		__emit 00Dh
		__emit 014h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov dword ptr [0x130ad14], ecx
		__emit 083h
		__emit 03Dh
		__emit 018h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 001h   // cmp dword ptr [0x130ad18], 1
		jne L03_817C37
		push 12C4E3Ch
		__emit 0E8h
		__emit 04Ch
		__emit 06Bh
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 4h
L03_817C37:
		__emit 083h
		__emit 03Dh
		__emit 018h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 002h   // cmp dword ptr [0x130ad18], 2
		jne L04_817C4D
		push 12C4E64h
		__emit 0E8h
		__emit 036h
		__emit 06Bh
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 4h
L04_817C4D:
		mov eax, dword ptr [ebp-14h]
		add eax, 1h
		mov dword ptr [ebp-14h], eax
		jmp L01_817C5D
L02_817C58:
		jmp L05_817B89
L01_817C5D:
		__emit 08Bh
		__emit 00Dh
		__emit 088h
		__emit 0B1h
		__emit 030h
		__emit 001h   // mov ecx, dword ptr [0x130b188]
		mov dword ptr [ebp-18h], ecx
		jmp L06_817C71
L34_817C68:
		mov edx, dword ptr [ebp-18h]
		mov eax, dword ptr [edx+78h]
		mov dword ptr [ebp-18h], eax
L06_817C71:
		cmp dword ptr [ebp-18h], 0h
		je L07_818199
		__emit 0E8h
		__emit 080h
		__emit 06Dh
		__emit 0FEh
		__emit 0FFh   // call 0x7FEA00
		mov dword ptr [ebp+8h], eax
		cmp dword ptr [ebp-1Ch], 0h
		jne L08_817CC9
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [ebp-38h]
		cmp edx, dword ptr [ecx+7Ch]
		jne L08_817CC9
		mov eax, dword ptr [ebp-18h]
		cmp dword ptr [eax+90h], 3h
		jne L08_817CC9
		__emit 083h
		__emit 03Dh
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 000h   // cmp dword ptr [0x130ad10], 0
		jne L08_817CC9
		__emit 083h
		__emit 03Dh
		__emit 018h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 001h   // cmp dword ptr [0x130ad18], 1
		jne L08_817CC9
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [ecx+94h]
		__emit 03Bh
		__emit 015h
		__emit 01Ch
		__emit 0ADh
		__emit 030h
		__emit 001h   // cmp edx, dword ptr [0x130ad1c]
		jne L08_817CC9
		mov eax, dword ptr [ebp-18h]
		mov dword ptr [ebp-1Ch], eax
L08_817CC9:
		__emit 083h
		__emit 03Dh
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 000h   // cmp dword ptr [0x130ad10], 0
		jl L09_817F32
		mov ecx, dword ptr [ebp-18h]
		cmp dword ptr [ecx+90h], 3h
		je L09_817F32
		mov edx, dword ptr [ebp-18h]
		cmp dword ptr [edx+90h], 5h
		je L09_817F32
		mov eax, dword ptr [ebp-18h]
		mov ecx, dword ptr [ebp-38h]
		cmp ecx, dword ptr [eax+7Ch]
		jne L09_817F32
		lea edx,  [ebp-30h]
		push edx
		mov eax, dword ptr [ebp-18h]
		add eax, 80h
		push eax
		__emit 0E8h
		__emit 009h
		__emit 07Ah
		__emit 0FEh
		__emit 0FFh   // call 0x7FF720
		add esp, 8h
		test eax, eax
		jne L09_817F32
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [ecx+60h]
		__emit 003h
		__emit 015h
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h   // add edx, dword ptr [0x130ad10]
		mov eax, dword ptr [ebp-18h]
		mov dword ptr [eax+60h], edx
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [ecx+68h]
		add edx, 1h
		mov eax, dword ptr [ebp-18h]
		mov dword ptr [eax+68h], edx
		__emit 083h
		__emit 03Dh
		__emit 018h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 001h   // cmp dword ptr [0x130ad18], 1
		je L10_817D5E
		__emit 083h
		__emit 03Dh
		__emit 018h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 002h   // cmp dword ptr [0x130ad18], 2
		je L10_817D5E
		__emit 083h
		__emit 03Dh
		__emit 018h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 003h   // cmp dword ptr [0x130ad18], 3
		jne L11_817D78
L10_817D5E:
		lea ecx,  [ebp-30h]
		push ecx
		push 130AD10h
		mov edx, dword ptr [ebp-18h]
		push edx
		__emit 0E8h
		__emit 090h
		__emit 006h
		__emit 000h
		__emit 000h   // call 0x818400
		add esp, 0Ch
		jmp L12_817F28
L11_817D78:
		mov eax, dword ptr [ebp-18h]
		cmp dword ptr [eax+90h], 4h
		je L13_817D89
		jmp L12_817F28
L13_817D89:
		__emit 083h
		__emit 03Dh
		__emit 018h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 004h   // cmp dword ptr [0x130ad18], 4
		jne L14_817DB7
		mov ecx, dword ptr [ebp-18h]
		__emit 08Bh
		__emit 015h
		__emit 014h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov edx, dword ptr [0x130ad14]
		mov dword ptr [ecx+0DCh], edx
		push 130AD10h
		mov eax, dword ptr [ebp-18h]
		push eax
		__emit 0E8h
		__emit 011h
		__emit 009h
		__emit 000h
		__emit 000h   // call 0x8186C0
		add esp, 8h
		jmp L12_817F28
L14_817DB7:
		__emit 081h
		__emit 03Dh
		__emit 018h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 000h
		__emit 000h
		__emit 000h
		__emit 010h   // cmp dword ptr [0x130ad18], 0x10000000
		jbe L15_817EF7
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [ecx+0ACh]
		mov dword ptr [ebp-3Ch], edx
		__emit 0A1h
		__emit 018h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov eax, dword ptr [0x130ad18]
		shr eax, 1Ch
		mov dword ptr [ebp-40h], eax
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov ecx, dword ptr [0x130ad14]
		__emit 089h
		__emit 00Dh
		__emit 064h
		__emit 0AFh
		__emit 030h
		__emit 001h   // mov dword ptr [0x130af64], ecx
		__emit 08Bh
		__emit 015h
		__emit 018h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov edx, dword ptr [0x130ad18]
		and edx, 0FFFFFFFh
		sub edx, dword ptr [ebp-40h]
		__emit 089h
		__emit 015h
		__emit 068h
		__emit 0AFh
		__emit 030h
		__emit 001h   // mov dword ptr [0x130af68], edx
		__emit 0A1h
		__emit 01Ch
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov eax, dword ptr [0x130ad1c]
		__emit 0A3h
		__emit 06Ch
		__emit 0AFh
		__emit 030h
		__emit 001h   // mov dword ptr [0x130af6c], eax
		mov ecx, dword ptr [ebp-18h]
		__emit 08Bh
		__emit 015h
		__emit 014h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov edx, dword ptr [0x130ad14]
		mov dword ptr [ecx+0DCh], edx
		jmp L16_817E23
L22_817E1A:
		mov eax, dword ptr [ebp-40h]
		sub eax, 1h
		mov dword ptr [ebp-40h], eax
L16_817E23:
		cmp dword ptr [ebp-40h], 0h
		jl L17_817EF5
		cmp dword ptr [ebp-40h], 0h
		jle L18_817E56
		__emit 08Bh
		__emit 00Dh
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov ecx, dword ptr [0x130ad10]
		sub ecx, 1h
		__emit 089h
		__emit 00Dh
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov dword ptr [0x130ad10], ecx
		__emit 08Bh
		__emit 015h
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov edx, dword ptr [0x130ad10]
		movzx eax, byte ptr [edx+130AD20h]
		__emit 0A3h
		__emit 060h
		__emit 0AFh
		__emit 030h
		__emit 001h   // mov dword ptr [0x130af60], eax
		jmp L19_817E62
L18_817E56:
		__emit 08Bh
		__emit 00Dh
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov ecx, dword ptr [0x130ad10]
		__emit 089h
		__emit 00Dh
		__emit 060h
		__emit 0AFh
		__emit 030h
		__emit 001h   // mov dword ptr [0x130af60], ecx
L19_817E62:
		__emit 08Bh
		__emit 015h
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov edx, dword ptr [0x130ad10]
		__emit 02Bh
		__emit 015h
		__emit 060h
		__emit 0AFh
		__emit 030h
		__emit 001h   // sub edx, dword ptr [0x130af60]
		__emit 089h
		__emit 015h
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov dword ptr [0x130ad10], edx
		__emit 0A1h
		__emit 060h
		__emit 0AFh
		__emit 030h
		__emit 001h   // mov eax, dword ptr [0x130af60]
		push eax
		__emit 08Bh
		__emit 00Dh
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov ecx, dword ptr [0x130ad10]
		add ecx, 130AD20h
		push ecx
		push 130AF70h
		__emit 0E8h
		__emit 027h
		__emit 0F7h
		__emit 01Dh
		__emit 000h   // call 0x9F75B8
		add esp, 0Ch
		push 130AF60h
		mov edx, dword ptr [ebp-18h]
		push edx
		__emit 0E8h
		__emit 01Eh
		__emit 008h
		__emit 000h
		__emit 000h   // call 0x8186C0
		add esp, 8h
		push 130AF60h
		mov eax, dword ptr [ebp-18h]
		push eax
		__emit 0E8h
		__emit 02Dh
		__emit 009h
		__emit 000h
		__emit 000h   // call 0x8187E0
		add esp, 8h
		test eax, eax
		jge L20_817EC1
		mov dword ptr [ebp-40h], 0h
L20_817EC1:
		cmp dword ptr [ebp-40h], 0h
		jle L21_817EE1
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [ebp-3Ch]
		cmp edx, dword ptr [ecx+0ACh]
		je L21_817EE1
		mov eax, dword ptr [ebp-18h]
		mov ecx, dword ptr [eax+0ACh]
		mov dword ptr [ebp-3Ch], ecx
L21_817EE1:
		__emit 08Bh
		__emit 015h
		__emit 068h
		__emit 0AFh
		__emit 030h
		__emit 001h   // mov edx, dword ptr [0x130af68]
		add edx, 1h
		__emit 089h
		__emit 015h
		__emit 068h
		__emit 0AFh
		__emit 030h
		__emit 001h   // mov dword ptr [0x130af68], edx
		jmp L22_817E1A
L17_817EF5:
		jmp L12_817F28
L15_817EF7:
		mov eax, dword ptr [ebp-18h]
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov ecx, dword ptr [0x130ad14]
		mov dword ptr [eax+0DCh], ecx
		push 130AD10h
		mov edx, dword ptr [ebp-18h]
		push edx
		__emit 0E8h
		__emit 0ACh
		__emit 007h
		__emit 000h
		__emit 000h   // call 0x8186C0
		add esp, 8h
		push 130AD10h
		mov eax, dword ptr [ebp-18h]
		push eax
		__emit 0E8h
		__emit 0BBh
		__emit 008h
		__emit 000h
		__emit 000h   // call 0x8187E0
		add esp, 8h
L12_817F28:
		__emit 0C7h
		__emit 005h
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 0FFh
		__emit 0FFh
		__emit 0FFh
		__emit 0FFh   // mov dword ptr [0x130ad10], 0xffffffff
L09_817F32:
		mov ecx, dword ptr [ebp-18h]
		cmp dword ptr [ecx+90h], 2h
		jne L23_817F5D
		mov edx, dword ptr [ebp-18h]
		mov eax, dword ptr [ebp+8h]
		sub eax, dword ptr [edx+0D8h]
		cmp eax, 3E8h
		jbe L23_817F5D
		mov ecx, dword ptr [ebp-18h]
		push ecx
		__emit 0E8h
		__emit 0C6h
		__emit 006h
		__emit 000h
		__emit 000h   // call 0x818620
		add esp, 4h
L23_817F5D:
		mov edx, dword ptr [ebp-18h]
		cmp dword ptr [edx+90h], 4h
		jne L24_817F89
		mov eax, dword ptr [ebp-18h]
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [eax+0C8h]
		cmp edx, dword ptr [ecx+0C0h]
		je L24_817F89
		mov eax, dword ptr [ebp-18h]
		push eax
		__emit 0E8h
		__emit 0BAh
		__emit 0F6h
		__emit 0FFh
		__emit 0FFh   // call 0x817640
		add esp, 4h
L24_817F89:
		mov ecx, dword ptr [ebp-18h]
		cmp dword ptr [ecx+90h], 4h
		jne L25_817FFA
		mov edx, dword ptr [ebp-18h]
		mov eax, dword ptr [ebp+8h]
		sub eax, dword ptr [edx+0DCh]
		cmp eax, 1D4C0h
		jbe L25_817FFA
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [ebp+8h]
		sub edx, dword ptr [ecx+0D8h]
		cmp edx, 7D0h
		jae L25_817FFA
		push 12C4E8Ch
		__emit 0E8h
		__emit 0BAh
		__emit 067h
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 4h
		mov eax, dword ptr [ebp-18h]
		mov ecx, dword ptr [eax+0D8h]
		push ecx
		mov edx, dword ptr [ebp-18h]
		mov eax, dword ptr [edx+0DCh]
		push eax
		mov ecx, dword ptr [ebp+8h]
		push ecx
		push 12C4EB8h
		__emit 0E8h
		__emit 095h
		__emit 067h
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 10h
		mov edx, dword ptr [ebp-18h]
		push edx
		__emit 0E8h
		__emit 069h
		__emit 0EFh
		__emit 0FFh
		__emit 0FFh   // call 0x816F60
		add esp, 4h
L25_817FFA:
		mov eax, dword ptr [ebp-18h]
		cmp dword ptr [eax+90h], 3h
		jne L26_818035
		mov ecx, dword ptr [ebp-18h]
		movzx edx, word ptr [ecx+80h]
		cmp edx, 2h
		jne L26_818035
		mov eax, dword ptr [ebp-18h]
		mov ecx, dword ptr [eax+0D8h]
		add ecx, 3E8h
		cmp dword ptr [ebp+8h], ecx
		jbe L26_818035
		mov edx, dword ptr [ebp-18h]
		push edx
		__emit 0E8h
		__emit 0EEh
		__emit 009h
		__emit 000h
		__emit 000h   // call 0x818A20
		add esp, 4h
L26_818035:
		mov eax, dword ptr [ebp-18h]
		cmp dword ptr [eax+21Ch], 0h
		jne L27_818076
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [ecx+0E0h]
		add edx, 0FAh
		cmp dword ptr [ebp+8h], edx
		jbe L27_818076
		mov eax, dword ptr [ebp-18h]
		mov ecx, dword ptr [ebp+8h]
		mov dword ptr [eax+0E0h], ecx
		mov edx, dword ptr [ebp-18h]
		mov eax, dword ptr [edx+21Ch]
		or eax, 4h
		mov ecx, dword ptr [ebp-18h]
		mov dword ptr [ecx+21Ch], eax
L27_818076:
		mov edx, dword ptr [ebp-18h]
		cmp dword ptr [edx+218h], 0h
		jne L28_8180FC
		mov eax, dword ptr [ebp-18h]
		cmp dword ptr [eax+21Ch], 0h
		je L28_8180FC
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [ecx+218h]
		add edx, 1h
		mov eax, dword ptr [ebp-18h]
		mov dword ptr [eax+218h], edx
		mov ecx, dword ptr [ebp-18h]
		cmp dword ptr [ecx+220h], 0h
		je L29_8180D2
		mov esi, esp
		mov edx, dword ptr [ebp-18h]
		mov eax, dword ptr [edx+21Ch]
		push eax
		mov ecx, dword ptr [ebp-18h]
		push ecx
		mov edx, dword ptr [ebp-18h]
		call dword ptr [edx+220h]
		add esp, 8h
		cmp esi, esp
		__emit 0E8h
		__emit 030h
		__emit 0F4h
		__emit 01Dh
		__emit 000h   // call 0x9F7502
L29_8180D2:
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [ecx+218h]
		sub edx, 1h
		mov eax, dword ptr [ebp-18h]
		mov dword ptr [eax+218h], edx
		mov ecx, dword ptr [ebp-18h]
		mov dword ptr [ecx+21Ch], 0h
		__emit 0E8h
		__emit 007h
		__emit 069h
		__emit 0FEh
		__emit 0FFh   // call 0x7FEA00
		mov dword ptr [ebp+8h], eax
L28_8180FC:
		mov edx, dword ptr [ebp-18h]
		cmp dword ptr [edx+90h], 4h
		jne L30_818194
		mov eax, dword ptr [ebp-18h]
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [eax+0C8h]
		cmp edx, dword ptr [ecx+0C0h]
		jne L30_818194
		mov eax, dword ptr [ebp-18h]
		mov ecx, dword ptr [ebp+8h]
		sub ecx, dword ptr [eax+0D8h]
		mov dword ptr [ebp-44h], ecx
		cmp dword ptr [ebp-44h], 64h
		jbe L31_818149
		mov edx, dword ptr [ebp-18h]
		mov eax, dword ptr [ebp-18h]
		mov ecx, dword ptr [edx+0B0h]
		cmp ecx, dword ptr [eax+0ACh]
		jne L32_81817B
L31_818149:
		cmp dword ptr [ebp-44h], 64h
		jbe L33_818163
		mov edx, dword ptr [ebp-18h]
		mov eax, dword ptr [ebp-18h]
		mov ecx, dword ptr [edx+0C0h]
		cmp ecx, dword ptr [eax+0C4h]
		jne L32_81817B
L33_818163:
		cmp dword ptr [ebp-44h], 9C4h
		ja L32_81817B
		mov edx, dword ptr [ebp-18h]
		cmp dword ptr [edx+0B4h], 800h
		jl L30_818194
L32_81817B:
		mov eax, dword ptr [ebp-18h]
		mov dword ptr [eax+0B4h], 0h
		mov ecx, dword ptr [ebp-18h]
		push ecx
		__emit 0E8h
		__emit 03Fh
		__emit 009h
		__emit 000h
		__emit 000h   // call 0x818AD0
		add esp, 4h
L30_818194:
		jmp L34_817C68
L07_818199:
		__emit 083h
		__emit 03Dh
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 000h   // cmp dword ptr [0x130ad10], 0
		jl L35_818343
		__emit 083h
		__emit 03Dh
		__emit 018h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 005h   // cmp dword ptr [0x130ad18], 5
		jne L35_818343
		movzx edx, word ptr [ebp-30h]
		cmp edx, 2h
		jne L35_818343
		movzx eax, byte ptr [ebp-2Ch]
		shl eax, 8h
		movzx ecx, byte ptr [ebp-2Bh]
		or eax, ecx
		shl eax, 8h
		movzx edx, byte ptr [ebp-2Ah]
		or eax, edx
		shl eax, 8h
		movzx ecx, byte ptr [ebp-29h]
		or eax, ecx
		push eax
		push 12C4EE0h
		__emit 0E8h
		__emit 096h
		__emit 065h
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 8h
		__emit 08Bh
		__emit 015h
		__emit 088h
		__emit 0B1h
		__emit 030h
		__emit 001h   // mov edx, dword ptr [0x130b188]
		mov dword ptr [ebp-18h], edx
		jmp L36_818201
L38_8181F8:
		mov eax, dword ptr [ebp-18h]
		mov ecx, dword ptr [eax+78h]
		mov dword ptr [ebp-18h], ecx
L36_818201:
		cmp dword ptr [ebp-18h], 0h
		je L35_818343
		mov edx, dword ptr [ebp-18h]
		cmp dword ptr [edx+90h], 2h
		jne L37_81833E
		mov eax, dword ptr [ebp-18h]
		movzx ecx, word ptr [eax+80h]
		cmp ecx, 2h
		jne L37_81833E
		mov edx, dword ptr [ebp-18h]
		mov eax, dword ptr [edx+94h]
		__emit 03Bh
		__emit 005h
		__emit 01Ch
		__emit 0ADh
		__emit 030h
		__emit 001h   // cmp eax, dword ptr [0x130ad1c]
		jne L37_81833E
		mov ecx, dword ptr [ebp-18h]
		movzx edx, byte ptr [ecx+84h]
		shl edx, 8h
		mov eax, dword ptr [ebp-18h]
		movzx ecx, byte ptr [eax+85h]
		or edx, ecx
		shl edx, 8h
		mov eax, dword ptr [ebp-18h]
		movzx ecx, byte ptr [eax+86h]
		or edx, ecx
		shl edx, 8h
		mov eax, dword ptr [ebp-18h]
		movzx ecx, byte ptr [eax+87h]
		or edx, ecx
		push edx
		push 12C4F0Ch
		__emit 0E8h
		__emit 0FBh
		__emit 064h
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 8h
		mov edx, dword ptr [ebp-18h]
		mov eax, dword ptr [ebp-38h]
		cmp eax, dword ptr [edx+7Ch]
		jne L37_81833E
		mov ecx, dword ptr [ebp-18h]
		movzx edx, byte ptr [ecx+82h]
		shl edx, 8h
		mov eax, dword ptr [ebp-18h]
		movzx ecx, byte ptr [eax+83h]
		or edx, ecx
		push edx
		mov edx, dword ptr [ebp-18h]
		movzx eax, byte ptr [edx+84h]
		shl eax, 8h
		mov ecx, dword ptr [ebp-18h]
		movzx edx, byte ptr [ecx+85h]
		or eax, edx
		shl eax, 8h
		mov ecx, dword ptr [ebp-18h]
		movzx edx, byte ptr [ecx+86h]
		or eax, edx
		shl eax, 8h
		mov ecx, dword ptr [ebp-18h]
		movzx edx, byte ptr [ecx+87h]
		or eax, edx
		push eax
		movzx eax, byte ptr [ebp-2Eh]
		shl eax, 8h
		movzx ecx, byte ptr [ebp-2Dh]
		or eax, ecx
		push eax
		movzx edx, byte ptr [ebp-2Ch]
		shl edx, 8h
		movzx eax, byte ptr [ebp-2Bh]
		or edx, eax
		shl edx, 8h
		movzx ecx, byte ptr [ebp-2Ah]
		or edx, ecx
		shl edx, 8h
		movzx eax, byte ptr [ebp-29h]
		or edx, eax
		push edx
		push 12C4F40h
		__emit 0E8h
		__emit 05Fh
		__emit 064h
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 14h
		push 10h
		lea ecx,  [ebp-30h]
		push ecx
		mov edx, dword ptr [ebp-18h]
		add edx, 80h
		push edx
		__emit 0E8h
		__emit 07Fh
		__emit 0F2h
		__emit 01Dh
		__emit 000h   // call 0x9F75B8
		add esp, 0Ch
		jmp L35_818343
L37_81833E:
		jmp L38_8181F8
L35_818343:
		cmp dword ptr [ebp-1Ch], 0h
		je L39_8183A3
		__emit 083h
		__emit 03Dh
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 000h   // cmp dword ptr [0x130ad10], 0
		jne L39_8183A3
		mov eax, dword ptr [ebp-1Ch]
		mov dword ptr [ebp-18h], eax
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [ecx+94h]
		__emit 03Bh
		__emit 015h
		__emit 01Ch
		__emit 0ADh
		__emit 030h
		__emit 001h   // cmp edx, dword ptr [0x130ad1c]
		jne L39_8183A3
		push 10h
		lea eax,  [ebp-30h]
		push eax
		mov ecx, dword ptr [ebp-18h]
		add ecx, 80h
		push ecx
		__emit 0E8h
		__emit 03Ah
		__emit 0F2h
		__emit 01Dh
		__emit 000h   // call 0x9F75B8
		add esp, 0Ch
		mov edx, dword ptr [ebp-18h]
		mov dword ptr [edx+90h], 4h
		lea eax,  [ebp-30h]
		push eax
		push 130AD10h
		mov ecx, dword ptr [ebp-18h]
		push ecx
		__emit 0E8h
		__emit 060h
		__emit 000h
		__emit 000h
		__emit 000h   // call 0x818400
		add esp, 0Ch
L39_8183A3:
		mov eax, dword ptr [ebp-14h]
		push edx
		mov ecx, ebp
		push eax
		__emit 08Dh
		__emit 015h
		__emit 0CFh
		__emit 083h
		__emit 0C1h
		__emit 000h   // lea edx, [0xc183cf]
		__emit 0E8h
		__emit 070h
		__emit 0F1h
		__emit 01Dh
		__emit 000h   // call 0x9F7525
		pop eax
		pop edx
		mov ecx, dword ptr [ebp-4h]
		__emit 0E8h
		__emit 035h
		__emit 0F1h
		__emit 01Dh
		__emit 000h   // call 0x9F74F4
		pop edi
		pop esi
		add esp, 44h
		cmp ebp, esp
		__emit 0E8h
		__emit 037h
		__emit 0F1h
		__emit 01Dh
		__emit 000h   // call 0x9F7502
		mov esp, ebp
		pop ebp
		ret
	}
}

// Answers an INIT with a CONN, and warns "commudp: warning - connident
// mismatch" when the connection identifier does not line up.
__declspec(naked) int CommUdpSetup()
{
	__asm {
		push ebp
		mov ebp, esp
		mov eax, dword ptr [ebp+0Ch]
		cmp dword ptr [eax], 0h
		je L00_818410
		jmp L01_8184F4
L00_818410:
		mov ecx, dword ptr [ebp+0Ch]
		mov edx, dword ptr [ebp+8h]
		mov eax, dword ptr [ecx+0Ch]
		cmp eax, dword ptr [edx+94h]
		je L02_818449
		push 12C4D9Ch
		__emit 0E8h
		__emit 055h
		__emit 063h
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 4h
		mov ecx, dword ptr [ebp+0Ch]
		cmp dword ptr [ecx+8h], 1h
		jne L03_818444
		mov edx, dword ptr [ebp+8h]
		mov dword ptr [edx+90h], 5h
L03_818444:
		jmp L01_8184F4
L02_818449:
		__emit 0E8h
		__emit 0B2h
		__emit 065h
		__emit 0FEh
		__emit 0FFh   // call 0x7FEA00
		sub eax, 3E8h
		mov ecx, dword ptr [ebp+8h]
		mov dword ptr [ecx+0DCh], eax
		mov edx, dword ptr [ebp+0Ch]
		cmp dword ptr [edx+8h], 1h
		jne L04_81849E
		mov eax, dword ptr [ebp+10h]
		push eax
		mov ecx, dword ptr [ebp+8h]
		push ecx
		__emit 0E8h
		__emit 08Eh
		__emit 000h
		__emit 000h
		__emit 000h   // call 0x818500
		add esp, 8h
		push 12C4DC4h
		__emit 0E8h
		__emit 001h
		__emit 063h
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 4h
		mov edx, dword ptr [ebp+0Ch]
		mov dword ptr [edx+8h], 2h
		mov eax, dword ptr [ebp+0Ch]
		push eax
		mov ecx, dword ptr [ebp+8h]
		push ecx
		__emit 0E8h
		__emit 097h
		__emit 0EBh
		__emit 0FFh
		__emit 0FFh   // call 0x817030
		add esp, 8h
		jmp L01_8184F4
L04_81849E:
		mov edx, dword ptr [ebp+0Ch]
		cmp dword ptr [edx+8h], 2h
		jne L05_8184D2
		mov eax, dword ptr [ebp+8h]
		cmp dword ptr [eax+90h], 2h
		jne L06_8184D0
		mov ecx, dword ptr [ebp+10h]
		push ecx
		mov edx, dword ptr [ebp+8h]
		push edx
		__emit 0E8h
		__emit 040h
		__emit 000h
		__emit 000h
		__emit 000h   // call 0x818500
		add esp, 8h
		mov eax, dword ptr [ebp+8h]
		mov dword ptr [eax+90h], 4h
L06_8184D0:
		jmp L01_8184F4
L05_8184D2:
		mov ecx, dword ptr [ebp+0Ch]
		cmp dword ptr [ecx+8h], 3h
		jne L01_8184F4
		mov edx, dword ptr [ebp+8h]
		cmp dword ptr [edx+90h], 4h
		jne L01_8184F4
		mov eax, dword ptr [ebp+8h]
		mov dword ptr [eax+90h], 5h
L01_8184F4:
		cmp ebp, esp
		__emit 0E8h
		__emit 007h
		__emit 0F0h
		__emit 01Dh
		__emit 000h   // call 0x9F7502
		pop ebp
		ret
	}
}

// Sends a poke packet to prod a peer whose address may have moved.
__declspec(naked) int CommUdpPoke()
{
	__asm {
		push ebp
		mov ebp, esp
		sub esp, 234h
		push edi
		lea edi,  [ebp-234h]
		mov ecx, 8Dh
		mov eax, 0CCCCCCCCh
		rep stosd
		__emit 0A1h
		__emit 0B0h
		__emit 0BDh
		__emit 02Dh
		__emit 001h   // mov eax, dword ptr [0x12dbdb0]
		mov dword ptr [ebp-4h], eax
		push 12C4E18h
		__emit 0E8h
		__emit 032h
		__emit 05Dh
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 4h
		mov dword ptr [ebp-230h], 0h
		mov dword ptr [ebp-228h], 5h
		mov eax, dword ptr [ebp+8h]
		mov ecx, dword ptr [eax+94h]
		mov dword ptr [ebp-224h], ecx
		lea edx,  [ebp-230h]
		push edx
		mov eax, dword ptr [ebp+8h]
		push eax
		__emit 0E8h
		__emit 0ACh
		__emit 0E5h
		__emit 0FFh
		__emit 0FFh   // call 0x817030
		add esp, 8h
		push edx
		mov ecx, ebp
		push eax
		__emit 08Dh
		__emit 015h
		__emit 0B2h
		__emit 08Ah
		__emit 0C1h
		__emit 000h   // lea edx, [0xc18ab2]
		__emit 0E8h
		__emit 08Fh
		__emit 0EAh
		__emit 01Dh
		__emit 000h   // call 0x9F7525
		pop eax
		pop edx
		mov ecx, dword ptr [ebp-4h]
		__emit 0E8h
		__emit 054h
		__emit 0EAh
		__emit 01Dh
		__emit 000h   // call 0x9F74F4
		pop edi
		add esp, 234h
		cmp ebp, esp
		__emit 0E8h
		__emit 054h
		__emit 0EAh
		__emit 01Dh
		__emit 000h   // call 0x9F7502
		mov esp, ebp
		pop ebp
		ret
	}
}

// Puts the socket into listening mode for an incoming CommUDP connection.
__declspec(naked) int CommUdpListen()
{
	__asm {
		push ebp
		mov ebp, esp
		sub esp, 4Ch
		push edi
		lea edi,  [ebp-4Ch]
		mov ecx, 13h
		mov eax, 0CCCCCCCCh
		rep stosd
		__emit 0A1h
		__emit 0B0h
		__emit 0BDh
		__emit 02Dh
		__emit 001h   // mov eax, dword ptr [0x12dbdb0]
		mov dword ptr [ebp-4h], eax
		mov word ptr [ebp-44h], 2h
		mov word ptr [ebp-42h], 0h
		mov dword ptr [ebp-40h], 0h
		mov dword ptr [ebp-3Ch], 0h
		mov dword ptr [ebp-38h], 0h
		mov eax, dword ptr [ebp+0Ch]
		push eax
		lea ecx,  [ebp-1Ch]
		push ecx
		lea edx,  [ebp-10h]
		push edx
		lea eax,  [ebp-28h]
		push eax
		__emit 0E8h
		__emit 0ECh
		__emit 06Fh
		__emit 0FEh
		__emit 0FFh   // call 0x7FFDD0
		add esp, 10h
		and eax, 2h
		jne L00_818DF6
		mov eax, 0FFFFFFFDh
		jmp L01_818F5F
L00_818DF6:
		mov ecx, dword ptr [ebp-10h]
		sar ecx, 8h
		mov byte ptr [ebp-42h], cl
		mov dl, byte ptr [ebp-10h]
		mov byte ptr [ebp-41h], dl
		push 0h
		push 2h
		push 2h
		__emit 0E8h
		__emit 0C0h
		__emit 044h
		__emit 0FEh
		__emit 0FFh   // call 0x7FD2D0
		add esp, 0Ch
		mov dword ptr [ebp-30h], eax
		cmp dword ptr [ebp-30h], 0h
		jne L02_818E26
		mov eax, 0FFFFFFFCh
		jmp L01_818F5F
L02_818E26:
		lea eax,  [ebp-44h]
		push eax
		mov ecx, dword ptr [ebp-30h]
		push ecx
		mov edx, dword ptr [ebp+8h]
		push edx
		__emit 0E8h
		__emit 059h
		__emit 002h
		__emit 000h
		__emit 000h   // call 0x819090
		add esp, 0Ch
		mov dword ptr [ebp-8h], eax
		mov eax, dword ptr [ebp+0Ch]
		push eax
		mov ecx, dword ptr [ebp+8h]
		push ecx
		__emit 0E8h
		__emit 0A6h
		__emit 001h
		__emit 000h
		__emit 000h   // call 0x818FF0
		add esp, 8h
		mov edx, dword ptr [ebp+8h]
		mov eax, dword ptr [edx+94h]
		push eax
		mov ecx, dword ptr [ebp-10h]
		push ecx
		mov edx, dword ptr [ebp-8h]
		push edx
		push 12C4FFCh
		__emit 0E8h
		__emit 017h
		__emit 059h
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 10h
		cmp dword ptr [ebp-8h], 0h
		jne L03_818F4F
		cmp dword ptr [ebp-28h], 0h
		je L03_818F4F
		cmp dword ptr [ebp-1Ch], 0h
		jne L04_818E8F
		mov eax, dword ptr [ebp-10h]
		add eax, 1h
		mov dword ptr [ebp-1Ch], eax
L04_818E8F:
		mov ecx, dword ptr [ebp-1Ch]
		push ecx
		mov edx, dword ptr [ebp-28h]
		push edx
		push 12C5030h
		__emit 0E8h
		__emit 0DFh
		__emit 058h
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 0Ch
		mov eax, dword ptr [ebp+8h]
		mov word ptr [eax+80h], 2h
		mov ecx, dword ptr [ebp+8h]
		mov word ptr [ecx+82h], 0h
		mov edx, dword ptr [ebp+8h]
		mov dword ptr [edx+84h], 0h
		mov eax, dword ptr [ebp+8h]
		mov dword ptr [eax+88h], 0h
		mov ecx, dword ptr [ebp+8h]
		mov dword ptr [ecx+8Ch], 0h
		mov edx, dword ptr [ebp-28h]
		mov dword ptr [ebp-4Ch], edx
		mov eax, dword ptr [ebp+8h]
		mov cl, byte ptr [ebp-4Ch]
		mov byte ptr [eax+87h], cl
		mov edx, dword ptr [ebp-4Ch]
		shr edx, 8h
		mov dword ptr [ebp-4Ch], edx
		mov eax, dword ptr [ebp+8h]
		mov cl, byte ptr [ebp-4Ch]
		mov byte ptr [eax+86h], cl
		mov edx, dword ptr [ebp-4Ch]
		shr edx, 8h
		mov dword ptr [ebp-4Ch], edx
		mov eax, dword ptr [ebp+8h]
		mov cl, byte ptr [ebp-4Ch]
		mov byte ptr [eax+85h], cl
		mov edx, dword ptr [ebp-4Ch]
		shr edx, 8h
		mov dword ptr [ebp-4Ch], edx
		mov eax, dword ptr [ebp+8h]
		mov cl, byte ptr [ebp-4Ch]
		mov byte ptr [eax+84h], cl
		mov edx, dword ptr [ebp-1Ch]
		sar edx, 8h
		mov eax, dword ptr [ebp+8h]
		mov byte ptr [eax+82h], dl
		mov ecx, dword ptr [ebp+8h]
		mov dl, byte ptr [ebp-1Ch]
		mov byte ptr [ecx+83h], dl
L03_818F4F:
		mov eax, dword ptr [ebp+8h]
		mov dword ptr [eax+0D4h], 0h
		mov eax, dword ptr [ebp-8h]
L01_818F5F:
		push edx
		mov ecx, ebp
		push eax
		__emit 08Dh
		__emit 015h
		__emit 087h
		__emit 08Fh
		__emit 0C1h
		__emit 000h   // lea edx, [0xc18f87]
		__emit 0E8h
		__emit 0B7h
		__emit 0E5h
		__emit 01Dh
		__emit 000h   // call 0x9F7525
		pop eax
		pop edx
		mov ecx, dword ptr [ebp-4h]
		__emit 0E8h
		__emit 07Ch
		__emit 0E5h
		__emit 01Dh
		__emit 000h   // call 0x9F74F4
		pop edi
		add esp, 4Ch
		cmp ebp, esp
		__emit 0E8h
		__emit 07Fh
		__emit 0E5h
		__emit 01Dh
		__emit 000h   // call 0x9F7502
		mov esp, ebp
		pop ebp
		ret
	}
}

// Queues an outbound packet, rejecting anything past the limit with
// "CommUDP: Oversized packet send (%d bytes)".
__declspec(naked) int CommUDPSend()
{
	__asm {
		push ebp
		mov ebp, esp
		sub esp, 10h
		mov eax, 0CCCCCCCCh
		mov dword ptr [ebp-10h], eax
		mov dword ptr [ebp-0Ch], eax
		mov dword ptr [ebp-8h], eax
		mov dword ptr [ebp-4h], eax
		mov eax, dword ptr [ebp+8h]
		cmp dword ptr [eax+90h], 4h
		je L00_8173ED
		mov eax, 0FFFFFFFEh
		jmp L01_817623
L00_8173ED:
		mov ecx, dword ptr [ebp+8h]
		mov eax, dword ptr [ecx+0C0h]
		mov edx, dword ptr [ebp+8h]
		add eax, dword ptr [edx+0B8h]
		mov ecx, dword ptr [ebp+8h]
		cdq
		idiv dword ptr [ecx+0BCh]
		mov eax, dword ptr [ebp+8h]
		cmp edx, dword ptr [eax+0C4h]
		jne L02_81741B
		xor eax, eax
		jmp L01_817623
L02_81741B:
		mov ecx, dword ptr [ebp+8h]
		mov edx, dword ptr [ecx+0B8h]
		sub edx, 10h
		cmp dword ptr [ebp+10h], edx
		jle L03_817447
		mov eax, dword ptr [ebp+10h]
		push eax
		push 12C4FD0h
		__emit 0E8h
		__emit 046h
		__emit 073h
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 8h
		mov eax, 0FFFFFFFAh
		jmp L01_817623
L03_817447:
		cmp dword ptr [ebp+10h], 0h
		jne L04_81748C
		mov ecx, dword ptr [ebp+8h]
		mov eax, dword ptr [ecx+0C0h]
		mov edx, dword ptr [ebp+8h]
		add eax, dword ptr [edx+0BCh]
		mov ecx, dword ptr [ebp+8h]
		sub eax, dword ptr [ecx+0C4h]
		mov ecx, dword ptr [ebp+8h]
		cdq
		idiv dword ptr [ecx+0BCh]
		mov ecx, dword ptr [ebp+8h]
		mov eax, edx
		cdq
		idiv dword ptr [ecx+0B8h]
		mov dword ptr [ebp-4h], eax
		mov eax, dword ptr [ebp-4h]
		add eax, 1h
		jmp L01_817623
L04_81748C:
		mov edx, dword ptr [ebp+8h]
		mov eax, dword ptr [edx+0CCh]
		mov ecx, dword ptr [ebp+8h]
		add eax, dword ptr [ecx+0C0h]
		mov dword ptr [ebp-8h], eax
		mov edx, dword ptr [ebp-8h]
		mov eax, dword ptr [ebp+10h]
		mov dword ptr [edx], eax
		mov ecx, dword ptr [ebp+10h]
		push ecx
		mov edx, dword ptr [ebp+0Ch]
		push edx
		mov eax, dword ptr [ebp-8h]
		add eax, 10h
		push eax
		__emit 0E8h
		__emit 0FBh
		__emit 000h
		__emit 01Eh
		__emit 000h   // call 0x9F75B8
		add esp, 0Ch
		__emit 0E8h
		__emit 03Bh
		__emit 075h
		__emit 0FEh
		__emit 0FFh   // call 0x7FEA00
		mov ecx, dword ptr [ebp-8h]
		mov dword ptr [ecx+4h], eax
		mov edx, dword ptr [ebp+14h]
		and edx, 1h
		je L05_817523
		push 130AF38h
		__emit 0E8h
		__emit 0F3h
		__emit 076h
		__emit 0FEh
		__emit 0FFh   // call 0x7FEBD0
		add esp, 4h
		mov eax, dword ptr [ebp-8h]
		mov dword ptr [eax+8h], 6h
		mov ecx, dword ptr [ebp+8h]
		mov edx, dword ptr [ecx+0ACh]
		sub edx, 1h
		mov eax, dword ptr [ebp-8h]
		mov dword ptr [eax+0Ch], edx
		mov ecx, dword ptr [ebp-8h]
		push ecx
		mov edx, dword ptr [ebp+8h]
		push edx
		__emit 0E8h
		__emit 027h
		__emit 0FBh
		__emit 0FFh
		__emit 0FFh   // call 0x817030
		add esp, 8h
		push 130AF38h
		__emit 0E8h
		__emit 09Ah
		__emit 077h
		__emit 0FEh
		__emit 0FFh   // call 0x7FECB0
		add esp, 4h
		mov eax, 1h
		jmp L01_817623
L05_817523:
		mov eax, dword ptr [ebp-8h]
		mov ecx, dword ptr [ebp+8h]
		mov edx, dword ptr [ecx+0D0h]
		mov dword ptr [eax+8h], edx
		mov eax, dword ptr [ebp+8h]
		mov ecx, dword ptr [eax+0D0h]
		add ecx, 1h
		mov edx, dword ptr [ebp+8h]
		mov dword ptr [edx+0D0h], ecx
		mov eax, dword ptr [ebp+8h]
		mov ecx, dword ptr [eax+0ACh]
		sub ecx, 1h
		mov edx, dword ptr [ebp-8h]
		mov dword ptr [edx+0Ch], ecx
		mov eax, dword ptr [ebp+8h]
		mov eax, dword ptr [eax+0C0h]
		mov ecx, dword ptr [ebp+8h]
		add eax, dword ptr [ecx+0B8h]
		mov ecx, dword ptr [ebp+8h]
		cdq
		idiv dword ptr [ecx+0BCh]
		mov eax, dword ptr [ebp+8h]
		mov dword ptr [eax+0C0h], edx
		mov ecx, dword ptr [ebp+8h]
		mov eax, dword ptr [ecx+0C0h]
		mov edx, dword ptr [ebp+8h]
		add eax, dword ptr [edx+0BCh]
		mov ecx, dword ptr [ebp+8h]
		sub eax, dword ptr [ecx+0C4h]
		mov ecx, dword ptr [ebp+8h]
		cdq
		idiv dword ptr [ecx+0BCh]
		mov ecx, dword ptr [ebp+8h]
		mov eax, edx
		cdq
		idiv dword ptr [ecx+0B8h]
		mov dword ptr [ebp-4h], eax
		cmp dword ptr [ebp-4h], 10h
		jge L06_81760B
		push 130AF38h
		__emit 0E8h
		__emit 00Eh
		__emit 076h
		__emit 0FEh
		__emit 0FFh   // call 0x7FEBD0
		add esp, 4h
		mov edx, dword ptr [ebp+8h]
		push edx
		__emit 0E8h
		__emit 072h
		__emit 000h
		__emit 000h
		__emit 000h   // call 0x817640
		add esp, 4h
		__emit 083h
		__emit 03Dh
		__emit 008h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 000h   // cmp dword ptr [0x130ad08], 0
		je L07_8175FE
		__emit 0E8h
		__emit 021h
		__emit 074h
		__emit 0FEh
		__emit 0FFh   // call 0x7FEA00
		mov dword ptr [ebp-0Ch], eax
L09_8175E2:
		mov eax, dword ptr [ebp-0Ch]
		push eax
		__emit 0E8h
		__emit 045h
		__emit 005h
		__emit 000h
		__emit 000h   // call 0x817B30
		add esp, 4h
		test eax, eax
		jle L08_8175F4
		jmp L09_8175E2
L08_8175F4:
		__emit 0C7h
		__emit 005h
		__emit 008h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 000h
		__emit 000h
		__emit 000h
		__emit 000h   // mov dword ptr [0x130ad08], 0
L07_8175FE:
		push 130AF38h
		__emit 0E8h
		__emit 0A8h
		__emit 076h
		__emit 0FEh
		__emit 0FFh   // call 0x7FECB0
		add esp, 4h
L06_81760B:
		cmp dword ptr [ebp-4h], 0h
		jle L10_817619
		mov ecx, dword ptr [ebp-4h]
		mov dword ptr [ebp-10h], ecx
		jmp L11_817620
L10_817619:
		mov dword ptr [ebp-10h], 1h
L11_817620:
		mov eax, dword ptr [ebp-10h]
L01_817623:
		add esp, 10h
		cmp ebp, esp
		__emit 0E8h
		__emit 0D5h
		__emit 0FEh
		__emit 01Dh
		__emit 000h   // call 0x9F7502
		mov esp, ebp
		pop ebp
		ret
	}
}
