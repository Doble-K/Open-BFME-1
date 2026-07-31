// cl: /DNDEBUG /MD /GX

typedef bool Bool;

class BFMEConnectionManager
{
public:
	Bool isPlayerConnected(int playerID);
	Bool isPlayerConnectedForTimeout(int playerID, unsigned int timeout);
	Bool hasPacketRouterFrameStall();
	void processRequestFrameDataCommand(void *msg);
	Bool areFrameCommandsComplete(unsigned int frame, Bool debugSpewage);
	int getFrameHeadroom();
	void processInformPlayerLeaveFrameCommand(void *msg);
	void sendFrameInfo();
	Bool processIncomingCommand(void *ref);
	void *construct();
	void init();
	void computePlayerFrameRatios();
};

class BFMEDisconnectManager
{
public:
	Bool hasDisconnectScreenNotifyTimedOut(int playerID);
};

__declspec(naked) Bool BFMEConnectionManager::isPlayerConnected(int playerID)
{
	__asm {
		mov eax, dword ptr [esp+04h]
		cmp eax, dword ptr [ecx+12028h]
		jne notLocalPlayer
		mov al, 1
		ret 4
notLocalPlayer:
		push esi
		mov esi, dword ptr [ecx+eax*4+04h]
		test esi, esi
		je connected
		mov eax, dword ptr [esi+34Ch]
		test eax, eax
		jne testTimeout
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h
		mov dword ptr [esi+34Ch], eax
connected:
		mov al, 1
		pop esi
		ret 4
testTimeout:
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h
		mov edx, dword ptr [ecx+3Ch]
		__emit 03Bh
		__emit 015h
		__emit 050h
		__emit 0ADh
		__emit 00Eh
		__emit 001h
		jb earlyFrameTimeout
		mov edx, dword ptr [esi+34Ch]
		__emit 08Bh
		__emit 00Dh
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h
		mov ecx, dword ptr [ecx+0CBCh]
		sub eax, edx
		cmp ecx, eax
		sbb al, al
		inc al
		pop esi
		ret 4
earlyFrameTimeout:
		__emit 08Bh
		__emit 015h
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h
		mov ecx, dword ptr [edx+0CBCh]
		sub eax, dword ptr [esi+34Ch]
		shl ecx, 2
		cmp ecx, eax
		sbb al, al
		inc al
		pop esi
		ret 4
	}
}

__declspec(naked) Bool BFMEConnectionManager::isPlayerConnectedForTimeout(int playerID, unsigned int timeout)
{
	__asm {
		mov eax, dword ptr [esp+04h]
		cmp eax, dword ptr [ecx+12028h]
		jne notLocalPlayer
		mov al, 1
		ret 8
notLocalPlayer:
		push esi
		mov esi, dword ptr [ecx+eax*4+04h]
		test esi, esi
		je connected
		mov eax, dword ptr [esi+34Ch]
		test eax, eax
		jne testTimeout
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h
		mov dword ptr [esi+34Ch], eax
connected:
		mov al, 1
		pop esi
		ret 8
testTimeout:
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h
		mov edx, dword ptr [ecx+3Ch]
		__emit 03Bh
		__emit 015h
		__emit 050h
		__emit 0ADh
		__emit 00Eh
		__emit 001h
		jb earlyFrameTimeout
		mov edx, dword ptr [esi+34Ch]
		mov ecx, dword ptr [esp+0Ch]
		sub eax, edx
		cmp ecx, eax
		sbb al, al
		inc al
		pop esi
		ret 8
earlyFrameTimeout:
		__emit 08Bh
		__emit 00Dh
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h
		mov edx, dword ptr [esi+34Ch]
		mov ecx, dword ptr [ecx+0CBCh]
		sub eax, edx
		shl ecx, 2
		cmp ecx, eax
		sbb al, al
		inc al
		pop esi
		ret 8
	}
}

__declspec(naked) Bool BFMEConnectionManager::hasPacketRouterFrameStall()
{
	__asm {
		mov eax, dword ptr [ecx+12028h]
		cmp eax, dword ptr [ecx+1202Ch]
		je localIsRouter
		xor al, al
		ret
localIsRouter:
		__emit 08Bh
		__emit 015h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h
		push ebx
		mov ebx, dword ptr [edx+3Ch]
		cmp ebx, 5
		push edi
		jbe useStartupDelay
		__emit 0A1h
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h
		mov edi, dword ptr [eax+0CB4h]
		jmp haveDelay
useStartupDelay:
		mov edi, 3
haveDelay:
		push esi
		xor esi, esi
		lea eax, [ecx+04h]
		__emit 08Dh
		__emit 0A4h
		__emit 024h
		__emit 000h
		__emit 000h
		__emit 000h
		__emit 000h
scanPlayers:
		mov edx, dword ptr [eax]
		test edx, edx
		je nextPlayer
		cmp dword ptr [edx], 0FFFFFFFFh
		jne nextPlayer
		cmp esi, 8
		jae testFrameAge
		mov edx, dword ptr [eax+1207Ch]
		cmp edx, 1
		jl testFrameAge
		cmp edx, 3
		jle nextPlayer
testFrameAge:
		mov edx, dword ptr [eax+1205Ch]
		add edx, edi
		cmp edx, ebx
		jb stalled
nextPlayer:
		inc esi
		add eax, 4
		cmp esi, 8
		jl scanPlayers
		pop esi
		pop edi
		xor al, al
		pop ebx
		ret
stalled:
		mov esi, dword ptr [ecx+esi*4+12060h]
		__emit 03Bh
		__emit 035h
		__emit 004h
		__emit 077h
		__emit 02Fh
		__emit 001h
		je sameStalledFrame
		__emit 089h
		__emit 035h
		__emit 004h
		__emit 077h
		__emit 02Fh
		__emit 001h
sameStalledFrame:
		pop esi
		pop edi
		mov al, 1
		pop ebx
		ret
	}
}

__declspec(naked) Bool BFMEDisconnectManager::hasDisconnectScreenNotifyTimedOut(int playerID)
{
	__asm {
		push esi
		push edi
		mov edi, dword ptr [esp+0Ch]
		cmp edi, 0FFFFFFFFh
		mov esi, ecx
		jne validPlayer
		pop edi
		xor al, al
		pop esi
		ret 4
validPlayer:
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h
		sub eax, dword ptr [esi+edi*4+14h]
		__emit 08Bh
		__emit 00Dh
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h
		cmp eax, dword ptr [ecx+0CC0h]
		sbb al, al
		pop edi
		inc al
		pop esi
		ret 4
	}
}

