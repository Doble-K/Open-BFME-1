// cl: /DNDEBUG /MD /GX /Od

// EA's DirtySock middleware -- see commudp.cpp for why this directory name is an
// inference. Every function name here is retail's own: each body logs it.
// Parameter lists are not recovered yet; these are naked bodies and the
// extern "C" __cdecl name does not encode them.

extern "C" {
	int CommTCPResolve();
	struct CommTCPRef;
	int CommTCPUnlisten(CommTCPRef *ref);
}

struct CommTCPRef
{
	char m_prefix[0x90];
	int m_state;
	int m_listenSocket;
};

int CommTCPUnlisten(CommTCPRef *ref)
{
	if (ref->m_state != 4) {
		return 0;
	}
	ref->m_listenSocket = 0;
	ref->m_state = 5;
	return 0;
}

// Always fails: "Resolve functionality not supported by CommTCP".
__declspec(naked) int CommTCPResolve()
{
	__asm {
		push ebp
		mov ebp, esp
		push 12C4AB0h
		__emit 0E8h
		__emit 0A3h
		__emit 0A3h
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 4h
		or eax, 0FFFFFFFFh
		cmp ebp, esp
		__emit 0E8h
		__emit 018h
		__emit 031h
		__emit 01Eh
		__emit 000h   // call 0x9F7502
		pop ebp
		ret
	}
}
