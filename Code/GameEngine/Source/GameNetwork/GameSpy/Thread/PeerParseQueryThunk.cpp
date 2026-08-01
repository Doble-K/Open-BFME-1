// cl: /DNDEBUG /MD /EHsc

struct sockaddr;

__declspec(naked) int peerParseQuery(void *, char *, int, sockaddr *)
{
    __asm {
        _emit 08Bh
        _emit 04Ch
        _emit 024h
        _emit 004h
        _emit 08Bh
        _emit 081h
        _emit 0F0h
        _emit 00Ah
        _emit 000h
        _emit 000h
        _emit 085h
        _emit 0C0h
        _emit 075h
        _emit 00Ah
        _emit 08Bh
        _emit 081h
        _emit 0F4h
        _emit 01Eh
        _emit 000h
        _emit 000h
        _emit 085h
        _emit 0C0h
        _emit 074h
        _emit 009h
        _emit 089h
        _emit 044h
        _emit 024h
        _emit 004h
        _emit 0E9h
        _emit 0DFh
        _emit 0E9h
        _emit 0FFh
        _emit 0FFh
        _emit 0C3h
    }
}