__declspec(naked) void BFMEConnectionManager::processRequestFrameDataCommand(void *msg)
{
	__asm {
		sub esp, 8
		push ebp
		push edi
		mov edi, dword ptr [esp+14h]
		test edi, edi
		mov ebp, ecx
		je done
		push ebx
		mov ecx, edi
		__emit 0E8h
		__emit 058h
		__emit 037h
		__emit 09Ah
		__emit 0FFh
		mov ebx, eax
		mov ecx, edi
		mov dword ptr [esp+10h], ebx
		__emit 0E8h
		__emit 020h
		__emit 005h
		__emit 09Dh
		__emit 0FFh
		cmp eax, ebx
		mov dword ptr [esp+0Ch], eax
		jb popEbxDone
		__emit 08Bh
		__emit 00Dh
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h
		mov edx, dword ptr [ecx+0CB4h]
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h
		mov ecx, dword ptr [ecx+3Ch]
		push esi
		lea esi, [edx+eax]
		cmp esi, ecx
		jb popEsiDone
		cmp ecx, eax
		mov dword ptr [esp+1Ch], ecx
		lea eax, [esp+1Ch]
		jb haveStartPointer
		lea eax, [esp+10h]
haveStartPointer:
		cmp ecx, edx
		mov esi, dword ptr [eax]
		jb clampLowToZero
		sub ecx, edx
		cmp ecx, ebx
		mov dword ptr [esp+1Ch], ecx
		lea eax, [esp+1Ch]
		ja haveEndPointer
useOriginalEndPointer:
		lea eax, [esp+14h]
haveEndPointer:
		mov eax, dword ptr [eax]
		cmp eax, esi
		ja popEsiDone
		mov edx, dword ptr [edi+0Ch]
		push esi
		push eax
		push edx
		mov ecx, ebp
		__emit 0E8h
		__emit 099h
		__emit 07Eh
		__emit 09Ah
		__emit 0FFh
popEsiDone:
		pop esi
popEbxDone:
		pop ebx
done:
		pop edi
		pop ebp
		add esp, 8
		ret 4
clampLowToZero:
		mov dword ptr [esp+1Ch], 0
		jmp useOriginalEndPointer
	}
}

// The readiness gate the frame scheduler consults (0x00681F70 calls it with
// (frame, 0); the second argument is accepted and ignored). Sums
// getCommandCount(frame) over the eight FrameDataManagers at this+0x120E4,
// skipping null and quitting ones, and compares the total against the LOCAL
// manager's getFrameCommandCount(frame), which the FRAMEINFO path stores as the
// announced expected total. Zero Hour instead matches counts per player.
__declspec(naked) Bool BFMEConnectionManager::areFrameCommandsComplete(unsigned int frame, Bool debugSpewage)
{
	__asm {
		push ebx
		push ebp
		push esi
		mov ebx, ecx
		push edi
		xor edi, edi
		lea esi,  [ebx+120E4h]
		mov ebp, 8h
nextSlot:
		mov ecx, dword ptr [esi]
		test ecx, ecx
		je skipSlot
		__emit 0E8h
		__emit 0DEh
		__emit 002h
		__emit 09Ch
		__emit 0FFh   // call 0x236DC
		test al, al
		jne skipSlot
		mov eax, dword ptr [esp+14h]
		mov ecx, dword ptr [esi]
		push eax
		__emit 0E8h
		__emit 084h
		__emit 043h
		__emit 09Bh
		__emit 0FFh   // call 0x17792
		add edi, eax
skipSlot:
		add esi, 4h
		dec ebp
		jne nextSlot
		mov ecx, dword ptr [esp+14h]
		mov edx, dword ptr [ebx+12028h]
		push ecx
		mov ecx, dword ptr [ebx+edx*4+120E4h]
		__emit 0E8h
		__emit 076h
		__emit 0A3h
		__emit 09Dh
		__emit 0FFh   // call 0x3D7A3
		cmp eax, edi
		pop edi
		pop esi
		pop ebp
		sete al
		pop ebx
		ret 8h
	}
}

// Frames of headroom. Off the packet router that is the shared ceiling at
// this+0x1205C minus the current frame plus one -- the same expression the
// scheduler returns. As router it is the current frame minus the furthest-ahead
// connected player's frame plus one, so the router cannot outrun its clients.
// The player scan is unrolled four slots at a time, reading m_connections
// (this+0x04) as this+0x12060-0x1205C.
__declspec(naked) int BFMEConnectionManager::getFrameHeadroom()
{
	__asm {
		mov eax, dword ptr [ecx+12028h]
		cmp eax, dword ptr [ecx+1202Ch]
		je routerPath
		mov eax, dword ptr [ecx+1205Ch]
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		mov edx, dword ptr [ecx+3Ch]
		sub eax, edx
		inc eax
		ret
routerPath:
		push esi
		xor edx, edx
		lea eax,  [ecx+12060h]
		mov esi, 2h
		nop
nextGroup:
		mov ecx, dword ptr [eax-1205Ch]
		test ecx, ecx
		je slot1
		mov ecx, dword ptr [eax]
		cmp edx, ecx
		ja slot1
		mov edx, ecx
slot1:
		mov ecx, dword ptr [eax-12058h]
		test ecx, ecx
		je slot2
		mov ecx, dword ptr [eax+4h]
		cmp edx, ecx
		ja slot2
		mov edx, ecx
slot2:
		mov ecx, dword ptr [eax-12054h]
		test ecx, ecx
		je slot3
		mov ecx, dword ptr [eax+8h]
		cmp edx, ecx
		ja slot3
		mov edx, ecx
slot3:
		mov ecx, dword ptr [eax-12050h]
		test ecx, ecx
		je groupDone
		mov ecx, dword ptr [eax+0Ch]
		cmp edx, ecx
		ja groupDone
		mov edx, ecx
groupDone:
		add eax, 10h
		dec esi
		jne nextGroup
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		mov eax, dword ptr [eax+3Ch]
		sub eax, edx
		pop esi
		inc eax
		ret
	}
}

