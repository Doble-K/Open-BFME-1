// cl: /DNDEBUG /MD /GX

typedef bool Bool;

class NetCommandMsg;

// Retail's real ConnectionManager, named so these two bodies carry their true
// mangled names; the BFME-native helpers below keep the BFMEConnectionManager
// name because theirs are unknown.
class ConnectionManager
{
public:
	void sendLocalCommand(NetCommandMsg *msg, unsigned char relay);
	void sendLocalCommandDirect(NetCommandMsg *msg, unsigned char relay);
};

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
	Bool isPlayerInGame(int slot);
	Bool isPlayerSlotActive(int slot);
	void markPlayerInGame(void *msg);
	void relayCommand(void *ref);
	void update();
	void runRelayPass();
	void resendFrameRangeToPlayer(int playerID, unsigned int startFrame, unsigned int endFrame);
};

class BFMEDisconnectManager
{
public:
	Bool hasDisconnectScreenNotifyTimedOut(int playerID);
	void update(void *conMgr);
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

// Real body, reached in retail through the ILT thunk at 0x0003F17A that the
// ledger used to claim on its own. Attaches the message, and when its execution
// frame is still -1 stamps max(TheGameLogic->getFrame(), 2) into it, then clears
// the local slot out of the relay mask before queueing.
__declspec(naked) void ConnectionManager::sendLocalCommandDirect(NetCommandMsg *msg, unsigned char relay)
{
	__asm {
		push ebx
		push ebp
		mov ebp, dword ptr [esp+0Ch]
		push esi
		push edi
		mov edi, ecx
		mov ecx, ebp
		__emit 0E8h
		__emit 08Fh
		__emit 0A0h
		__emit 09Ah
		__emit 0FFh   // call 0xD3A0
		cmp dword ptr [ebp+8h], 0FFFFFFFFh
		jne L00_66332C
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		mov eax, dword ptr [eax+3Ch]
		cmp eax, 2h
		ja L01_663329
		mov eax, 2h
L01_663329:
		mov dword ptr [ebp+8h], eax
L00_66332C:
		mov ecx, dword ptr [edi+12028h]
		movzx ebx, byte ptr [esp+18h]
		mov edx, 1h
		shl edx, cl
		__emit 085h
		__emit 0D3h   // test ebx, edx
		je L02_66336E
		mov eax, dword ptr [ebp+14h]
		push eax
		__emit 0E8h
		__emit 06Eh
		__emit 0ECh
		__emit 099h
		__emit 0FFh   // call 0x1FB9
		add esp, 4h
		test al, al
		je L02_66336E
		mov eax, dword ptr [edi+12028h]
		cmp eax, 8h
		jae L02_66336E
		mov ecx, dword ptr [edi+eax*4+120E4h]
		test ecx, ecx
		je L02_66336E
		push ebp
		__emit 0E8h
		__emit 0EFh
		__emit 0C7h
		__emit 09Ch
		__emit 0FFh   // call 0x2FB5D
L02_66336E:
		xor esi, esi
		add edi, 4h
L04_663373:
		mov eax, 1h
		mov ecx, esi
		shl eax, cl
		__emit 085h
		__emit 0C3h   // test ebx, eax
		je L03_663395
		mov eax, dword ptr [edi]
		test eax, eax
		je L03_663395
		xor edx, edx
		mov dl, 1h
		shl dl, cl
		mov ecx, eax
		push edx
		push ebp
		__emit 0E8h
		__emit 0A7h
		__emit 039h
		__emit 09Ch
		__emit 0FFh   // call 0x26D3C
L03_663395:
		inc esi
		add edi, 4h
		cmp esi, 8h
		jl L04_663373
		mov ecx, ebp
		__emit 0E8h
		__emit 0FFh
		__emit 0CCh
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		pop edi
		pop esi
		pop ebp
		pop ebx
		ret 8h
	}
}

// Real body, reached in retail through the ILT thunk at 0x000411D7. Drops the
// message if the filter at 0x00682E80 rejects it or the packet router's slot has
// no Connection, otherwise attaches it and splits: when we ARE the router it
// stamps max(TheGameLogic->getFrame(), 2) as the execution frame and fans the
// message out directly, and when we are not it hands it to the router alone.
__declspec(naked) void ConnectionManager::sendLocalCommand(NetCommandMsg *msg, unsigned char relay)
{
	__asm {
		push esi
		mov esi, dword ptr [esp+8h]
		push edi
		push esi
		mov edi, ecx
		__emit 0E8h
		__emit 006h
		__emit 0AAh
		__emit 09Bh
		__emit 0FFh   // call 0x1F154
		add esp, 4h
		test al, al
		jne L00_664843
		mov eax, dword ptr [edi+1202Ch]
		cmp eax, 8h
		jae L00_664843
		mov ecx, dword ptr [edi+eax*4+4h]
		test ecx, ecx
		je L00_664843
		mov ecx, esi
		__emit 0E8h
		__emit 025h
		__emit 08Ch
		__emit 09Ah
		__emit 0FFh   // call 0xD3A0
		mov eax, dword ptr [edi+1202Ch]
		cmp dword ptr [edi+12028h], eax
		jne L01_66481D
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		mov eax, dword ptr [eax+3Ch]
		cmp eax, 2h
		ja L02_66479F
		mov eax, 2h
L02_66479F:
		push ebx
		movzx ebx, byte ptr [esp+14h]
		push ebp
		mov dword ptr [esi+8h], eax
		xor esi, esi
		lea ebp,  [edi+4h]
		mov edi, edi
L04_6647B0:
		mov edx, 1h
		mov ecx, esi
		shl edx, cl
		__emit 085h
		__emit 0D3h   // test ebx, edx
		je L03_6647D7
		mov eax, dword ptr [ebp]
		test eax, eax
		je L03_6647D7
		xor edx, edx
		mov dl, 1h
		shl dl, cl
		mov ecx, dword ptr [esp+14h]
		push edx
		push ecx
		mov ecx, eax
		__emit 0E8h
		__emit 065h
		__emit 025h
		__emit 09Ch
		__emit 0FFh   // call 0x26D3C
L03_6647D7:
		inc esi
		add ebp, 4h
		cmp esi, 8h
		jl L04_6647B0
		mov ecx, dword ptr [edi+12028h]
		cmp ecx, 8h
		jae L05_66480B
		mov edx, 1h
		shl edx, cl
		__emit 085h
		__emit 0D3h   // test ebx, edx
		je L05_66480B
		mov ecx, dword ptr [edi+ecx*4+120E4h]
		test ecx, ecx
		je L05_66480B
		mov eax, dword ptr [esp+14h]
		push eax
		__emit 0E8h
		__emit 052h
		__emit 0B3h
		__emit 09Ch
		__emit 0FFh   // call 0x2FB5D
L05_66480B:
		mov esi, dword ptr [esp+14h]
		pop ebp
		pop ebx
L06_664811:
		mov ecx, esi
		__emit 0E8h
		__emit 08Ch
		__emit 0B8h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		pop edi
		pop esi
		ret 8h
L01_66481D:
		cmp eax, 8h
		jae L06_664811
		mov eax, dword ptr [edi+eax*4+4h]
		test eax, eax
		je L06_664811
		mov ecx, dword ptr [esp+10h]
		push ecx
		push esi
		mov ecx, eax
		__emit 0E8h
		__emit 005h
		__emit 025h
		__emit 09Ch
		__emit 0FFh   // call 0x26D3C
		mov ecx, esi
		__emit 0E8h
		__emit 066h
		__emit 0B8h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		pop edi
		pop esi
		ret 8h
L00_664843:
		mov edx, dword ptr [esp+10h]
		push edx
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 087h
		__emit 0C9h
		__emit 09Dh
		__emit 0FFh   // call 0x411D7
		pop edi
		pop esi
		ret 8h
	}
}

// A slot is in the game when its per-player state at this+0x12080 is exactly 1
// and either it is our own slot or its Connection at this+0x04 is open (the
// dword at Connection+0 is the -1 sentinel).
__declspec(naked) Bool BFMEConnectionManager::isPlayerInGame(int slot)
{
	__asm {
		mov eax, dword ptr [esp+4h]
		cmp eax, 8h
		jae L00_662C10
		cmp dword ptr [ecx+eax*4+12080h], 1h
		jne L00_662C10
		cmp eax, dword ptr [ecx+12028h]
		je L01_662C08
		mov eax, dword ptr [ecx+eax*4+4h]
		test eax, eax
		je L00_662C10
		cmp dword ptr [eax], 0FFFFFFFFh
		jne L00_662C10
L01_662C08:
		mov eax, 1h
		ret 4h
L00_662C10:
		xor eax, eax
		ret 4h
	}
}

// Same test as isPlayerInGame but accepting states 1 through 3, so a player who
// is on the way out still counts. Together the two bound the state values:
// 0 is an empty slot, 1 is in the game, 2 and 3 are leaving.
__declspec(naked) Bool BFMEConnectionManager::isPlayerSlotActive(int slot)
{
	__asm {
		mov eax, dword ptr [esp+4h]
		cmp eax, 8h
		jae L00_662C67
		mov edx, dword ptr [ecx+eax*4+12080h]
		cmp edx, 1h
		jl L00_662C67
		cmp edx, 3h
		jg L00_662C67
		cmp eax, dword ptr [ecx+12028h]
		je L01_662C5F
		mov eax, dword ptr [ecx+eax*4+4h]
		test eax, eax
		je L00_662C67
		cmp dword ptr [eax], 0FFFFFFFFh
		jne L00_662C67
L01_662C5F:
		mov eax, 1h
		ret 4h
L00_662C67:
		xor eax, eax
		ret 4h
	}
}

// Moves a slot from empty to in-game: reads the message's player id (retail
// re-reads it through the accessor all three times rather than keeping it in a
// register) and, if the state at this+0x12080 is still 0, sets it to 1.
__declspec(naked) void BFMEConnectionManager::markPlayerInGame(void *msg)
{
	__asm {
		push esi
		push edi
		mov edi, dword ptr [esp+0Ch]
		mov esi, ecx
		mov ecx, edi
		__emit 0E8h
		__emit 08Fh
		__emit 016h
		__emit 09Ch
		__emit 0FFh   // call 0x2442E
		cmp eax, 8h
		jae L00_662DC8
		mov ecx, edi
		__emit 0E8h
		__emit 083h
		__emit 016h
		__emit 09Ch
		__emit 0FFh   // call 0x2442E
		mov ecx, dword ptr [esi+eax*4+12080h]
		test ecx, ecx
		jne L00_662DC8
		mov ecx, edi
		__emit 0E8h
		__emit 071h
		__emit 016h
		__emit 09Ch
		__emit 0FFh   // call 0x2442E
		mov dword ptr [esi+eax*4+12080h], 1h
L00_662DC8:
		pop edi
		pop esi
		ret 4h
	}
}

// Relays one queued command. Reads the message straight off the reference's
// first dword -- BFME de-pooled NetCommandRef, so m_msg is at +0 where ZH has a
// vptr -- stamps TheGameLogic's frame into the message when its execution frame
// is still -1, drops it when that frame plus NetworkKeepAliveDelay has already
// passed, and then tests the reference's relay byte at +0x0C against our own
// slot bit. Together with NetCommandList::reset this pins the 20-byte
// NetCommandRef: m_msg +0, m_next +4, m_prev +8, m_relay +0x0C.
__declspec(naked) void BFMEConnectionManager::relayCommand(void *ref)
{
	__asm {
		mov eax, dword ptr [esp+4h]
		push ebx
		push edi
		mov edi, dword ptr [eax]
		test edi, edi
		mov ebx, ecx
		je L00_6631E8
		cmp dword ptr [edi+8h], 0FFFFFFFFh
		jne L01_663124
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		mov edx, dword ptr [ecx+3Ch]
		mov dword ptr [edi+8h], edx
L01_663124:
		__emit 08Bh
		__emit 00Dh
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h   // mov ecx, dword ptr [0x12ed5c8]
		mov edx, dword ptr [ecx+0CB4h]
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		push ebp
		mov ebp, dword ptr [edi+8h]
		push esi
		mov esi, dword ptr [ecx+3Ch]
		add edx, ebp
		cmp edx, esi
		jb L02_6631E6
		mov ecx, dword ptr [ebx+12028h]
		movzx eax, byte ptr [eax+0Ch]
		mov edx, 1h
		shl edx, cl
		mov dword ptr [esp+14h], eax
		__emit 085h
		__emit 0D0h   // test eax, edx
		je L02_6631E6
		mov eax, dword ptr [edi+0Ch]
		mov ecx, dword ptr [ebx+eax*4+120E4h]
		test ecx, ecx
		je L02_6631E6
		mov eax, dword ptr [edi+14h]
		push eax
		__emit 0E8h
		__emit 03Dh
		__emit 0EEh
		__emit 099h
		__emit 0FFh   // call 0x1FB9
		add esp, 4h
		test al, al
		je L02_6631E6
		mov ecx, dword ptr [edi+0Ch]
		cmp ecx, dword ptr [ebx+12028h]
		jne L03_66319B
		cmp dword ptr [edi+14h], 0Ah
		je L03_66319B
		mov edx, dword ptr [edi]
		mov ecx, edi
		call dword ptr [edx+8h]
L03_66319B:
		mov eax, dword ptr [edi+0Ch]
		mov ecx, dword ptr [ebx+eax*4+120E4h]
		push edi
		__emit 0E8h
		__emit 0B2h
		__emit 0C9h
		__emit 09Ch
		__emit 0FFh   // call 0x2FB5D
		test eax, eax
		je L02_6631E6
		xor esi, esi
		lea ebp,  [ebx+4h]
L05_6631B4:
		mov ecx, esi
		mov eax, 1h
		shl eax, cl
		mov ecx, dword ptr [esp+14h]
		__emit 085h
		__emit 0C1h   // test ecx, eax
		je L04_6631DD
		mov eax, dword ptr [ebp]
		test eax, eax
		je L04_6631DD
		xor edx, edx
		mov dl, 1h
		mov ecx, esi
		shl dl, cl
		mov ecx, eax
		push edx
		push edi
		__emit 0E8h
		__emit 05Fh
		__emit 03Bh
		__emit 09Ch
		__emit 0FFh   // call 0x26D3C
L04_6631DD:
		inc esi
		add ebp, 4h
		cmp esi, 8h
		jl L05_6631B4
L02_6631E6:
		pop esi
		pop ebp
L00_6631E8:
		pop edi
		pop ebx
		ret 4h
	}
}

// The frame-data resender, and the far end of the REQUESTFRAMEDATA round trip.
// Distinct from retail's own two-argument ConnectionManager::sendFrameDataToPlayer
// (0x00664D20), which only raises a per-player watermark:
// the matched processRequestFrameDataCommand (0x006659B0) reaches it through the
// ILT thunk at 0x0000D8CD after clamping the requested window. It walks the
// eight FrameDataManagers at this+0x120E4 over the requested frame range,
// re-sends each stored command to the requesting slot alone, and issues a
// FRAMEINFO carrying getFrameCommandCount so the receiver knows how many to
// expect.
__declspec(naked) void BFMEConnectionManager::resendFrameRangeToPlayer(int playerID, unsigned int startFrame, unsigned int endFrame)
{
	__asm {
		push 0FFFFFFFFh
		push 104414Bh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		mov eax, dword ptr [eax+3Ch]
		push ebp
		push esi
		push edi
		dec eax
		mov edi, ecx
		mov ecx, dword ptr [esp+28h]
		mov dword ptr [esp+0Ch], eax
		cmp eax, ecx
		lea eax,  [esp+0Ch]
		jb L00_664B78
		lea eax,  [esp+28h]
L00_664B78:
		mov edx, dword ptr [eax]
		__emit 08Bh
		__emit 00Dh
		__emit 08Ch
		__emit 0A0h
		__emit 02Bh
		__emit 001h   // mov ecx, dword ptr [0x12ba08c]
		mov eax, dword ptr [esp+24h]
		__emit 08Dh
		__emit 034h
		__emit 001h   // lea esi, [ecx + eax]
		cmp esi, edx
		mov dword ptr [esp+0Ch], edx
		jae L01_664B9B
		cmp edx, ecx
		jbe L02_664B99
		mov eax, edx
		sub eax, ecx
		jmp L01_664B9B
L02_664B99:
		xor eax, eax
L01_664B9B:
		cmp eax, edx
		mov ebp, eax
		ja L03_664CAC
		mov ecx, dword ptr [esp+20h]
		mov dl, 1h
		shl dl, cl
		push ebx
		mov byte ptr [esp+2Ch], dl
		mov ebx, dword ptr [esp+2Ch]
L10_664BB6:
		lea eax,  [edi+120E4h]
		mov dword ptr [esp+2Ch], eax
		mov dword ptr [esp+28h], 8h
L06_664BC8:
		mov ecx, dword ptr [eax]
		test ecx, ecx
		je L04_664BF2
		push ebp
		__emit 0E8h
		__emit 0FDh
		__emit 0EEh
		__emit 09Dh
		__emit 0FFh   // call 0x43AD1
		test eax, eax
		je L04_664BF2
		mov esi, dword ptr [eax+4h]
		test esi, esi
		je L04_664BF2
		nop
L05_664BE0:
		mov eax, dword ptr [esi]
		push ebx
		push eax
		mov ecx, edi
		__emit 0E8h
		__emit 0ECh
		__emit 0C5h
		__emit 09Dh
		__emit 0FFh   // call 0x411D7
		mov esi, dword ptr [esi+4h]
		test esi, esi
		jne L05_664BE0
L04_664BF2:
		mov eax, dword ptr [esp+2Ch]
		mov ecx, dword ptr [esp+28h]
		add eax, 4h
		dec ecx
		mov dword ptr [esp+2Ch], eax
		mov dword ptr [esp+28h], ecx
		jne L06_664BC8
		push 28h
		__emit 0E8h
		__emit 021h
		__emit 0D3h
		__emit 021h
		__emit 000h   // call 0x881F30
		mov esi, eax
		add esp, 4h
		mov dword ptr [esp+2Ch], esi
		test esi, esi
		mov dword ptr [esp+1Ch], 0h
		je L07_664C49
		mov ecx, esi
		__emit 0E8h
		__emit 089h
		__emit 0E6h
		__emit 09Ah
		__emit 0FFh   // call 0x132B4
		xor eax, eax
		mov dword ptr [esi], 111A220h
		mov dword ptr [esi+1Ch], eax
		mov dword ptr [esi+20h], eax
		mov dword ptr [esi+24h], 0FFFFFFFFh
		mov dword ptr [esi+14h], 3h
		jmp L08_664C4B
L07_664C49:
		xor esi, esi
L08_664C4B:
		mov eax, dword ptr [esi+14h]
		push eax
		mov dword ptr [esp+20h], 0FFFFFFFFh
		mov dword ptr [esi+1Ch], ebp
		__emit 0E8h
		__emit 013h
		__emit 00Fh
		__emit 09Bh
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L09_664C6F
		__emit 0E8h
		__emit 0EDh
		__emit 0B8h
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L09_664C6F:
		mov eax, dword ptr [edi+12028h]
		mov dword ptr [esi+0Ch], eax
		mov ecx, dword ptr [edi+12028h]
		mov ecx, dword ptr [edi+ecx*4+120E4h]
		push ebp
		__emit 0E8h
		__emit 018h
		__emit 08Bh
		__emit 09Dh
		__emit 0FFh   // call 0x3D7A3
		push ebx
		push esi
		mov ecx, edi
		mov dword ptr [esi+24h], eax
		__emit 0E8h
		__emit 040h
		__emit 0C5h
		__emit 09Dh
		__emit 0FFh   // call 0x411D7
		mov ecx, esi
		__emit 0E8h
		__emit 006h
		__emit 0B4h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		mov eax, dword ptr [esp+10h]
		inc ebp
		cmp ebp, eax
		jbe L10_664BB6
		pop ebx
L03_664CAC:
		mov ecx, dword ptr [esp+10h]
		pop edi
		pop esi
		pop ebp
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret 0Ch
	}
}

// The per-tick network update, and what drives the delay cadence: it is the
// only caller of sendFrameInfo, so the frame ceiling is published from here.
// It also runs the relay pass (0x0066A740) and the disconnect/timeout sweep
// (0x0066C8D0), builds keep-alive and progress commands, and touches the tail
// scalars at this+0x12050, +0x12054, +0x120E0, +0x12114 and +0x12115. Nothing
// in .text calls it directly and it is in no recovered vtable, so retail must
// reach it through a stored function pointer.
__declspec(naked) void BFMEConnectionManager::update()
{
	__asm {
		push 0FFFFFFFFh
		push 104473Bh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 44h
		push ebx
		push ebp
		mov ebp, ecx
		mov eax, dword ptr [ebp+12050h]
		xor ebx, ebx
		cmp eax, ebx
		push esi
		push edi
		mov dword ptr [esp+10h], ebx
		jne L00_66AB6B
		cmp word ptr [ebp+12054h], bx
		je L01_66AE49
L00_66AB6B:
		mov ecx, dword ptr [ebp+12024h]
		cmp ecx, ebx
		je L02_66AB7A
		__emit 0E8h
		__emit 055h
		__emit 0E5h
		__emit 099h
		__emit 0FFh   // call 0x90CF
L02_66AB7A:
		mov al, byte ptr [esp+64h]
		test al, al
		je L03_66ABCA
		mov ecx, dword ptr [ebp+120E0h]
		cmp ecx, ebx
		je L04_66AB92
		push ebp
		__emit 0E8h
		__emit 0EEh
		__emit 0E4h
		__emit 09Dh
		__emit 0FFh   // call 0x49080
L04_66AB92:
		mov ecx, ebp
		__emit 0E8h
		__emit 0E5h
		__emit 0FAh
		__emit 09Dh
		__emit 0FFh   // call 0x4A67E
		cmp dword ptr [esp+68h], ebx
		je L03_66ABCA
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
		cmp ecx, ebx
		je L05_66ABC3
		mov eax, dword ptr [ecx]
		call dword ptr [eax+0DCh]
		test al, al
		je L05_66ABC3
		mov ecx, dword ptr [ebp+12028h]
		cmp ecx, dword ptr [ebp+1202Ch]
		je L03_66ABCA
L05_66ABC3:
		mov ecx, ebp
		__emit 0E8h
		__emit 043h
		__emit 04Bh
		__emit 09Bh
		__emit 0FFh   // call 0x1F70D
L03_66ABCA:
		__emit 0A1h
		__emit 098h
		__emit 071h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f7198]
		cmp eax, ebx
		je L06_66AD90
		__emit 039h
		__emit 01Dh
		__emit 0B4h
		__emit 071h
		__emit 02Fh
		__emit 001h   // cmp dword ptr [0x12f71b4], ebx
		je L06_66AD90
		mov cl, byte ptr [ebp+12115h]
		test cl, cl
		je L06_66AD90
		mov cl, byte ptr [eax+43Ch]
		test cl, cl
		je L07_66AD89
		mov edx, dword ptr [eax+464h]
		push edx
		mov edi, 111A2C0h
		__emit 0E8h
		__emit 090h
		__emit 08Dh
		__emit 036h
		__emit 000h   // call 0x9D39A0
		add esp, 4h
		mov esi, eax
		mov ecx, 9h
		xor eax, eax
		repe cmpsb
		je L06_66AD90
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 071h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7198]
		mov edx, dword ptr [ecx+464h]
		push edx
		__emit 0E8h
		__emit 06Ah
		__emit 08Dh
		__emit 036h
		__emit 000h   // call 0x9D39A0
		push eax
		__emit 0E8h
		__emit 074h
		__emit 097h
		__emit 01Eh
		__emit 000h   // call 0x8543B0
		push 20h
		mov ebx, eax
		__emit 0E8h
		__emit 0EBh
		__emit 072h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 0Ch
		mov dword ptr [esp+64h], eax
		xor esi, esi
		cmp eax, esi
		mov dword ptr [esp+5Ch], esi
		je L08_66AC5F
		mov ecx, eax
		__emit 0E8h
		__emit 00Dh
		__emit 0E3h
		__emit 09Bh
		__emit 0FFh   // call 0x28F6A
		mov esi, eax
L08_66AC5F:
		mov ecx, dword ptr [ebp+12028h]
		or eax, 0FFFFFFFFh
		mov dword ptr [esp+5Ch], eax
		mov dword ptr [esi+8h], eax
		mov eax, dword ptr [esi+14h]
		push eax
		mov dword ptr [esi+0Ch], ecx
		__emit 0E8h
		__emit 0F7h
		__emit 0AEh
		__emit 09Ah
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L09_66AC8B
		__emit 0E8h
		__emit 0D1h
		__emit 058h
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L09_66AC8B:
		push ecx
		mov ecx, esp
		mov dword ptr [esp+68h], esp
		push ebx
		__emit 0E8h
		__emit 0AAh
		__emit 07Fh
		__emit 09Ah
		__emit 0FFh   // call 0x12C42
		mov ecx, esi
		__emit 0E8h
		__emit 0C6h
		__emit 0FDh
		__emit 099h
		__emit 0FFh   // call 0xAA65
		mov ecx, dword ptr [ebp+12028h]
		xor edx, edx
		mov dl, 1h
		shl dl, cl
		mov ecx, ebp
		not dl
		push edx
		push esi
		__emit 0E8h
		__emit 021h
		__emit 065h
		__emit 09Dh
		__emit 0FFh   // call 0x411D7
		mov ecx, esi
		__emit 0E8h
		__emit 0E7h
		__emit 053h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		__emit 08Bh
		__emit 00Dh
		__emit 0B4h
		__emit 071h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f71b4]
		mov eax, dword ptr [ecx]
		call dword ptr [eax+30h]
		push eax
		__emit 0E8h
		__emit 0E2h
		__emit 096h
		__emit 01Eh
		__emit 000h   // call 0x8543B0
		lea ecx,  [esp+18h]
		push ecx
		mov edi, eax
		push edi
		push ebx
		__emit 0E8h
		__emit 0D4h
		__emit 07Dh
		__emit 036h
		__emit 000h   // call 0x9D2AB0
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 071h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7198]
		mov edx, dword ptr [ecx]
		add esp, 10h
		call dword ptr [edx+14h]
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 071h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7198]
		push eax
		__emit 0E8h
		__emit 0E0h
		__emit 0B4h
		__emit 099h
		__emit 0FFh   // call 0x61D6
		mov esi, eax
		test esi, esi
		je L10_66AD22
		lea eax,  [esp+68h]
		push eax
		mov ecx, esi
		__emit 0E8h
		__emit 0D0h
		__emit 0C0h
		__emit 09Ah
		__emit 0FFh   // call 0x16DD8
		mov eax, dword ptr [eax]
		test eax, eax
		mov ecx, 1h
		je L11_66AD1B
		movzx eax, word ptr [eax+4h]
		test eax, eax
		jne L12_66AD26
