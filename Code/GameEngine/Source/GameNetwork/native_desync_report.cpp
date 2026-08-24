// cl: /DNDEBUG /MD /GX

typedef bool Bool;
typedef int Int;

typedef unsigned int UnsignedInt;

class GameLogicBFMEShim
{
public:
	UnsignedInt getCRC( Int mode );
};

extern GameLogicBFMEShim *TheGameLogic;

struct GameLogicBFMERetailLayout
{
	unsigned char m_padding[0x10C];
	Int m_gameMode;
};

// The client-side desync reporter. `this` is a caller-supplied stack record --
// 0x0006B910 passes `lea ecx, [esp+8]` -- whose first dword holds the CRC the
// frame was expected to produce; nothing else in the record is touched here.
// The class name is invented, like the other BFME-native names in this
// directory, because retail's is unknown.
class BFMEDesyncCheck
{
public:
	BFMEDesyncCheck();
	void writeReportIfMismatched();
};

// ??0BFMEDesyncCheck@@QAE@XZ
BFMEDesyncCheck::BFMEDesyncCheck()
{
	if (*reinterpret_cast<const unsigned char *>( 0x012ED4E4 ) != 0)
	{
		GameLogicBFMERetailLayout *logic = reinterpret_cast<GameLogicBFMERetailLayout *>( TheGameLogic );
		if (logic->m_gameMode != 8 && logic->m_gameMode != 4)
		{
			*reinterpret_cast<UnsignedInt *>( this ) = TheGameLogic->getCRC( 0 );
			return;
		}
	}
	*reinterpret_cast<UnsignedInt *>( this ) = 0;
}

// Recomputes GameLogic::getCRC and compares it against the expected value in
// this record's first dword. On a mismatch it formats CLIENT_DESYNC_%s.txt,
// opens it, and writes "Desync detected on frame %d on %u-%u-%u %u:%u:%u"
// with the wall-clock time. It returns immediately when the enable byte at
// 0x012ED4E4 is clear, or when TheGameLogic's mode at +0x10C is 4 or 8.
//
// This is the real lockstep desync reporter. The two large functions at
// 0x00655360 and 0x006386F0 that an earlier survey identified as such are
// GameSpy persistent-storage serialization -- their \desyncs%d\%d is a stats
// key, not a report.
__declspec(naked) void BFMEDesyncCheck::writeReportIfMismatched()
{
	__asm {
		mov eax, dword ptr fs:[0h]
		push 0FFFFFFFFh
		push 0FF2910h
		push eax
		__emit 0A0h
		__emit 0E4h
		__emit 0D4h
		__emit 02Eh
		__emit 001h   // mov al, byte ptr [0x12ed4e4]
		mov dword ptr fs:[0h], esp
		sub esp, 28h
		test al, al
		push esi
		mov esi, ecx
		je L00_065655
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		mov eax, dword ptr [ecx+10Ch]
		cmp eax, 8h
		je L00_065655
		cmp eax, 4h
		je L00_065655
		push 0h
		__emit 0E8h
		__emit 075h
		__emit 060h
		__emit 0FAh
		__emit 0FFh   // call 0xB532
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		mov ecx, dword ptr [ecx+10Ch]
		cmp ecx, 1h
		je L01_0654D7
		cmp ecx, 5h
		jne L00_065655
L01_0654D7:
		cmp dword ptr [esi], eax
		je L00_065655
		__emit 0A1h
		__emit 08Ch
		__emit 014h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f148c]
		test eax, eax
		je L02_065507
		push ecx
		mov dword ptr [esp+0Ch], esp
		mov ecx, esp
		push 10754A8h
		__emit 0E8h
		__emit 0E7h
		__emit 038h
		__emit 082h
		__emit 000h   // call 0x888DE0
		__emit 0A1h
		__emit 08Ch
		__emit 014h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f148c]
		mov edx, dword ptr [eax]
		push eax
		call dword ptr [edx+34h]
		add esp, 8h
L02_065507:
		mov dword ptr [esp+8h], 0h
		mov dword ptr [esp+34h], 0h
		mov dword ptr [esp+4h], 0h
		lea ecx,  [esp+14h]
		mov byte ptr [esp+34h], 1h
		__emit 0E8h
		__emit 072h
		__emit 00Fh
		__emit 0FCh
		__emit 0FFh   // call 0x2649F
		lea eax,  [esp+0Ch]
		push eax
		lea ecx,  [esp+18h]
		mov byte ptr [esp+38h], 2h
		__emit 0E8h
		__emit 09Dh
		__emit 072h
		__emit 0FBh
		__emit 0FFh   // call 0x1C7DD
		mov eax, dword ptr [eax]
		test eax, eax
		mov byte ptr [esp+34h], 3h
		je L03_065550
		add eax, 8h
		jmp L04_065555
