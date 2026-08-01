// cl: /DNDEBUG /MD /EHsc

class Xfer
{
};

class TerrainLogic
{
protected:
    virtual void xfer(Xfer *);
};

__declspec(naked) void TerrainLogic::xfer(Xfer *)
{
    __asm {
        _emit 051h
        _emit 056h
        _emit 08Bh
        _emit 074h
        _emit 024h
        _emit 00Ch
        _emit 057h
        _emit 08Bh
        _emit 0F9h
        _emit 0B0h
        _emit 001h
        _emit 08Dh
        _emit 04Ch
        _emit 024h
        _emit 008h
        _emit 088h
        _emit 044h
        _emit 024h
        _emit 008h
        _emit 088h
        _emit 044h
        _emit 024h
        _emit 009h
        _emit 08Bh
        _emit 006h
        _emit 051h
        _emit 08Bh
        _emit 0CEh
        _emit 0FFh
        _emit 050h
        _emit 028h
        _emit 056h
        _emit 08Bh
        _emit 0CFh
        _emit 0E8h
        _emit 080h
        _emit 05Ah
        _emit 098h
        _emit 0FFh
        _emit 05Fh
        _emit 05Eh
        _emit 059h
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}