L11_66AD1B:
		mov byte ptr [esp+64h], 1h
		jmp L13_66AD2B
L10_66AD22:
		mov cl, byte ptr [esp+10h]
L12_66AD26:
		mov byte ptr [esp+64h], 0h
L13_66AD2B:
		test cl, 1h
		je L14_66AD39
		lea ecx,  [esp+68h]
		__emit 0E8h
		__emit 007h
		__emit 0CCh
		__emit 021h
		__emit 000h   // call 0x887940
L14_66AD39:
		mov al, byte ptr [esp+64h]
		test al, al
		je L15_66AD78
		push ecx
		lea edx,  [esp+18h]
		mov dword ptr [esp+68h], esp
		mov ecx, esp
		push edx
		__emit 0E8h
		__emit 06Eh
		__emit 0DEh
		__emit 021h
		__emit 000h   // call 0x888BC0
		mov ecx, esi
		__emit 0E8h
		__emit 0F9h
		__emit 0DBh
		__emit 09Bh
		__emit 0FFh   // call 0x28952
		__emit 08Bh
		__emit 00Dh
		__emit 0B4h
		__emit 071h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f71b4]
		mov eax, dword ptr [ecx]
		call dword ptr [eax+2Ch]
		push ecx
		mov ecx, esp
		mov dword ptr [esp+68h], esp
		push eax
		__emit 0E8h
		__emit 0D1h
		__emit 07Eh
		__emit 09Ah
		__emit 0FFh   // call 0x12C42
		mov ecx, esi
		__emit 0E8h
		__emit 0B9h
		__emit 0BFh
		__emit 09Ch
		__emit 0FFh   // call 0x36D31