L03_065550:
		mov eax, 107388Bh
L04_065555:
		push eax
		push ecx
		mov dword ptr [esp+18h], esp
		mov ecx, esp
		push 1075488h
		__emit 0E8h
		__emit 059h
		__emit 036h
		__emit 082h
		__emit 000h   // call 0x888BC0
		lea ecx,  [esp+10h]
		push ecx
		__emit 0E8h
		__emit 07Fh
		__emit 03Ah
		__emit 082h
		__emit 000h   // call 0x888FF0
		add esp, 0Ch
		lea ecx,  [esp+0Ch]
		mov byte ptr [esp+34h], 2h
		__emit 0E8h
		__emit 0BEh
		__emit 023h
		__emit 082h
		__emit 000h   // call 0x887940
		mov eax, dword ptr [esp+8h]
		test eax, eax
		je L05_06558F
		add eax, 8h
		jmp L06_065594
L05_06558F:
		mov eax, 107388Bh
L06_065594:
		push 1075484h
		push eax
		__emit 0FFh
		__emit 015h
		__emit 0BCh
		__emit 093h
		__emit 035h
		__emit 001h   // call dword ptr [0x13593bc]
		add esp, 8h
		lea edx,  [esp+1Ch]
		push edx
		mov esi, eax
		__emit 0FFh
		__emit 015h
		__emit 0B8h
		__emit 08Dh
		__emit 035h
		__emit 001h   // call dword ptr [0x1358db8]
		movzx eax, word ptr [esp+28h]
		movzx ecx, word ptr [esp+26h]
		movzx edx, word ptr [esp+24h]
		push eax
		movzx eax, word ptr [esp+20h]
		push ecx
		movzx ecx, word ptr [esp+2Ah]
		push edx
		movzx edx, word ptr [esp+2Ah]
		push eax
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		mov eax, dword ptr [eax+3Ch]
		push ecx
		push edx
		push eax
		push ecx
		mov dword ptr [esp+30h], esp
		mov ecx, esp
		push 1075444h
		__emit 0E8h
		__emit 0D2h
		__emit 035h
		__emit 082h
		__emit 000h   // call 0x888BC0
		lea ecx,  [esp+24h]
		push ecx
		__emit 0E8h
		__emit 0F8h
		__emit 039h
		__emit 082h
		__emit 000h   // call 0x888FF0
		mov eax, dword ptr [esp+28h]
		add esp, 24h
		test eax, eax
		je L07_06560C
		movzx ecx, word ptr [eax+4h]
		add eax, 8h
		jmp L08_065613
L07_06560C:
		xor ecx, ecx
		mov eax, 107388Bh
L08_065613:
		push esi
		push ecx
		push 1h
		push eax
		__emit 0FFh
		__emit 015h
		__emit 0F4h
		__emit 093h
		__emit 035h
		__emit 001h   // call dword ptr [0x13593f4]
		push esi
		__emit 0FFh
		__emit 015h
		__emit 0A0h
		__emit 093h
		__emit 035h
		__emit 001h   // call dword ptr [0x13593a0]
		add esp, 14h
		lea ecx,  [esp+14h]
		mov byte ptr [esp+34h], 1h
		__emit 0E8h
		__emit 055h
		__emit 078h
		__emit 0FBh
		__emit 0FFh   // call 0x1CE8B
		lea ecx,  [esp+4h]
		mov byte ptr [esp+34h], 0h
		__emit 0E8h
		__emit 0FCh
		__emit 022h
		__emit 082h
		__emit 000h   // call 0x887940
		lea ecx,  [esp+8h]
		mov dword ptr [esp+34h], 0FFFFFFFFh
		__emit 0E8h
		__emit 0EBh
		__emit 022h
		__emit 082h
		__emit 000h   // call 0x887940
L00_065655:
		mov ecx, dword ptr [esp+2Ch]
		mov dword ptr fs:[0h], ecx
		pop esi
		add esp, 34h
		ret
	}
}
