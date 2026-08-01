// cl: /DNDEBUG /MD /GX

// EA's DirtySock middleware -- see commudp.cpp for why this directory name is an
// inference. Every function name here is retail's own: each body logs it.
// Parameter lists are not recovered yet; these are naked bodies and the
// extern "C" __cdecl name does not encode them.

extern "C" {
	int CommSRPResolve();
	int CommSRPSend();
	int CommSRPListen();
	int CommSRPConnect();
}

// Always fails: "Resolve functionality not supported by CommSRP".
__declspec(naked) int CommSRPResolve()
{
	__asm {
		push ebp
		mov ebp, esp
		push 12C4C68h
		__emit 0E8h
		__emit 013h
		__emit 090h
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 4h
		or eax, 0FFFFFFFFh
		cmp ebp, esp
		__emit 0E8h
		__emit 088h
		__emit 01Dh
		__emit 01Eh
		__emit 000h   // call 0x9F7502
		pop ebp
		ret
	}
}

// Queues an outbound packet. Reports "CommSRPSend: input queue full" and
// "CommSRP: Oversized packet send (%d bytes)".
__declspec(naked) int CommSRPSend()
{
	__asm {
		push ebp
		mov ebp, esp
		sub esp, 0Ch
		mov dword ptr [ebp-0Ch], 0CCCCCCCCh
		mov dword ptr [ebp-8h], 0CCCCCCCCh
		mov dword ptr [ebp-4h], 0CCCCCCCCh
		mov eax, dword ptr [ebp+8h]
		cmp dword ptr [eax+90h], 3h
		je L00_8158E1
		mov eax, 0FFFFFFFEh
		jmp L01_815A94
L00_8158E1:
		mov ecx, dword ptr [ebp+8h]
		mov eax, dword ptr [ecx+0B8h]
		mov edx, dword ptr [ebp+8h]
		add eax, dword ptr [edx+0B0h]
		mov ecx, dword ptr [ebp+8h]
		cdq
		idiv dword ptr [ecx+0B4h]
		mov eax, dword ptr [ebp+8h]
		cmp edx, dword ptr [eax+0BCh]
		jne L02_81591C
		push 12C4CA8h
		__emit 0E8h
		__emit 06Eh
		__emit 08Eh
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 4h
		xor eax, eax
		jmp L01_815A94
L02_81591C:
		mov ecx, dword ptr [ebp+8h]
		mov edx, dword ptr [ecx+0B0h]
		sub edx, 0Bh
		cmp dword ptr [ebp+10h], edx
		jle L03_815948
		mov eax, dword ptr [ebp+10h]
		push eax
		push 12C4CC8h
		__emit 0E8h
		__emit 045h
		__emit 08Eh
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 8h
		mov eax, 0FFFFFFFAh
		jmp L01_815A94
L03_815948:
		cmp dword ptr [ebp+10h], 0h
		jne L04_81598D
		mov ecx, dword ptr [ebp+8h]
		mov eax, dword ptr [ecx+0B8h]
		mov edx, dword ptr [ebp+8h]
		add eax, dword ptr [edx+0B4h]
		mov ecx, dword ptr [ebp+8h]
		sub eax, dword ptr [ecx+0BCh]
		mov ecx, dword ptr [ebp+8h]
		cdq
		idiv dword ptr [ecx+0B4h]
		mov ecx, dword ptr [ebp+8h]
		mov eax, edx
		cdq
		idiv dword ptr [ecx+0B0h]
		mov dword ptr [ebp-8h], eax
		mov eax, dword ptr [ebp-8h]
		add eax, 1h
		jmp L01_815A94
L04_81598D:
		mov edx, dword ptr [ebp+8h]
		mov eax, dword ptr [edx+0C0h]
		mov ecx, dword ptr [ebp+8h]
		add eax, dword ptr [ecx+0B8h]
		mov dword ptr [ebp-4h], eax
		mov edx, dword ptr [ebp-4h]
		mov eax, dword ptr [ebp+10h]
		mov dword ptr [edx+4h], eax
		mov ecx, dword ptr [ebp+10h]
		push ecx
		mov edx, dword ptr [ebp+0Ch]
		push edx
		mov eax, dword ptr [ebp-4h]
		add eax, 9h
		push eax
		__emit 0E8h
		__emit 0F9h
		__emit 01Bh
		__emit 01Eh
		__emit 000h   // call 0x9F75B8
		add esp, 0Ch
		mov ecx, dword ptr [ebp+14h]
		and ecx, 1h
		je L05_815A29
		mov edx, dword ptr [ebp+8h]
		movzx eax, byte ptr [edx+0CCh]
		add eax, 40h
		mov ecx, dword ptr [ebp-4h]
		mov byte ptr [ecx+8h], al
		mov edx, dword ptr [ebp+8h]
		mov eax, dword ptr [edx+0CCh]
		add eax, 1h
		mov ecx, dword ptr [ebp+8h]
		mov dword ptr [ecx+0CCh], eax
		mov edx, dword ptr [ebp+8h]
		mov eax, dword ptr [edx+0CCh]
		and eax, 3Fh
		mov ecx, dword ptr [ebp+8h]
		mov dword ptr [ecx+0CCh], eax
		mov edx, dword ptr [ebp-4h]
		push edx
		mov eax, dword ptr [ebp+8h]
		push eax
		__emit 0E8h
		__emit 06Ch
		__emit 0FCh
		__emit 0FFh
		__emit 0FFh   // call 0x815680
		add esp, 8h
		mov dword ptr [ebp-8h], eax
		cmp dword ptr [ebp-8h], 0h
		jle L06_815A27
		mov dword ptr [ebp-8h], 1h
L06_815A27:
		jmp L07_815A7C
L05_815A29:
		mov ecx, dword ptr [ebp+8h]
		movzx edx, byte ptr [ecx+0D4h]
		add edx, 80h
		mov eax, dword ptr [ebp-4h]
		mov byte ptr [eax+8h], dl
		mov ecx, dword ptr [ebp+8h]
		mov edx, dword ptr [ecx+0D4h]
		add edx, 1h
		mov eax, dword ptr [ebp+8h]
		mov dword ptr [eax+0D4h], edx
		mov ecx, dword ptr [ebp+8h]
		mov edx, dword ptr [ecx+0D4h]
		and edx, 3Fh
		mov eax, dword ptr [ebp+8h]
		mov dword ptr [eax+0D4h], edx
		mov ecx, dword ptr [ebp-4h]
		push ecx
		mov edx, dword ptr [ebp+8h]
		push edx
		__emit 0E8h
		__emit 03Ah
		__emit 000h
		__emit 000h
		__emit 000h   // call 0x815AB0
		add esp, 8h
		mov dword ptr [ebp-8h], eax
L07_815A7C:
		cmp dword ptr [ebp-8h], 0h
		jle L08_815A8A
		mov eax, dword ptr [ebp-8h]
		mov dword ptr [ebp-0Ch], eax
		jmp L09_815A91
L08_815A8A:
		mov dword ptr [ebp-0Ch], 1h
L09_815A91:
		mov eax, dword ptr [ebp-0Ch]
L01_815A94:
		add esp, 0Ch
		cmp ebp, esp
		__emit 0E8h
		__emit 064h
		__emit 01Ah
		__emit 01Eh
		__emit 000h   // call 0x9F7502
		mov esp, ebp
		pop ebp
		ret
	}
}