// Command type 8 handler. Records the sender's announced frame in the
// per-player latest-frame array at this+0x12060 when it is within
// NetworkKeepAliveDelay of our own, then -- if that frame is still ahead of us
// and the leaving player is not us -- allocates a 0x24-byte command type 9
// (REQUESTFRAMEDATA), stamps the range [currentFrame+1, announcedFrame] into its
// two payload dwords at +0x1C and +0x20, and sends it back to the sender alone.
__declspec(naked) void BFMEConnectionManager::processInformPlayerLeaveFrameCommand(void *msg)
{
	__asm {
		mov eax, dword ptr fs:[0h]
		push 0FFFFFFFFh
		push 10440ABh
		push eax
		mov dword ptr fs:[0h], esp
		push ebx
		push ebp
		mov ebp, dword ptr [esp+18h]
		push esi
		xor esi, esi
		cmp ebp, esi
		push edi
		mov ebx, ecx
		je done
		mov ecx, ebp
		__emit 0E8h
		__emit 0A6h
		__emit 09Ah
		__emit 09Ch
		__emit 0FFh   // call 0x2DF06
		mov edi, eax
		mov ecx, ebp
		mov dword ptr [esp+20h], edi
		__emit 0E8h
		__emit 0A5h
		__emit 001h
		__emit 09Dh
		__emit 0FFh   // call 0x34612
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		__emit 08Bh
		__emit 015h
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h   // mov edx, dword ptr [0x12ed5c8]
		mov ecx, dword ptr [ecx+3Ch]
		mov edx, dword ptr [edx+0CB4h]
		add edx, ecx
		cmp edi, edx
		jae frameRecorded
		mov ecx, dword ptr [ebp+0Ch]
		cmp ecx, 8h
		jae frameRecorded
		cmp dword ptr [ebx+ecx*4+12060h], edi
		lea edx,  [ebx+ecx*4+12060h]
		ja useIncomingFrame
		lea edx,  [esp+20h]
useIncomingFrame:
		mov edx, dword ptr [edx]
		mov dword ptr [ebx+ecx*4+12060h], edx
frameRecorded:
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		cmp dword ptr [ecx+3Ch], edi
		jae done
		movzx edx, ax
		cmp edx, dword ptr [ebx+12028h]
		je done
		push 24h
		__emit 0E8h
		__emit 05Eh
		__emit 0DAh
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+20h], eax
		cmp eax, esi
		mov dword ptr [esp+18h], esi
		je haveRequest
		mov ecx, eax
		__emit 0E8h
		__emit 078h
		__emit 0DDh
		__emit 09Ah
		__emit 0FFh   // call 0x12260
		mov esi, eax
haveRequest:
		mov ecx, dword ptr [ebx+12028h]
		or eax, 0FFFFFFFFh
		mov dword ptr [esi+0Ch], ecx
		mov dword ptr [esi+8h], eax
		__emit 08Bh
		__emit 015h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov edx, dword ptr [0x12f0898]
		mov dword ptr [esp+18h], eax
		mov eax, dword ptr [edx+3Ch]
		inc eax
		push eax
		mov ecx, esi
		__emit 0E8h
		__emit 051h
		__emit 0CEh
		__emit 09Ah
		__emit 0FFh   // call 0x11360
		push edi
		mov ecx, esi
		__emit 0E8h
		__emit 0BEh
		__emit 0BFh
		__emit 09Dh
		__emit 0FFh   // call 0x404D5
		mov eax, dword ptr [esi+14h]
		push eax
		__emit 0E8h
		__emit 052h
		__emit 016h
		__emit 09Bh
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je sendToSender
		__emit 0E8h
		__emit 02Ch
		__emit 0C0h
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
sendToSender:
		mov ecx, dword ptr [ebp+0Ch]
		cmp ecx, 8h
		jae releaseRequest
		xor edx, edx
		mov dl, 1h
		shl dl, cl
		mov ecx, ebx
		push edx
		push esi
		__emit 0E8h
		__emit 090h
		__emit 0CCh
		__emit 09Dh
		__emit 0FFh   // call 0x411D7
releaseRequest:
		mov ecx, esi
		__emit 0E8h
		__emit 056h
		__emit 0BBh
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
done:
		mov ecx, dword ptr [esp+10h]
		pop edi
		pop esi
		pop ebp
		mov dword ptr fs:[0h], ecx
		pop ebx
		add esp, 0Ch
		ret 4h
	}
}

// The FRAMEINFO (command type 3) sender, and the function that publishes the
// frame ceiling. Builds a 0x28-byte type-3 message stamped with TheGameLogic's
// current frame, sums getCommandCount(frame) across the eight FrameDataManagers,
// records that total on the local manager via setFrameCommandCount and copies it
// into the message at +0x24. As packet router it broadcasts to every other slot
// and then sets the shared ceiling at this+0x1205C to its OWN current frame;
// otherwise it sends only to the router. This is BFME's off-host delay: a client
// may advance only up to the last frame the router announced, and the router
// announces on the fixed QueryPerformanceFrequency/5 (200ms) quantum that
// BFMENativeNetwork::getFrameAdvanceCount enforces.
__declspec(naked) void BFMEConnectionManager::sendFrameInfo()
{
	__asm {
		push 0FFFFFFFFh
		push 104426Bh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		push ebx
		push ebp
		push esi
		push edi
		push 28h
		mov edi, ecx
		or ebp, 0FFFFFFFFh
		__emit 0E8h
		__emit 0FAh
		__emit 0C1h
		__emit 021h
		__emit 000h   // call 0x881F30
		mov esi, eax
		add esp, 4h
		mov dword ptr [esp+10h], esi
		xor ebx, ebx
		cmp esi, ebx
		mov dword ptr [esp+1Ch], ebx
		je allocFailed
		mov ecx, esi
		__emit 0E8h
		__emit 064h
		__emit 0D5h
		__emit 09Ah
		__emit 0FFh   // call 0x132B4
		mov dword ptr [esi], 111A220h
		mov dword ptr [esi+1Ch], ebx
		mov dword ptr [esi+20h], ebx
		mov dword ptr [esi+24h], ebp
		mov dword ptr [esi+14h], 3h
		jmp stampFrame
allocFailed:
		xor esi, esi
stampFrame:
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		mov ecx, dword ptr [eax+3Ch]
		mov dword ptr [esi+1Ch], ecx
		__emit 08Bh
		__emit 00Dh
		__emit 064h
		__emit 014h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f1464]
		mov edx, dword ptr [ecx]
		mov dword ptr [esp+1Ch], ebp
		call dword ptr [edx+68h]
		mov dword ptr [esi+20h], eax
		mov eax, dword ptr [edi+12028h]
		mov dword ptr [esi+0Ch], eax
		mov eax, dword ptr [esi+14h]
		push eax
		__emit 0E8h
		__emit 0D9h
		__emit 0FDh
		__emit 09Ah
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je countCommands
		__emit 0E8h
		__emit 0B3h
		__emit 0A7h
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
countCommands:
		mov eax, dword ptr [edi+12028h]
		cmp dword ptr [edi+eax*4+120E4h], ebx
		je recordTotal
		cmp eax, dword ptr [edi+1202Ch]
		jne recordTotal
		xor ebp, ebp
		lea ebx,  [edi+120E4h]
		mov dword ptr [esp+10h], 8h
nextSlot:
		mov ecx, dword ptr [ebx]
		test ecx, ecx
		je advanceSlot
		__emit 0E8h
		__emit 001h
		__emit 0D9h
		__emit 09Bh
		__emit 0FFh   // call 0x236DC
		test al, al
		jne advanceSlot
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		mov eax, dword ptr [ecx+3Ch]
		mov ecx, dword ptr [ebx]
		push eax
		__emit 0E8h
		__emit 0A2h
		__emit 019h
		__emit 09Bh
		__emit 0FFh   // call 0x17792
		add ebp, eax
advanceSlot:
		mov eax, dword ptr [esp+10h]
		add ebx, 4h
		dec eax
		mov dword ptr [esp+10h], eax
		jne nextSlot
		mov edx, dword ptr [esi+1Ch]
		mov eax, dword ptr [edi+12028h]
		mov ecx, dword ptr [edi+eax*4+120E4h]
		push ebp
		push edx
		__emit 0E8h
		__emit 04Bh
		__emit 060h
		__emit 09Dh
		__emit 0FFh   // call 0x3BE62
recordTotal:
		mov dword ptr [esi+24h], ebp
		mov eax, dword ptr [edi+12028h]
		mov ecx, dword ptr [edi+1202Ch]
		xor edx, edx
		cmp eax, ecx
		mov dl, 1h
		jne sendToRouter
		mov ecx, eax
		shl dl, cl
		mov ecx, edi
		not dl
		push edx
		push esi
		__emit 0E8h
		__emit 03Dh
		__emit 093h
		__emit 09Dh
		__emit 0FFh   // call 0x3F17A
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		mov ecx, dword ptr [eax+3Ch]
		mov dword ptr [edi+1205Ch], ecx
		jmp release
sendToRouter:
		shl dl, cl
		mov ecx, edi
		push edx
		push esi
		__emit 0E8h
		__emit 022h
		__emit 093h
		__emit 09Dh
		__emit 0FFh   // call 0x3F17A
release:
		mov ecx, esi
		__emit 0E8h
		__emit 045h
		__emit 0A2h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		mov ecx, dword ptr [esp+14h]
		pop edi
		pop esi
		pop ebp
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret
	}
}