L15_66AD78:
		__emit 08Bh
		__emit 035h
		__emit 0D4h
		__emit 093h
		__emit 035h
		__emit 001h   // mov esi, dword ptr [0x13593d4]
		push ebx
		call esi
		push edi
		call esi
		add esp, 8h
		xor ebx, ebx
L07_66AD89:
		mov byte ptr [ebp+12115h], 0h
L06_66AD90:
		mov ecx, ebp
		__emit 0E8h
		__emit 022h
		__emit 0A3h
		__emit 09Ah
		__emit 0FFh   // call 0x150B9
		lea esi,  [ebp+4h]
		mov dword ptr [esp+64h], 8h
L20_66ADA2:
		mov ecx, dword ptr [esi]
		cmp ecx, ebx
		je L16_66ADE6
		xor edx, edx
		mov dl, byte ptr [ebp+12114h]
		push edx
		__emit 0E8h
		__emit 07Dh
		__emit 088h
		__emit 09Ah
		__emit 0FFh   // call 0x13633
		mov ecx, dword ptr [esi]
		__emit 08Bh
		__emit 015h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov edx, dword ptr [0x12f0898]
		mov eax, dword ptr [ecx]
		cmp eax, dword ptr [edx+3Ch]
		ja L16_66ADE6
		__emit 0E8h
		__emit 0EEh
		__emit 02Fh
		__emit 09Bh
		__emit 0FFh   // call 0x1DDB8
		test al, al
		je L16_66ADE6
		mov edi, dword ptr [esi]
		cmp edi, ebx
		je L17_66ADE4
		mov ecx, edi
		__emit 0E8h
		__emit 0F4h
		__emit 020h
		__emit 09Dh
		__emit 0FFh   // call 0x3CECF
		push edi
		__emit 0E8h
		__emit 0CFh
		__emit 070h
		__emit 021h
		__emit 000h   // call 0x881EB0
		add esp, 4h