// Binds and listens, logging "CommSRPListen: Error %d binding socket".
__declspec(naked) int CommSRPListen()
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
		mov eax, dword ptr [ebp+8h]
		cmp dword ptr [eax+90h], 0h
		jne L00_816693
		mov ecx, dword ptr [ebp+8h]
		cmp dword ptr [ecx+7Ch], 0h
		je L01_81669D
L00_816693:
		mov eax, 0FFFFFFFEh
		jmp L02_816879
L01_81669D:
		mov word ptr [ebp-40h], 2h
		mov word ptr [ebp-3Eh], 0h
		mov dword ptr [ebp-3Ch], 0h
		mov dword ptr [ebp-38h], 0h
		mov dword ptr [ebp-34h], 0h
		mov edx, dword ptr [ebp+0Ch]
		push edx
		lea eax,  [ebp-1Ch]
		push eax
		lea ecx,  [ebp-10h]
		push ecx
		lea edx,  [ebp-28h]
		push edx
		__emit 0E8h
		__emit 0FDh
		__emit 096h
		__emit 0FEh
		__emit 0FFh   // call 0x7FFDD0
		add esp, 10h
		and eax, 2h
		jne L03_8166E5
		mov eax, 0FFFFFFFDh
		jmp L02_816879
L03_8166E5:
		mov eax, dword ptr [ebp-10h]
		sar eax, 8h
		mov byte ptr [ebp-3Eh], al
		mov cl, byte ptr [ebp-10h]
		mov byte ptr [ebp-3Dh], cl
		mov edx, dword ptr [ebp+8h]
		push edx
		__emit 0E8h
		__emit 013h
		__emit 002h
		__emit 000h
		__emit 000h   // call 0x816910
		add esp, 4h
		push 0h
		push 2h
		push 2h
		__emit 0E8h
		__emit 0C5h
		__emit 06Bh
		__emit 0FEh
		__emit 0FFh   // call 0x7FD2D0
		add esp, 0Ch
		mov dword ptr [ebp-48h], eax
		mov eax, dword ptr [ebp-48h]
		push eax
		mov ecx, dword ptr [ebp+8h]
		push ecx
		__emit 0E8h
		__emit 0D2h
		__emit 0EDh
		__emit 0FFh
		__emit 0FFh   // call 0x8154F0
		add esp, 8h
		mov edx, dword ptr [ebp+8h]
		cmp dword ptr [edx+7Ch], 0h
		jne L04_816734
		mov eax, 0FFFFFFFCh
		jmp L02_816879