// The incoming-command dispatcher: switch on the command type at message
// +0x14 through the jump table at 0x0066A634 (data, deliberately outside this
// row). Case 3 is the FRAMEINFO receiver and the other half of the delay path --
// it updates the sender's latest frame at this+0x12060 and its aux dword at
// this+0x120A0, and when we are NOT the packet router it raises the shared
// ceiling at this+0x1205C to the announced frame. Only then, if the frame is not
// behind us and the message's count at +0x24 is not -1, it stores that count on
// the local FrameDataManager as the expected total. Case 8 calls
// processInformPlayerLeaveFrameCommand and case 9
// processRequestFrameDataCommand.
__declspec(naked) Bool BFMEConnectionManager::processIncomingCommand(void *ref)
{
	__asm {
		push ebx
		push ebp
		mov ebp, dword ptr [esp+0Ch]
		push esi
		mov esi, dword ptr [ebp]
		mov ebx, dword ptr [esi+0Ch]
		cmp ebx, 8h
		push edi
		mov edi, ecx
		jae L00_66A62B
		cmp ebx, dword ptr [edi+12028h]
		je L01_66A431
		mov eax, dword ptr [edi+ebx*4+4h]
		test eax, eax
		mov dword ptr [esp+14h], eax
		je L00_66A62B
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h   // call dword ptr [0x1359544]
		mov ecx, dword ptr [esp+14h]
		mov dword ptr [ecx+34Ch], eax
L01_66A431:
		mov eax, dword ptr [esi+14h]
		cmp eax, 16h
		ja L02_66A608
		jmp dword ptr [eax*4+0A6A634h]
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 0DFh
		__emit 093h
		__emit 09Bh
		__emit 0FFh   // call 0x2382B
L07_66A44C:
		pop edi
		pop esi
		pop ebp
		mov al, 1h
		pop ebx
		ret 4h
		push ebp
		mov ecx, edi
		__emit 0E8h
		__emit 099h
		__emit 032h
		__emit 09Bh
		__emit 0FFh   // call 0x1D6F6
		pop edi
		pop esi
		pop ebp
		mov al, 1h
		pop ebx
		ret 4h
		mov eax, dword ptr [edi+1202Ch]
		mov edx, dword ptr [edi+12028h]
		mov ecx, dword ptr [edi+ebx*4+12060h]
		cmp edx, eax
		mov eax, dword ptr [esi+1Ch]
		jne L03_66A49E
		cmp eax, ecx
		jbe L04_66A4EE
		mov dword ptr [edi+ebx*4+12060h], eax
		mov eax, dword ptr [esi+20h]
		mov dword ptr [edi+ebx*4+120A0h], eax
		pop edi
		pop esi
		pop ebp
		xor al, al
		pop ebx
		ret 4h
L03_66A49E:
		cmp eax, ecx
		jbe L05_66A4B3
		mov dword ptr [edi+ebx*4+12060h], eax
		mov ecx, dword ptr [esi+20h]
		mov dword ptr [edi+ebx*4+120A0h], ecx
L05_66A4B3:
		mov eax, dword ptr [esi+1Ch]
		cmp dword ptr [edi+1205Ch], eax
		jae L06_66A4C4
		mov dword ptr [edi+1205Ch], eax
L06_66A4C4:
		__emit 08Bh
		__emit 015h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov edx, dword ptr [0x12f0898]
		mov eax, dword ptr [esi+1Ch]
		cmp eax, dword ptr [edx+3Ch]
		jb L04_66A4EE
		mov esi, dword ptr [esi+24h]
		cmp esi, 0FFFFFFFFh
		je L04_66A4EE
		push esi
		push eax
		mov eax, dword ptr [edi+12028h]
		mov ecx, dword ptr [edi+eax*4+120E4h]
		__emit 0E8h
		__emit 074h
		__emit 019h
		__emit 09Dh
		__emit 0FFh   // call 0x3BE62
L04_66A4EE:
		pop edi
		pop esi
		pop ebp
		xor al, al
		pop ebx
		ret 4h
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 06Ah
		__emit 0ECh
		__emit 09Ah
		__emit 0FFh   // call 0x19169
		pop edi
		pop esi
		pop ebp
		xor al, al
		pop ebx
		ret 4h
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 01Ah
		__emit 05Dh
		__emit 09Bh
		__emit 0FFh   // call 0x2022A
		pop edi
		pop esi
		pop ebp
		xor al, al
		pop ebx
		ret 4h
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 08Eh
		__emit 05Fh
		__emit 09Bh
		__emit 0FFh   // call 0x204AF
		pop edi
		pop esi
		pop ebp
		xor al, al
		pop ebx
		ret 4h
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 0CEh
		__emit 025h
		__emit 09Dh
		__emit 0FFh   // call 0x3CB00
		pop edi
		pop esi
		pop ebp
		xor al, al
		pop ebx
		ret 4h
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 0E4h
		__emit 0E0h
		__emit 09Ch
		__emit 0FFh   // call 0x38627
		pop edi
		pop esi
		pop ebp
		xor al, al
		pop ebx
		ret 4h
		add esi, 1Ch
		add edi, 12030h
		mov ecx, 8h
		rep movsd
		pop edi
		pop esi
		pop ebp
		mov al, 1h
		pop ebx
		ret 4h
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 0BAh
		__emit 0EDh
		__emit 099h
		__emit 0FFh   // call 0x9327
		mov ecx, dword ptr [edi+12028h]
		mov al, byte ptr [ebp+0Ch]
		mov dl, 1h
		shl dl, cl
		pop edi
		pop esi
		not dl
		and al, dl
		mov byte ptr [ebp+0Ch], al
		pop ebp
		mov al, 1h
		pop ebx
		ret 4h
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		__emit 0E8h
		__emit 013h
		__emit 085h
		__emit 09Ah
		__emit 0FFh   // call 0x12AA8
		pop edi
		pop esi
		pop ebp
		mov al, 1h
		pop ebx
		ret 4h
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 01Ch
		__emit 0C6h
		__emit 099h
		__emit 0FFh   // call 0x6BC2
		pop edi
		pop esi
		pop ebp
		mov al, 1h
		pop ebx
		ret 4h
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		push ebx
		__emit 0E8h
		__emit 04Ah
		__emit 05Eh
		__emit 09Bh
		__emit 0FFh   // call 0x20405
		pop edi
		pop esi
		pop ebp
		mov al, 1h
		pop ebx
		ret 4h
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 03Bh
		__emit 0A4h
		__emit 099h
		__emit 0FFh   // call 0x4A07
		pop edi
		pop esi
		pop ebp
		mov al, 1h
		pop ebx
		ret 4h
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 035h
		__emit 052h
		__emit 09Ah
		__emit 0FFh   // call 0xF812
		pop edi
		pop esi
		pop ebp
		mov al, 1h
		pop ebx
		ret 4h
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 006h
		__emit 0E4h
		__emit 099h
		__emit 0FFh   // call 0x89F4
		pop edi
		pop esi
		pop ebp
		mov al, 1h
		pop ebx
		ret 4h
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 074h
		__emit 05Dh
		__emit 09Ch
		__emit 0FFh   // call 0x30373
		pop edi
		pop esi
		pop ebp
		mov al, 1h
		pop ebx
		ret 4h
L02_66A608:
		cmp eax, 17h
		jle L07_66A44C
		cmp eax, 1Dh
		jge L07_66A44C
		mov ecx, dword ptr [edi+120E0h]
		test ecx, ecx
		je L00_66A62B
		push edi
		push ebp
		__emit 0E8h
		__emit 045h
		__emit 0E3h
		__emit 09Bh
		__emit 0FFh   // call 0x28970
L00_66A62B:
		pop edi
		pop esi
		pop ebp
		xor al, al
		pop ebx
		ret 4h
	}
}