L17_66ADE4:
		mov dword ptr [esi], ebx
L16_66ADE6:
		mov ecx, dword ptr [esi+120E0h]
		cmp ecx, ebx
		je L18_66AE26
		__emit 0E8h
		__emit 0E7h
		__emit 088h
		__emit 09Bh
		__emit 0FFh   // call 0x236DC
		test al, al
		je L18_66AE26
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		mov ecx, dword ptr [esi+120E0h]
		mov edi, dword ptr [eax+3Ch]
		__emit 0E8h
		__emit 0ADh
		__emit 009h
		__emit 09Dh
		__emit 0FFh   // call 0x3B7B9
		cmp eax, edi
		jne L18_66AE26
		mov ecx, dword ptr [esi+120E0h]
		cmp ecx, ebx
		je L19_66AE20
		mov edx, dword ptr [ecx]
		push 1h
		call dword ptr [edx]
L19_66AE20:
		mov dword ptr [esi+120E0h], ebx
L18_66AE26:
		mov eax, dword ptr [esp+64h]
		add esi, 4h
		dec eax
		mov dword ptr [esp+64h], eax
		jne L20_66ADA2
		mov ebp, dword ptr [ebp+12024h]
		cmp ebp, ebx
		je L01_66AE49
		mov ecx, ebp
		__emit 0E8h
		__emit 0F5h
		__emit 0AEh
		__emit 09Ah
		__emit 0FFh   // call 0x15D3E