L04_816734:
		push 10h
		lea eax,  [ebp-40h]
		push eax
		mov ecx, dword ptr [ebp+8h]
		mov edx, dword ptr [ecx+7Ch]
		push edx
		__emit 0E8h
		__emit 0CAh
		__emit 06Dh
		__emit 0FEh
		__emit 0FFh   // call 0x7FD510
		add esp, 0Ch
		mov dword ptr [ebp-8h], eax
		cmp dword ptr [ebp-8h], 0h
		jge L05_81678A
		mov eax, dword ptr [ebp-8h]
		push eax
		push 12C4CF4h
		__emit 0E8h
		__emit 020h
		__emit 080h
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 8h
		mov ecx, dword ptr [ebp+8h]
		mov edx, dword ptr [ecx+7Ch]
		push edx
		__emit 0E8h
		__emit 081h
		__emit 06Ch
		__emit 0FEh
		__emit 0FFh   // call 0x7FD3F0
		add esp, 4h
		push 0h
		mov eax, dword ptr [ebp+8h]
		push eax
		__emit 0E8h
		__emit 073h
		__emit 0EDh
		__emit 0FFh
		__emit 0FFh   // call 0x8154F0
		add esp, 8h
		mov eax, 0FFFFFFFBh
		jmp L02_816879
L05_81678A:
		push 0C15B50h
		mov ecx, dword ptr [ebp+8h]
		push ecx
		push 64h
		push 2h
		mov edx, dword ptr [ebp+8h]
		mov eax, dword ptr [edx+7Ch]
		push eax
		__emit 0E8h
		__emit 0DDh
		__emit 076h
		__emit 0FEh
		__emit 0FFh   // call 0x7FDE80
		add esp, 14h
		cmp dword ptr [ebp-28h], 0h
		je L06_81686A
		cmp dword ptr [ebp-1Ch], 0h
		jne L07_8167BF
		mov ecx, dword ptr [ebp-10h]
		add ecx, 1h
		mov dword ptr [ebp-1Ch], ecx