// Constructor. Zeroes the whole tail of the object, which is what pins its
// layout: the frame ceiling at +0x1205C, the scalar trio at +0x12050/+0x12054
// (word)/+0x12058, +0x120E0, and the pointer block +0x12104..+0x12110 plus a
// byte at +0x12114.
__declspec(naked) void *BFMEConnectionManager::construct()
{
	__asm {
		push 0FFFFFFFFh
		push 10445DAh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		push ebx
		push ebp
		push esi
		mov esi, ecx
		push edi
		mov dword ptr [esp+10h], esi
		mov dword ptr [esi], 111A2B0h
		lea edx,  [esi+24h]
		mov ebp, 9h
		xor ebx, ebx
L00_669660:
		xor eax, eax
		mov edi, edx
		mov ecx, 800h
		rep stosd
		mov dword ptr [edx], ebx
		add edx, 2000h
		dec ebp
		jne L00_669660
		mov dword ptr [esi+12024h], ebx
		or edi, 0FFFFFFFFh
		mov dword ptr [esi+12028h], edi
		mov dword ptr [esi+1202Ch], ebx
		mov dword ptr [esi+12050h], ebx
		mov word ptr [esi+12054h], bx
		mov dword ptr [esi+12058h], ebx
		mov dword ptr [esi+1205Ch], ebx
		mov dword ptr [esi+120E0h], ebx
		mov dword ptr [esi+12104h], ebx
		mov dword ptr [esi+12108h], ebx
		mov dword ptr [esi+1210Ch], ebx
		mov dword ptr [esi+12110h], ebx
		mov byte ptr [esi+12114h], bl
		mov byte ptr [esi+12115h], 1h
		push 18h
		mov dword ptr [esp+20h], ebx
		mov dword ptr [esi+12118h], ebx
		__emit 0E8h
		__emit 060h
		__emit 04Eh
		__emit 01Ch
		__emit 000h   // call 0x82E540
		mov dword ptr [esi+12118h], eax
		mov dword ptr [esi+1211Ch], ebx
		mov byte ptr [eax], bl
		mov eax, dword ptr [esi+12118h]
		mov dword ptr [eax+4h], ebx
		mov eax, dword ptr [esi+12118h]
		mov dword ptr [eax+8h], eax
		mov eax, dword ptr [esi+12118h]
		mov dword ptr [eax+0Ch], eax
		push 14h
		mov byte ptr [esp+24h], 1h
		mov dword ptr [esi+12124h], ebx
		__emit 0E8h
		__emit 025h
		__emit 04Eh
		__emit 01Ch
		__emit 000h   // call 0x82E540
		mov dword ptr [esi+12124h], eax
		mov dword ptr [esi+12128h], ebx
		mov byte ptr [eax], bl
		mov ecx, dword ptr [esi+12124h]
		mov dword ptr [ecx+4h], ebx
		mov eax, dword ptr [esi+12124h]
		mov dword ptr [eax+8h], eax
		mov eax, dword ptr [esi+12124h]
		add esp, 8h
		mov dword ptr [eax+0Ch], eax
		push 43C961h
		push 443649h
		push 8h
		push 0Ch
		lea edx,  [esi+12130h]
		push edx
		mov byte ptr [esp+30h], 2h
		__emit 0E8h
		__emit 07Eh
		__emit 0D7h
		__emit 038h
		__emit 000h   // call 0x9F6EE4
		mov dword ptr [esi+4h], ebx
		mov dword ptr [esi+12030h], edi
		mov dword ptr [esi+120E4h], ebx
		mov dword ptr [esi+12060h], ebx
		mov dword ptr [esi+120A0h], ebx
		mov dword ptr [esi+120C0h], ebx
		mov dword ptr [esi+12080h], ebx
		mov dword ptr [esi+8h], ebx
		mov dword ptr [esi+12034h], edi
		mov dword ptr [esi+120E8h], ebx
		mov dword ptr [esi+12064h], ebx
		mov dword ptr [esi+120A4h], ebx
		mov dword ptr [esi+120C4h], ebx
		mov dword ptr [esi+12084h], ebx
		mov dword ptr [esi+0Ch], ebx
		mov dword ptr [esi+12038h], edi
		mov dword ptr [esi+120ECh], ebx
		mov dword ptr [esi+12068h], ebx
		mov dword ptr [esi+120A8h], ebx
		mov dword ptr [esi+120C8h], ebx
		mov dword ptr [esi+12088h], ebx
		mov dword ptr [esi+10h], ebx
		mov dword ptr [esi+1203Ch], edi
		mov dword ptr [esi+120F0h], ebx
		mov dword ptr [esi+1206Ch], ebx
		mov dword ptr [esi+120ACh], ebx
		mov dword ptr [esi+120CCh], ebx
		mov dword ptr [esi+1208Ch], ebx
		mov ecx, dword ptr [esp+14h]
		mov dword ptr [esi+12040h], edi
		mov dword ptr [esi+12044h], edi
		mov dword ptr [esi+12048h], edi
		mov dword ptr [esi+1204Ch], edi
		pop edi
		mov dword ptr [esi+14h], ebx
		mov dword ptr [esi+120F4h], ebx
		mov dword ptr [esi+12070h], ebx
		mov dword ptr [esi+120B0h], ebx
		mov dword ptr [esi+120D0h], ebx
		mov dword ptr [esi+12090h], ebx
		mov dword ptr [esi+18h], ebx
		mov dword ptr [esi+120F8h], ebx
		mov dword ptr [esi+12074h], ebx
		mov dword ptr [esi+120B4h], ebx
		mov dword ptr [esi+120D4h], ebx
		mov dword ptr [esi+12094h], ebx
		mov dword ptr [esi+1Ch], ebx
		mov dword ptr [esi+120FCh], ebx
		mov dword ptr [esi+12078h], ebx
		mov dword ptr [esi+120B8h], ebx
		mov dword ptr [esi+120D8h], ebx
		mov dword ptr [esi+12098h], ebx
		mov dword ptr [esi+20h], ebx
		mov dword ptr [esi+12100h], ebx
		mov dword ptr [esi+1207Ch], ebx
		mov dword ptr [esi+120BCh], ebx
		mov dword ptr [esi+120DCh], ebx
		mov dword ptr [esi+1209Ch], ebx
		mov eax, esi
		pop esi
		pop ebp
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret
	}
}

