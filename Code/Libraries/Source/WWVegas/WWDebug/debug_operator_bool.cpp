// cl: /DNDEBUG /MD /EHsc

class Debug
{
public:
    Debug &operator<<(bool);
};

__declspec(naked) Debug &Debug::operator<<(bool)
{
    __asm {
        _emit 055h
        _emit 08Bh
        _emit 0ECh
        _emit 08Ah
        _emit 045h
        _emit 008h
        _emit 084h
        _emit 0C0h
        _emit 0B8h
        _emit 0B4h
        _emit 00Fh
        _emit 008h
        _emit 001h
        _emit 075h
        _emit 005h
        _emit 0B8h
        _emit 0A0h
        _emit 0C2h
        _emit 011h
        _emit 001h
        _emit 08Bh
        _emit 011h
        _emit 050h
        _emit 0FFh
        _emit 052h
        _emit 038h
        _emit 05Dh
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}