L07_8167BF:
		mov edx, dword ptr [ebp+8h]
		mov word ptr [edx+80h], 2h
		mov eax, dword ptr [ebp+8h]
		mov word ptr [eax+82h], 0h
		mov ecx, dword ptr [ebp+8h]
		mov dword ptr [ecx+84h], 0h
		mov edx, dword ptr [ebp+8h]
		mov dword ptr [edx+88h], 0h
		mov eax, dword ptr [ebp+8h]
		mov dword ptr [eax+8Ch], 0h
		mov ecx, dword ptr [ebp-28h]
		mov dword ptr [ebp-4Ch], ecx
		mov edx, dword ptr [ebp+8h]
		mov al, byte ptr [ebp-4Ch]
		mov byte ptr [edx+87h], al
		mov ecx, dword ptr [ebp-4Ch]
		shr ecx, 8h
		mov dword ptr [ebp-4Ch], ecx
		mov edx, dword ptr [ebp+8h]
		mov al, byte ptr [ebp-4Ch]
		mov byte ptr [edx+86h], al
		mov ecx, dword ptr [ebp-4Ch]
		shr ecx, 8h
		mov dword ptr [ebp-4Ch], ecx
		mov edx, dword ptr [ebp+8h]
		mov al, byte ptr [ebp-4Ch]
		mov byte ptr [edx+85h], al
		mov ecx, dword ptr [ebp-4Ch]
		shr ecx, 8h
		mov dword ptr [ebp-4Ch], ecx
		mov edx, dword ptr [ebp+8h]
		mov al, byte ptr [ebp-4Ch]
		mov byte ptr [edx+84h], al
		mov ecx, dword ptr [ebp-1Ch]
		sar ecx, 8h
		mov edx, dword ptr [ebp+8h]
		mov byte ptr [edx+82h], cl
		mov eax, dword ptr [ebp+8h]
		mov cl, byte ptr [ebp-1Ch]
		mov byte ptr [eax+83h], cl
L06_81686A:
		mov edx, dword ptr [ebp+8h]
		mov dword ptr [edx+90h], 2h
		xor eax, eax
L02_816879:
		push edx
		mov ecx, ebp
		push eax
		__emit 08Dh
		__emit 015h
		__emit 0A1h
		__emit 068h
		__emit 0C1h
		__emit 000h   // lea edx, [0xc168a1]
		__emit 0E8h
		__emit 09Dh
		__emit 00Ch
		__emit 01Eh
		__emit 000h   // call 0x9F7525
		pop eax
		pop edx
		mov ecx, dword ptr [ebp-4h]
		__emit 0E8h
		__emit 062h
		__emit 00Ch
		__emit 01Eh
		__emit 000h   // call 0x9F74F4
		pop edi
		add esp, 4Ch
		cmp ebp, esp
		__emit 0E8h
		__emit 065h
		__emit 00Ch
		__emit 01Eh
		__emit 000h   // call 0x9F7502
		mov esp, ebp
		pop ebp
		ret
	}
}

// Connects out, logging "CommSRPConnect: Error %d binding socket".
__declspec(naked) int CommSRPConnect()
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
		mov eax, dword ptr [ebp+8h]
		cmp dword ptr [eax+90h], 0h
		jne L00_8169A3
		mov ecx, dword ptr [ebp+8h]
		cmp dword ptr [ecx+7Ch], 0h
		je L01_8169AD
L00_8169A3:
		mov eax, 0FFFFFFFEh
		jmp L02_816B6B
L01_8169AD:
		mov edx, dword ptr [ebp+0Ch]
		push edx
		lea eax,  [ebp-28h]
		push eax
		lea ecx,  [ebp-34h]
		push ecx
		lea edx,  [ebp-40h]
		push edx
		__emit 0E8h
		__emit 00Eh
		__emit 094h
		__emit 0FEh
		__emit 0FFh   // call 0x7FFDD0
		add esp, 10h
		and eax, 3h
		cmp eax, 3h
		je L03_8169D7
		mov eax, 0FFFFFFFDh
		jmp L02_816B6B
L03_8169D7:
		cmp dword ptr [ebp-28h], 0h
		jne L04_8169EC
		mov eax, dword ptr [ebp-34h]
		mov dword ptr [ebp-28h], eax
		mov ecx, dword ptr [ebp-34h]
		add ecx, 1h
		mov dword ptr [ebp-34h], ecx