// init/reset. Clears the eight Connection pointers at +0x04, rebuilds the two
// 16-byte objects at +0x12104 and +0x12108, sets m_localSlot to -1, zeroes the
// frame ceiling and m_packetRouterSlot, then walks eight slots at once writing
// -1 to the id array at +0x12030 and zero to the per-player arrays at +0x12060,
// +0x120A0 and +0x120C0.
__declspec(naked) void BFMEConnectionManager::init()
{
	__asm {
		push 0FFFFFFFFh
		push 104458Ch
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		xor eax, eax
		push ebx
		mov ebx, ecx
		mov dword ptr [ebx+4h], eax
		mov dword ptr [ebx+8h], eax
		mov dword ptr [ebx+0Ch], eax
		mov dword ptr [ebx+10h], eax
		mov dword ptr [ebx+14h], eax
		mov dword ptr [ebx+18h], eax
		mov dword ptr [ebx+1Ch], eax
		push ebp
		mov dword ptr [ebx+20h], eax
		mov eax, dword ptr [ebx+12104h]
		xor ebp, ebp
		cmp eax, ebp
		push esi
		push edi
		jne L00_6690C9
		push 10h
		__emit 0E8h
		__emit 097h
		__emit 08Eh
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+10h], eax
		cmp eax, ebp
		mov dword ptr [esp+1Ch], ebp
		je L01_6690B1
		mov ecx, eax
		__emit 0E8h
		__emit 0F7h
		__emit 072h
		__emit 09Bh
		__emit 0FFh   // call 0x203A6
		jmp L02_6690B3
L01_6690B1:
		xor eax, eax
L02_6690B3:
		or esi, 0FFFFFFFFh
		mov ecx, eax
		mov dword ptr [esp+1Ch], esi
		mov dword ptr [ebx+12104h], eax
		__emit 0E8h
		__emit 007h
		__emit 029h
		__emit 09Ah
		__emit 0FFh   // call 0xB9CE
		jmp L03_6690CC
L00_6690C9:
		or esi, 0FFFFFFFFh
L03_6690CC:
		mov ecx, dword ptr [ebx+12104h]
		__emit 0E8h
		__emit 0F7h
		__emit 028h
		__emit 09Ah
		__emit 0FFh   // call 0xB9CE
		cmp dword ptr [ebx+12108h], ebp
		jne L04_669115
		push 10h
		__emit 0E8h
		__emit 04Ah
		__emit 08Eh
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+10h], eax
		cmp eax, ebp
		mov dword ptr [esp+1Ch], 1h
		je L05_669102
		mov ecx, eax
		__emit 0E8h
		__emit 0A6h
		__emit 072h
		__emit 09Bh
		__emit 0FFh   // call 0x203A6
		jmp L06_669104
L05_669102:
		xor eax, eax
L06_669104:
		mov ecx, eax
		mov dword ptr [esp+1Ch], esi
		mov dword ptr [ebx+12108h], eax
		__emit 0E8h
		__emit 0B9h
		__emit 028h
		__emit 09Ah
		__emit 0FFh   // call 0xB9CE