L01_66AE49:
		mov ecx, dword ptr [esp+54h]
		pop edi
		pop esi
		pop ebp
		mov dword ptr fs:[0h], ecx
		pop ebx
		add esp, 50h
		ret 8h
	}
}

// The relay pass update() drives. Off the packet router it does nothing; as
// router it walks the eight per-player states at this+0x12080 with a 0x20C-byte
// packet buffer on an eight-aligned stack frame, feeding what it reads to
// processIncomingCommand and relayCommand and fanning the results back out with
// sendLocalCommand.
__declspec(naked) void BFMEConnectionManager::runRelayPass()
{
	__asm {
		push ebp
		mov ebp, esp
		and esp, 0FFFFFFF8h
		push 0FFFFFFFFh
		push 1044717h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 20Ch
		push ebx
		push ebp
		push esi
		push edi
		mov edi, ecx
		mov eax, dword ptr [edi+12028h]
		cmp eax, dword ptr [edi+1202Ch]
		jne L00_66A8AE
		xor ebx, ebx
		lea ebp,  [edi+12080h]
		cmp ebx, 8h
L08_66A784:
		jae L01_66A8A1
		cmp dword ptr [ebp], 1h
		jne L01_66A8A1
		cmp ebx, dword ptr [edi+12028h]
		je L02_66A7B3
		mov eax, dword ptr [ebp-1207Ch]
		test eax, eax
		je L01_66A8A1
		cmp dword ptr [eax], 0FFFFFFFFh
		jne L01_66A8A1
L02_66A7B3:
		push 20h
		__emit 0E8h
		__emit 076h
		__emit 077h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+10h], eax
		xor esi, esi
		cmp eax, esi
		mov dword ptr [esp+224h], esi
		je L03_66A7D7
		mov ecx, eax
		__emit 0E8h
		__emit 0B8h
		__emit 0A4h
		__emit 09Dh
		__emit 0FFh   // call 0x44C8D
		mov esi, eax
L03_66A7D7:
		push ebx
		mov ecx, esi
		mov dword ptr [esp+228h], 0FFFFFFFFh
		__emit 0E8h
		__emit 063h
		__emit 01Ch
		__emit 09Dh
		__emit 0FFh   // call 0x3C44D
		mov eax, dword ptr [esi+14h]
		push eax
		mov dword ptr [esi+8h], 0FFFFFFFFh
		__emit 0E8h
		__emit 078h
		__emit 0B3h
		__emit 09Ah
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L04_66A80A
		__emit 0E8h
		__emit 052h
		__emit 05Dh
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L04_66A80A:
		mov eax, dword ptr [edi+12028h]
		push 0FFh
		push esi
		mov ecx, edi
		mov dword ptr [esi+0Ch], eax
		__emit 0E8h
		__emit 05Ah
		__emit 049h
		__emit 09Dh
		__emit 0FFh   // call 0x3F17A
		mov ecx, esi
		__emit 0E8h
		__emit 07Dh
		__emit 058h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		push 20h
		__emit 0E8h
		__emit 002h
		__emit 077h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+10h], eax
		test eax, eax
		mov dword ptr [esp+224h], 1h
		je L05_66A84F
		mov ecx, eax
		__emit 0E8h
		__emit 0B9h
		__emit 010h
		__emit 09Ch
		__emit 0FFh   // call 0x2B904
		mov esi, eax
		jmp L06_66A851
L05_66A84F:
		xor esi, esi
