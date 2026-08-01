class AsciiString
{
};

class GameSpyInfo
{
public:
    virtual void setPingString(const AsciiString &);
};

__declspec(naked) void GameSpyInfo::setPingString(const AsciiString &)
{
    __asm {
        _emit 083h
        _emit 0C1h
        _emit 014h
        _emit 0E9h
        _emit 058h
        _emit 00Ah
        _emit 025h
        _emit 000h
    }
}
