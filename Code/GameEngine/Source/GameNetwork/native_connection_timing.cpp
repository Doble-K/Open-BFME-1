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
