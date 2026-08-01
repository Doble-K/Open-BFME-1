// cl: /DNDEBUG /MD /EHsc

class AsciiString
{
};

class InGameUI
{
public:
    virtual void message(AsciiString, ...);
};

__declspec(naked) void InGameUI::message(AsciiString, ...)
{
    __asm {
        _emit 08Dh
        _emit 04Ch
        _emit 024h
        _emit 008h
        _emit 0E9h
        _emit 067h
        _emit 09Ah
        _emit 044h
        _emit 000h
    }
}