L06_66A851:
		mov eax, dword ptr [esi+14h]
		push eax
		mov dword ptr [esp+228h], 0FFFFFFFFh
		__emit 0E8h
		__emit 00Dh
		__emit 0B3h
		__emit 09Ah
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L07_66A875
		__emit 0E8h
		__emit 0E7h
		__emit 05Ch
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L07_66A875:
		mov eax, dword ptr [edi+12028h]
		push ebx
		mov ecx, esi
		mov dword ptr [esi+0Ch], eax
		__emit 0E8h
		__emit 0ADh
		__emit 0C3h
		__emit 09Bh
		__emit 0FFh   // call 0x26C33
		push 0FFh
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 0E7h
		__emit 048h
		__emit 09Dh
		__emit 0FFh   // call 0x3F17A
		mov ecx, esi
		__emit 0E8h
		__emit 00Ah
		__emit 058h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		mov dword ptr [ebp], 2h
L01_66A8A1:
		inc ebx
		add ebp, 4h
		cmp ebx, 8h
		jl L08_66A784
L00_66A8AE:
		xor ebx, ebx
L15_66A8B0:
		mov eax, dword ptr [edi+12024h]
		mov ecx, dword ptr [ebx+eax+20B04h]
		test ecx, ecx
		je L09_66A9AE
		lea ecx,  [ebx+eax+20700h]
		push ecx
		lea ecx,  [esp+1Ch]
		__emit 0E8h
		__emit 0BAh
		__emit 0E8h
		__emit 09Bh
		__emit 0FFh   // call 0x29190
		mov edx, dword ptr [edi+12024h]
		lea ecx,  [esp+18h]
		mov dword ptr [esp+224h], 2h
		mov dword ptr [ebx+edx+20B04h], 0h
		__emit 0E8h
		__emit 040h
		__emit 002h
		__emit 09Bh
		__emit 0FFh   // call 0x1AB3B
		mov ecx, dword ptr [esp+200h]
		mov ebp, eax
		mov esi, dword ptr [ebp+4h]
		test esi, esi
		mov eax, dword ptr [esp+1FCh]
		mov dword ptr [esp+10h], eax
		mov dword ptr [esp+14h], ecx
		je L10_66A991
		__emit 08Dh
		__emit 09Bh
		__emit 000h
		__emit 000h
		__emit 000h
		__emit 000h   // lea ebx, [ebx]
L14_66A920:
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
		test ecx, ecx
		je L11_66A94C
		mov edx, dword ptr [ecx]
		call dword ptr [edx+0DCh]
		test al, al
		je L11_66A94C
		mov eax, dword ptr [edi+12028h]
		cmp eax, dword ptr [edi+1202Ch]
		jne L11_66A94C
		mov eax, dword ptr [esi]
		cmp dword ptr [eax+14h], 3h
		jne L12_66A98A
L11_66A94C:
		mov eax, dword ptr [esi]
		push eax
		__emit 0E8h
		__emit 029h
		__emit 077h
		__emit 09Dh
		__emit 0FFh   // call 0x4207D
		add esp, 4h
		test al, al
		je L13_66A968
		lea ecx,  [esp+10h]
		push ecx
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 0DBh
		__emit 0E3h
		__emit 09Ch
		__emit 0FFh   // call 0x38D43
L13_66A968:
		mov eax, dword ptr [esi]
		push eax
		mov ecx, edi
		__emit 0E8h
		__emit 001h
		__emit 0EEh
		__emit 099h
		__emit 0FFh   // call 0x9773
		test al, al
		jne L12_66A98A
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 0F9h
		__emit 0C6h
		__emit 099h
		__emit 0FFh   // call 0x7077
		test al, al
		je L12_66A98A
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 050h
		__emit 0D6h
		__emit 09Ah
		__emit 0FFh   // call 0x17FDA
L12_66A98A:
		mov esi, dword ptr [esi+4h]
		test esi, esi
		jne L14_66A920
L10_66A991:
		mov edx, dword ptr [ebp]
		push 1h
		mov ecx, ebp
		call dword ptr [edx]
		lea ecx,  [esp+18h]
		mov dword ptr [esp+224h], 0FFFFFFFFh
		__emit 0E8h
		__emit 0A9h
		__emit 026h
		__emit 09Bh
		__emit 0FFh   // call 0x1D057
L09_66A9AE:
		add ebx, 40Eh
		cmp ebx, 20700h
		jl L15_66A8B0
		mov ecx, dword ptr [edi+1210Ch]
		test ecx, ecx
		je L16_66AA48
		__emit 0E8h
		__emit 070h
		__emit 03Ah
		__emit 09Ah
		__emit 0FFh   // call 0xE43F
		mov ebx, eax
		mov esi, dword ptr [ebx+4h]
		test esi, esi
		je L17_66AA40
		jmp L18_66A9E0
		__emit 08Dh
		__emit 09Bh
		__emit 000h
		__emit 000h
		__emit 000h
		__emit 000h   // lea ebx, [ebx]
L18_66A9E0:
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
		test ecx, ecx
		je L19_66AA0C
		mov eax, dword ptr [ecx]
		call dword ptr [eax+0DCh]
		test al, al
		je L19_66AA0C
		mov ecx, dword ptr [edi+12028h]
		cmp ecx, dword ptr [edi+1202Ch]
		jne L19_66AA0C
		mov edx, dword ptr [esi]
		cmp dword ptr [edx+14h], 3h
		jne L20_66AA39
L19_66AA0C:
		mov eax, dword ptr [esi]
		push eax
		__emit 0E8h
		__emit 069h
		__emit 076h
		__emit 09Dh
		__emit 0FFh   // call 0x4207D
		add esp, 4h
		test al, al
		je L21_66AA25
		push 0h
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 01Eh
		__emit 0E3h
		__emit 09Ch
		__emit 0FFh   // call 0x38D43
L21_66AA25:
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 04Ah
		__emit 0C6h
		__emit 099h
		__emit 0FFh   // call 0x7077
		test al, al
		je L20_66AA39
		push esi
		mov ecx, edi
		__emit 0E8h
		__emit 0A1h
		__emit 0D5h
		__emit 09Ah
		__emit 0FFh   // call 0x17FDA
L20_66AA39:
		mov esi, dword ptr [esi+4h]
		test esi, esi
		jne L18_66A9E0
L17_66AA40:
		mov eax, dword ptr [ebx]
		push 1h
		mov ecx, ebx
		call dword ptr [eax]
L16_66AA48:
		mov ecx, dword ptr [esp+21Ch]
		pop edi
		mov dword ptr fs:[0h], ecx
		pop esi
	}
}