L04_669115:
		mov ecx, dword ptr [ebx+12108h]
		__emit 0E8h
		__emit 0AEh
		__emit 028h
		__emit 09Ah
		__emit 0FFh   // call 0xB9CE
		mov dword ptr [ebx+12028h], esi
		mov dword ptr [ebx+1205Ch], ebp
		mov dword ptr [ebx+1202Ch], ebp
		lea eax,  [ebx+12060h]
		mov ecx, 8h
		__emit 08Dh
		__emit 049h
		__emit 000h   // lea ecx, [ecx]
L07_669140:
		mov dword ptr [eax-30h], esi
		mov dword ptr [eax], ebp
		mov dword ptr [eax+40h], ebp
		mov dword ptr [eax+60h], ebp
		add eax, 4h
		dec ecx
		mov dword ptr [ebx+120A0h], ebp
		jne L07_669140
		lea esi,  [ebx+120E4h]
		mov edi, 8h
L09_669162:
		mov ecx, dword ptr [esi]
		cmp ecx, ebp
		je L08_669170
		mov edx, dword ptr [ecx]
		push 1h
		call dword ptr [edx]
		mov dword ptr [esi], ebp
L08_669170:
		add esi, 4h
		dec edi
		jne L09_669162
		push 28Ch
		__emit 0E8h
		__emit 0B0h
		__emit 08Dh
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+10h], eax
		cmp eax, ebp
		mov dword ptr [esp+1Ch], 2h
		je L10_66919C
		mov ecx, eax
		__emit 0E8h
		__emit 0BEh
		__emit 0ECh
		__emit 09Bh
		__emit 0FFh   // call 0x27E58
		jmp L11_66919E
L10_66919C:
		xor eax, eax
L11_66919E:
		or esi, 0FFFFFFFFh
		mov ecx, eax
		mov dword ptr [esp+1Ch], esi
		mov dword ptr [ebx+120E0h], eax
		__emit 0E8h
		__emit 030h
		__emit 01Ch
		__emit 09Ch
		__emit 0FFh   // call 0x2ADE2
		push 8h
		__emit 0E8h
		__emit 077h
		__emit 08Dh
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+10h], eax
		cmp eax, ebp
		mov dword ptr [esp+1Ch], 3h
		je L12_6691D5
		mov ecx, eax
		__emit 0E8h
		__emit 0D0h
		__emit 0D4h
		__emit 09Ah
		__emit 0FFh   // call 0x166A3
		jmp L13_6691D7
L12_6691D5:
		xor eax, eax
L13_6691D7:
		mov ecx, eax
		mov dword ptr [esp+1Ch], esi
		mov dword ptr [ebx+1210Ch], eax
		__emit 0E8h
		__emit 0C0h
		__emit 004h
		__emit 09Dh
		__emit 0FFh   // call 0x396A8
		mov eax, dword ptr [ebx+1211Ch]
		cmp eax, ebp
		lea edi,  [ebx+12118h]
		je L14_66923A
		mov eax, dword ptr [edi]
		mov esi, dword ptr [eax+4h]
		cmp esi, ebp
		je L15_669228
L16_669201:
		mov ecx, dword ptr [esi+0Ch]
		push ecx
		mov ecx, edi
		__emit 0E8h
		__emit 0DFh
		__emit 096h
		__emit 09Ah
		__emit 0FFh   // call 0x128EB
		mov ebp, dword ptr [esi+8h]
		lea ecx,  [esi+14h]
		__emit 0E8h
		__emit 029h
		__emit 0E7h
		__emit 021h
		__emit 000h   // call 0x887940
		push 18h
		push esi
		__emit 0E8h
		__emit 0D1h
		__emit 053h
		__emit 01Ch
		__emit 000h   // call 0x82E5F0
		add esp, 8h
		test ebp, ebp
		mov esi, ebp
		jne L16_669201
L15_669228:
		mov eax, dword ptr [edi]
		mov dword ptr [eax+8h], eax
		mov edx, dword ptr [edi]
		mov dword ptr [edx+4h], ebp
		mov eax, dword ptr [edi]
		mov dword ptr [eax+0Ch], eax
		mov dword ptr [edi+4h], ebp
L14_66923A:
		mov eax, dword ptr [ebx+12128h]
		cmp eax, ebp
		lea edi,  [ebx+12124h]
		je L17_669284
		mov eax, dword ptr [edi]
		mov esi, dword ptr [eax+4h]
		cmp esi, ebp
		je L18_669272
L19_669253:
		mov ecx, dword ptr [esi+0Ch]
		push ecx
		mov ecx, edi
		__emit 0E8h
		__emit 0C1h
		__emit 0F8h
		__emit 09Ah
		__emit 0FFh   // call 0x18B1F
		mov ebp, dword ptr [esi+8h]
		push 14h
		push esi
		__emit 0E8h
		__emit 087h
		__emit 053h
		__emit 01Ch
		__emit 000h   // call 0x82E5F0
		add esp, 8h
		test ebp, ebp
		mov esi, ebp
		jne L19_669253
L18_669272:
		mov eax, dword ptr [edi]
		mov dword ptr [eax+8h], eax
		mov edx, dword ptr [edi]
		mov dword ptr [edx+4h], ebp
		mov eax, dword ptr [edi]
		mov dword ptr [eax+0Ch], eax
		mov dword ptr [edi+4h], ebp
L17_669284:
		lea edi,  [ebx+12130h]
		mov dword ptr [esp+10h], 8h
L23_669292:
		cmp dword ptr [edi+4h], ebp
		je L20_6692D1
		mov eax, dword ptr [edi]
		mov esi, dword ptr [eax+4h]
		cmp esi, ebp
		je L21_6692BF
L22_6692A0:
		mov ecx, dword ptr [esi+0Ch]
		push ecx
		mov ecx, edi
		__emit 0E8h
		__emit 0AFh
		__emit 0F2h
		__emit 09Ch
		__emit 0FFh   // call 0x3855A
		mov ebp, dword ptr [esi+8h]
		push 18h
		push esi
		__emit 0E8h
		__emit 03Ah
		__emit 053h
		__emit 01Ch
		__emit 000h   // call 0x82E5F0
		add esp, 8h
		test ebp, ebp
		mov esi, ebp
		jne L22_6692A0
L21_6692BF:
		mov eax, dword ptr [edi]
		mov dword ptr [eax+8h], eax
		mov edx, dword ptr [edi]
		mov dword ptr [edx+4h], ebp
		mov eax, dword ptr [edi]
		mov dword ptr [eax+0Ch], eax
		mov dword ptr [edi+4h], ebp