L04_8169EC:
		mov edx, dword ptr [ebp+8h]
		push edx
		__emit 0E8h
		__emit 01Bh
		__emit 0FFh
		__emit 0FFh
		__emit 0FFh   // call 0x816910
		add esp, 4h
		push 0h
		push 2h
		push 2h
		__emit 0E8h
		__emit 0CDh
		__emit 068h
		__emit 0FEh
		__emit 0FFh   // call 0x7FD2D0
		add esp, 0Ch
		mov dword ptr [ebp-48h], eax
		mov eax, dword ptr [ebp-48h]
		push eax
		mov ecx, dword ptr [ebp+8h]
		push ecx
		__emit 0E8h
		__emit 0DAh
		__emit 0EAh
		__emit 0FFh
		__emit 0FFh   // call 0x8154F0
		add esp, 8h
		mov edx, dword ptr [ebp+8h]
		cmp dword ptr [edx+7Ch], 0h
		jne L05_816A2C
		mov eax, 0FFFFFFFCh
		jmp L02_816B6B
L05_816A2C:
		mov word ptr [ebp-18h], 2h
		mov word ptr [ebp-16h], 0h
		mov dword ptr [ebp-14h], 0h
		mov dword ptr [ebp-10h], 0h
		mov dword ptr [ebp-0Ch], 0h
		mov eax, dword ptr [ebp-34h]
		sar eax, 8h
		mov byte ptr [ebp-16h], al
		mov cl, byte ptr [ebp-34h]
		mov byte ptr [ebp-15h], cl
		push 10h
		lea edx,  [ebp-18h]
		push edx
		mov eax, dword ptr [ebp+8h]
		mov ecx, dword ptr [eax+7Ch]
		push ecx
		__emit 0E8h
		__emit 0A2h
		__emit 06Ah
		__emit 0FEh
		__emit 0FFh   // call 0x7FD510
		add esp, 0Ch
		mov dword ptr [ebp-20h], eax
		cmp dword ptr [ebp-20h], 0h
		jge L06_816A95
		mov edx, dword ptr [ebp-20h]
		push edx
		push 12C4D1Ch
		__emit 0E8h
		__emit 0F8h
		__emit 07Ch
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 8h
		mov eax, 0FFFFFFFBh
		jmp L02_816B6B
L06_816A95:
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
		mov edx, dword ptr [ebp-40h]
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
		mov edx, dword ptr [ebp-28h]
		sar edx, 8h
		mov eax, dword ptr [ebp+8h]
		mov byte ptr [eax+82h], dl
		mov ecx, dword ptr [ebp+8h]
		mov dl, byte ptr [ebp-28h]
		mov byte ptr [ecx+83h], dl
		push 0C15B50h
		mov eax, dword ptr [ebp+8h]
		push eax
		push 64h
		push 2h
		mov ecx, dword ptr [ebp+8h]
		mov edx, dword ptr [ecx+7Ch]
		push edx
		__emit 0E8h
		__emit 027h
		__emit 073h
		__emit 0FEh
		__emit 0FFh   // call 0x7FDE80
		add esp, 14h
		mov eax, dword ptr [ebp+8h]
		mov dword ptr [eax+90h], 1h
		xor eax, eax
L02_816B6B:
		push edx
		mov ecx, ebp
		push eax
		__emit 08Dh
		__emit 015h
		__emit 093h
		__emit 06Bh
		__emit 0C1h
		__emit 000h   // lea edx, [0xc16b93]
		__emit 0E8h
		__emit 0ABh
		__emit 009h
		__emit 01Eh
		__emit 000h   // call 0x9F7525
		pop eax
		pop edx
		mov ecx, dword ptr [ebp-4h]
		__emit 0E8h
		__emit 070h
		__emit 009h
		__emit 01Eh
		__emit 000h   // call 0x9F74F4
		pop edi
		add esp, 4Ch
		cmp ebp, esp
		__emit 0E8h
		__emit 073h
		__emit 009h
		__emit 01Eh
		__emit 000h   // call 0x9F7502
		mov esp, ebp
		pop ebp
		ret
	}
}