// The disconnect and timeout sweep, run once per tick from
// BFMEConnectionManager::update. It reaches every timing gate already matched
// in this file -- isPlayerConnected, isPlayerConnectedForTimeout,
// isPlayerSlotActive -- and maintains the blame-assignment tail of
// DisconnectManager: m_timeOfDisconnectScreenOn at +0x25C, m_pingsSent at
// +0x260, m_pingsRecieved at +0x264 and m_pingFrame at +0x268, which is the
// same tail the disconnectmanager shim pins. Ghidra sizes it 1119, three bytes
// short of its ret.
__declspec(naked) void BFMEDisconnectManager::update(void *conMgr)
{
	__asm {
		push 0FFFFFFFFh
		push 1044848h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 34h
		push ebx
		push ebp
		push esi
		push edi
		mov esi, ecx
		__emit 0E8h
		__emit 009h
		__emit 06Eh
		__emit 099h
		__emit 0FFh   // call 0x36FC
		mov ebx, dword ptr [esp+54h]
		xor edi, edi
		mov ecx, ebx
		mov dword ptr [esp+14h], edi
		mov byte ptr [esp+13h], 0h
		__emit 0E8h
		__emit 088h
		__emit 0D9h
		__emit 09Dh
		__emit 0FFh   // call 0x4A291
		mov ebp, eax
		mov dword ptr [esp+54h], ebp
		nop
L08_66C910:
		push edi
		mov ecx, ebx
		__emit 0E8h
		__emit 09Ah
		__emit 0BDh
		__emit 09Dh
		__emit 0FFh   // call 0x486B2
		test al, al
		jne L00_66C93E
		push edi
		mov ecx, ebx
		__emit 0E8h
		__emit 026h
		__emit 088h
		__emit 09Ah
		__emit 0FFh   // call 0x1514A
		test al, al
		je L00_66C93E
		push 1388h
		push edi
		mov ecx, ebx
		__emit 0E8h
		__emit 026h
		__emit 08Eh
		__emit 09Ch
		__emit 0FFh   // call 0x3575B
		test al, al
		jne L00_66C93E
		mov byte ptr [esp+13h], 1h
L00_66C93E:
		push edi
		mov ecx, ebx
		__emit 0E8h
		__emit 0F0h
		__emit 027h
		__emit 09Bh
		__emit 0FFh   // call 0x1F136
		test al, al
		jne L01_66C9AC
		push edi
		mov ecx, ebx
		__emit 0E8h
		__emit 060h
		__emit 0BDh
		__emit 09Dh
		__emit 0FFh   // call 0x486B2
		test al, al
		jne L01_66C9AC
		push edi
		mov ecx, ebx
		__emit 0E8h
		__emit 0ECh
		__emit 087h
		__emit 09Ah
		__emit 0FFh   // call 0x1514A
		test al, al
		je L01_66C9AC
		inc dword ptr [esp+14h]
		mov eax, dword ptr [esi+260h]
		test eax, eax
		mov ecx, edi
		mov dword ptr [esp+18h], eax
		jle L02_66C98F
		fild dword ptr [esi+264h]
		fidiv dword ptr [esp+18h]
		__emit 0D8h
		__emit 01Dh
		__emit 070h
		__emit 05Ch
		__emit 007h
		__emit 001h   // fcomp dword ptr [0x1075c70]
		fnstsw ax
		test ah, 5h
		jp L02_66C98F
		mov ecx, ebp
L02_66C98F:
		mov al, byte ptr [ecx+esi+282h]
		test al, al
		jne L03_66C9ED
		mov byte ptr [ecx+esi+282h], 1h
		inc word ptr [esi+ecx*2+272h]
		jmp L03_66C9ED
L01_66C9AC:
		cmp edi, ebp
		je L04_66C9B8
		mov byte ptr [edi+esi+282h], 0h
L04_66C9B8:
		mov ecx, ebx
		__emit 0E8h
		__emit 0D2h
		__emit 0D8h
		__emit 09Dh
		__emit 0FFh   // call 0x4A291
		cmp edi, eax
		jge L05_66C9CE
		mov eax, edi
		__emit 08Dh
		__emit 02Ch
		__emit 0BDh
		__emit 000h
		__emit 000h
		__emit 000h
		__emit 000h   // lea ebp, [edi*4]
		jmp L06_66C9DA
L05_66C9CE:
		je L03_66C9ED
		lea eax,  [edi-1h]
		lea ebp,  [edi*4-4h]
L06_66C9DA:
		cmp eax, 0FFFFFFFFh
		je L07_66C9E9
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h   // call dword ptr [0x1359544]
		mov dword ptr [esi+ebp+14h], eax
L07_66C9E9:
		mov ebp, dword ptr [esp+54h]
L03_66C9ED:
		inc edi
		cmp edi, 8h
		jl L08_66C910
		mov eax, dword ptr [esp+14h]
		test eax, eax
		jne L09_66CA78
		mov byte ptr [esi+ebp+282h], al
L15_66CA06:
		mov eax, dword ptr [esi+0Ch]
		test eax, eax
		mov byte ptr [esi+270h], 0h
		jne L10_66CA4B
		mov ecx, ebx
		__emit 0E8h
		__emit 076h
		__emit 0D8h
		__emit 09Dh
		__emit 0FFh   // call 0x4A291
		mov edi, eax
		cmp dword ptr [esi+0Ch], 1h
		je L10_66CA4B
		__emit 0E8h
		__emit 043h
		__emit 083h
		__emit 09Bh
		__emit 0FFh   // call 0x24D6B
		mov dword ptr [esi+0Ch], 1h
		lea eax,  [esi+edi*8+30h]
		mov ecx, 8h
L11_66CA38:
		mov byte ptr [eax], 0h
		add eax, 40h
		dec ecx
		jne L11_66CA38
		mov dword ptr [esi+25Ch], 0h
L10_66CA4B:
		cmp dword ptr [esi+8h], 0FFFFFFFFh
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		je L12_66CA62
		mov ecx, dword ptr [eax+3Ch]
		cmp dword ptr [esi+4h], ecx
		je L13_66CB1D
L12_66CA62:
		mov eax, dword ptr [eax+3Ch]
		__emit 08Bh
		__emit 02Dh
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h   // mov ebp, dword ptr [0x1359544]
		mov dword ptr [esi+4h], eax
		call ebp
		mov dword ptr [esi+8h], eax
		jmp L14_66CB23
L09_66CA78:
		jle L15_66CA06
		mov byte ptr [esi+270h], 1h
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		test eax, eax
		je L16_66CA94
		mov ecx, dword ptr [eax+118h]
		test ecx, ecx
		jne L17_66CB10
L16_66CA94:
		cmp dword ptr [esi+0Ch], 1h
		jne L17_66CB10
		cmp word ptr [esi+ebp*2+272h], 5h
		jb L18_66CAAF
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
		test ecx, ecx
		jne L19_66CB0B
L18_66CAAF:
		mov ecx, ebx
		__emit 0E8h
		__emit 0A7h
		__emit 06Ah
		__emit 099h
		__emit 0FFh   // call 0x355D
		cmp eax, 2h
		jl L20_66CB01
		__emit 08Bh
		__emit 00Dh
		__emit 09Ch
		__emit 007h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f079c]
		test ecx, ecx
		je L21_66CAEC
		mov edx, dword ptr [ecx]
		call dword ptr [edx+38h]
		test al, al
		jne L20_66CB01
		__emit 08Bh
		__emit 00Dh
		__emit 09Ch
		__emit 007h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f079c]
		mov eax, dword ptr [ecx]
		call dword ptr [eax+34h]
		test al, al
		jne L20_66CB01
		__emit 08Bh
		__emit 00Dh
		__emit 09Ch
		__emit 007h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f079c]
		mov edx, dword ptr [ecx]
		call dword ptr [edx+40h]
		test al, al
		jne L20_66CB01
L21_66CAEC:
		push ebx
		mov ecx, esi
		__emit 0E8h
		__emit 00Ch
		__emit 07Eh
		__emit 09Ch
		__emit 0FFh   // call 0x34900
		push ebx
		mov ecx, esi
		__emit 0E8h
		__emit 01Ch
		__emit 0CDh
		__emit 099h
		__emit 0FFh   // call 0x9818
		jmp L10_66CA4B