L20_6692D1:
		mov eax, dword ptr [esp+10h]
		add edi, 0Ch
		dec eax
		mov dword ptr [esp+10h], eax
		jne L23_669292
		mov ecx, dword ptr [esp+14h]
		pop edi
		mov dword ptr [ebx+12110h], ebp
		pop esi
		mov byte ptr [ebx+12114h], 0h
		mov byte ptr [ebx+12115h], 1h
		pop ebp
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret
	}
}

// Per-connection metrics. For each live Connection it converts the aux dword at
// +0x120A0 and the latest frame at +0x12060 to floats (with the usual
// unsigned-to-double fixup against 0x01075358) and takes their ratio. Ghidra
// sizes this function 447; the real body runs 454 bytes to its ret.
__declspec(naked) void BFMEConnectionManager::computePlayerFrameRatios()
{
	__asm {
		push 0FFFFFFFFh
		push 10442ABh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 2Ch
		push ebx
		push ebp
		push esi
		xor esi, esi
		push edi
		mov dword ptr [esp+14h], ecx
		xor ebx, ebx
		lea ebp,  [ecx+4h]
		jmp L00_666030
		__emit 08Dh
		__emit 0A4h
		__emit 024h
		__emit 000h
		__emit 000h
		__emit 000h
		__emit 000h   // lea esp, [esp]
L00_666030:
		mov eax, dword ptr [ebp]
		test eax, eax
		je L01_6660CC
		mov ecx, dword ptr [ebp+1209Ch]
		fild dword ptr [ebp+1209Ch]
		test ecx, ecx
		mov eax, dword ptr [eax+20h]
		mov dword ptr [esp+10h], eax
		jge L02_666058
		__emit 0D8h
		__emit 005h
		__emit 058h
		__emit 053h
		__emit 007h
		__emit 001h   // fadd dword ptr [0x1075358]
L02_666058:
		mov edx, dword ptr [ebp+1205Ch]
		fild dword ptr [ebp+1205Ch]
		test edx, edx
		jge L03_66606E
		__emit 0D8h
		__emit 005h
		__emit 058h
		__emit 053h
		__emit 007h
		__emit 001h   // fadd dword ptr [0x1075358]
L03_66606E:
		__emit 0DEh
		__emit 0F9h   // fdivp st(1)
		__emit 0D8h
		__emit 01Dh
		__emit 0E0h
		__emit 077h
		__emit 009h
		__emit 001h   // fcomp dword ptr [0x10977e0]
		fnstsw ax
		test ah, 41h
		jp L04_66608B
		fld dword ptr [esp+10h]
		__emit 0D8h
		__emit 005h
		__emit 068h
		__emit 05Ch
		__emit 007h
		__emit 001h   // fadd dword ptr [0x1075c68]
		fstp dword ptr [esp+10h]
L04_66608B:
		push 0Ch
		__emit 0E8h
		__emit 09Eh
		__emit 0BEh
		__emit 021h
		__emit 000h   // call 0x881F30
		mov edx, eax
		mov eax, dword ptr [esp+14h]
		add esp, 4h
		xor edi, edi
		test esi, esi
		mov dword ptr [edx], eax
		mov dword ptr [edx+4h], ebx
		mov ecx, esi
		je L05_6660BE
L06_6660A8:
		fld dword ptr [ecx]
		fcomp dword ptr [esp+10h]
		fnstsw ax
		test ah, 41h
		je L05_6660BE
		mov edi, ecx
		mov ecx, dword ptr [ecx+8h]
		test ecx, ecx
		jne L06_6660A8
L05_6660BE:
		test edi, edi
		mov dword ptr [edx+8h], ecx
		je L07_6660CA
		mov dword ptr [edi+8h], edx
		jmp L01_6660CC
L07_6660CA:
		mov esi, edx
L01_6660CC:
		inc ebx
		add ebp, 4h
		cmp ebx, 8h
		jl L00_666030
		test esi, esi
		mov ecx, dword ptr [esp+14h]
		mov edx, dword ptr [ecx+12028h]
		mov ebx, 1h
		mov dword ptr [esp+1Ch], edx
		je L08_6661B3
L10_6660F4:
		cmp ebx, 8h
		jae L09_666101
		mov eax, dword ptr [esi+4h]
		mov dword ptr [esp+ebx*4+1Ch], eax
		inc ebx
L09_666101:
		mov edi, dword ptr [esi+8h]
		push esi
		__emit 0E8h
		__emit 0A6h
		__emit 0BDh
		__emit 021h
		__emit 000h   // call 0x881EB0
		add esp, 4h
		test edi, edi
		mov esi, edi
		jne L10_6660F4
		cmp ebx, 2h
		jbe L08_6661B3
		cmp ebx, 8h
		jae L11_666131
		mov ecx, 8h
		sub ecx, ebx
		lea edi,  [esp+ebx*4+1Ch]
		or eax, 0FFFFFFFFh
		rep stosd
L11_666131:
		push 3Ch
		__emit 0E8h
		__emit 0F8h
		__emit 0BDh
		__emit 021h
		__emit 000h   // call 0x881F30
		mov esi, eax
		add esp, 4h
		mov dword ptr [esp+18h], esi
		test esi, esi
		mov dword ptr [esp+44h], 0h
		je L12_666163
		mov ecx, esi
		__emit 0E8h
		__emit 060h
		__emit 0D1h
		__emit 09Ah
		__emit 0FFh   // call 0x132B4
		mov dword ptr [esi], 111A234h
		mov dword ptr [esi+14h], 16h
		jmp L13_666165
L12_666163:
		xor esi, esi
L13_666165:
		lea ecx,  [esp+1Ch]
		push ecx
		mov ecx, esi
		mov dword ptr [esp+48h], 0FFFFFFFFh
		__emit 0E8h
		__emit 0BFh
		__emit 0C8h
		__emit 09Ch
		__emit 0FFh   // call 0x32A38
		mov edi, dword ptr [esp+14h]
		mov eax, dword ptr [esi+14h]
		mov edx, dword ptr [edi+12028h]
		push eax
		mov dword ptr [esi+0Ch], edx
		__emit 0E8h
		__emit 0E3h
		__emit 0F9h
		__emit 09Ah
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L14_66619F
		__emit 0E8h
		__emit 0BDh
		__emit 0A3h
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L14_66619F:
		push 0FFh
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 0CEh
		__emit 08Fh
		__emit 09Dh
		__emit 0FFh   // call 0x3F17A
		mov ecx, esi
		__emit 0E8h
		__emit 0F1h
		__emit 09Eh
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
L08_6661B3:
		mov ecx, dword ptr [esp+3Ch]
		pop edi
		pop esi
		pop ebp
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 38h
		ret
	}
}
