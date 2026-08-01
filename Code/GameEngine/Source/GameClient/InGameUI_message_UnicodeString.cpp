// cl: /DNDEBUG /MD /EHsc

class UnicodeString
{
};

class InGameUI
{
public:
    virtual void message(UnicodeString, ...);
};

__declspec(naked) void InGameUI::message(UnicodeString, ...)
{
    __asm {
        _emit 08Dh
        _emit 04Ch
        _emit 024h
        _emit 008h
        _emit 0E9h
        _emit 0E7h
        _emit 0A2h
        _emit 044h
        _emit 000h
    }
}