L20_66CB01:
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
		test ecx, ecx
		je L17_66CB10
L19_66CB0B:
		mov eax, dword ptr [ecx]
		call dword ptr [eax+78h]
L17_66CB10:
		push ebx
		mov ecx, esi
		__emit 0E8h
		__emit 000h
		__emit 0CDh
		__emit 099h
		__emit 0FFh   // call 0x9818
		jmp L10_66CA4B
L13_66CB1D:
		__emit 08Bh
		__emit 02Dh
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h   // mov ebp, dword ptr [0x1359544]
L14_66CB23:
		cmp dword ptr [esi+0Ch], 1h
		je L22_66CB31
		push ebx
		mov ecx, esi
		__emit 0E8h
		__emit 0E4h
		__emit 0AAh
		__emit 09Bh
		__emit 0FFh   // call 0x27615
L22_66CB31:
		mov al, byte ptr [esp+13h]
		test al, al
		mov ebx, 7D0h
		je L23_66CC5E
		__emit 0A1h
		__emit 0F4h
		__emit 076h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f76f4]
		test eax, eax
		je L24_66CD1D
		call ebp
		sub eax, dword ptr [esi+268h]
		cmp eax, 0BB8h
		jbe L25_66CC72
		mov eax, dword ptr [esp+14h]
		test eax, eax
		je L26_66CB7D
		call ebp
		sub eax, dword ptr [esi+25Ch]
		cmp eax, 1388h
		jae L25_66CC72
L26_66CB7D:
		lea ecx,  [esp+1Ch]
		__emit 0E8h
		__emit 004h
		__emit 039h
		__emit 09Dh
		__emit 0FFh   // call 0x4048A
		__emit 08Bh
		__emit 00Dh
		__emit 0E4h
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f70e4]
		mov edx, dword ptr [ecx]
		lea eax,  [esp+54h]
		push eax
		mov dword ptr [esp+50h], 0h
		call dword ptr [edx+4h]
		mov ecx, dword ptr [eax]
		mov eax, dword ptr [ecx]
		mov eax, dword ptr [eax+8h]
		test eax, eax
		mov byte ptr [esp+4Ch], 1h
		lea ecx,  [eax+8h]
		jne L27_66CBB6
		mov ecx, 107388Bh
L27_66CBB6:
		mov eax, ecx
		lea edi,  [eax+1h]
		jmp L28_66CBC0
		__emit 08Dh
		__emit 049h
		__emit 000h   // lea ecx, [ecx]
L28_66CBC0:
		mov dl, byte ptr [eax]
		inc eax
		test dl, dl
		jne L28_66CBC0
		sub eax, edi
		add eax, ecx
		push eax
		push ecx
		lea ecx,  [esp+24h]
		__emit 0E8h
		__emit 0C1h
		__emit 0E6h
		__emit 09Bh
		__emit 0FFh   // call 0x2B297
		lea ecx,  [esp+54h]
		mov byte ptr [esp+4Ch], 0h
		__emit 0E8h
		__emit 027h
		__emit 0C4h
		__emit 09Ah
		__emit 0FFh   // call 0x1900B
		mov eax, dword ptr [esp+54h]
		test eax, eax
		je L29_66CBF7
		push 0Ch
		push eax
		__emit 0E8h
		__emit 0FCh
		__emit 019h
		__emit 01Ch
		__emit 000h   // call 0x82E5F0
		add esp, 8h
L29_66CBF7:
		mov ecx, dword ptr [esi+260h]
		mov eax, 5h
		add ecx, eax
		mov dword ptr [esp+28h], eax
		mov dword ptr [esi+260h], ecx
		__emit 08Bh
		__emit 00Dh
		__emit 0F4h
		__emit 076h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f76f4]
		lea eax,  [esp+1Ch]
		mov dword ptr [esp+2Ch], ebx
		mov edx, dword ptr [ecx]
		push eax
		call dword ptr [edx+10h]
		call ebp
		mov ecx, dword ptr [esp+1Ch]
		mov dword ptr [esi+268h], eax
		mov eax, dword ptr [esp+24h]
		sub eax, ecx
		test ecx, ecx
		mov dword ptr [esp+4Ch], 0FFFFFFFFh
		je L25_66CC72
		cmp eax, 80h
		jbe L30_66CC52
		push ecx
		__emit 0E8h
		__emit 063h
		__emit 052h
		__emit 021h
		__emit 000h   // call 0x881EB0
		add esp, 4h
		jmp L25_66CC72
L30_66CC52:
		push eax
		push ecx
		__emit 0E8h
		__emit 097h
		__emit 019h
		__emit 01Ch
		__emit 000h   // call 0x82E5F0
		add esp, 8h
		jmp L25_66CC72
L23_66CC5E:
		xor eax, eax
		mov dword ptr [esi+260h], eax
		mov dword ptr [esi+264h], eax
		mov dword ptr [esi+268h], eax
L25_66CC72:
		__emit 0A1h
		__emit 0F4h
		__emit 076h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f76f4]
		test eax, eax
		je L24_66CD1D
		lea ecx,  [esp+30h]
		__emit 0E8h
		__emit 002h
		__emit 038h
		__emit 09Dh
		__emit 0FFh   // call 0x4048A
		__emit 08Bh
		__emit 00Dh
		__emit 0F4h
		__emit 076h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f76f4]
		mov edx, dword ptr [ecx]
		lea eax,  [esp+30h]
		push eax
		mov dword ptr [esp+50h], 2h
		call dword ptr [edx+1Ch]
		test al, al
		je L31_66CCD8
L33_66CCA4:
		mov al, byte ptr [esp+13h]
		test al, al
		je L32_66CCC4
		cmp dword ptr [esp+3Ch], ebx
		jge L32_66CCC4
		mov eax, dword ptr [esi+264h]
		mov ecx, dword ptr [esp+40h]
		add eax, ecx
		mov dword ptr [esi+264h], eax
L32_66CCC4:
		__emit 08Bh
		__emit 00Dh
		__emit 0F4h
		__emit 076h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f76f4]
		mov edx, dword ptr [ecx]
		lea eax,  [esp+30h]
		push eax
		call dword ptr [edx+1Ch]
		test al, al
		jne L33_66CCA4
L31_66CCD8:
		mov ecx, dword ptr [esp+30h]
		mov eax, dword ptr [esp+38h]
		sub eax, ecx
		test ecx, ecx
		mov dword ptr [esp+4Ch], 0FFFFFFFFh
		je L24_66CD1D
		cmp eax, 80h
		jbe L34_66CD13
		push ecx
		__emit 0E8h
		__emit 0B5h
		__emit 051h
		__emit 021h
		__emit 000h   // call 0x881EB0
		add esp, 4h
		pop edi
		pop esi
		pop ebp
		pop ebx
		mov ecx, dword ptr [esp+34h]
		mov dword ptr fs:[0h], ecx
		add esp, 40h
		ret 4h
L34_66CD13:
		push eax
		push ecx
		__emit 0E8h
		__emit 0D6h
		__emit 018h
		__emit 01Ch
		__emit 000h   // call 0x82E5F0
		add esp, 8h
L24_66CD1D:
		mov ecx, dword ptr [esp+44h]
		pop edi
		pop esi
		pop ebp
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 40h
		ret 4h
	}
}
