// cl: /DNDEBUG /MD /EHsc

class AsciiString
{
};

class MapObject
{
public:
    void setWaypointName(AsciiString);
};

__declspec(naked) void MapObject::setWaypointName(AsciiString)
{
    __asm {
        _emit 08Bh
        _emit 044h
        _emit 024h
        _emit 004h
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 050h
        _emit 0B9h
        _emit 0A8h
        _emit 077h
        _emit 02Ah
        _emit 001h
        _emit 0E8h
        _emit 0A2h
        _emit 014h
        _emit 0F8h
        _emit 0FFh
        _emit 050h
        _emit 08Dh
        _emit 04Eh
        _emit 024h
        _emit 0E8h
        _emit 025h
        _emit 031h
        _emit 0FAh
        _emit 0FFh
        _emit 05Eh
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}
