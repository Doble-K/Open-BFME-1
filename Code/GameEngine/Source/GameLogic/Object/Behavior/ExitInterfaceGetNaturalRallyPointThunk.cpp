// cl: /DNDEBUG /MD /EHsc

struct Coord3D;

class ExitInterface
{
public:
    virtual bool getNaturalRallyPoint(Coord3D &, bool) const;
};

// ?getNaturalRallyPoint@ExitInterface@@UBE_NAAUCoord3D@@_N@Z
__declspec(naked) bool ExitInterface::getNaturalRallyPoint(Coord3D &, bool) const
{
    __asm {
        __emit 0x8b;
        __emit 0x44;
        __emit 0x24;
        __emit 0x04;
        __emit 0x33;
        __emit 0xc9;
        __emit 0x89;
        __emit 0x48;
        __emit 0x08;
        __emit 0x89;
        __emit 0x48;
        __emit 0x04;
        __emit 0x89;
        __emit 0x08;
        __emit 0x32;
        __emit 0xc0;
        __emit 0xc2;
        __emit 0x08;
        __emit 0x00;
    }
}
