// cl: /DNDEBUG /MD /EHsc

namespace FXParticleSystem
{
class TerrainCollisionModuleInfo
{
public:
    TerrainCollisionModuleInfo(const TerrainCollisionModuleInfo &);
};

__declspec(naked) TerrainCollisionModuleInfo::TerrainCollisionModuleInfo(const TerrainCollisionModuleInfo &)
{
    __asm {
        _emit 06Ah
        _emit 0FFh
        _emit 068h
        _emit 038h
        _emit 0AFh
        _emit 003h
        _emit 001h
        _emit 064h
        _emit 0A1h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 050h
        _emit 064h
        _emit 089h
        _emit 025h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 051h
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 057h
        _emit 089h
        _emit 074h
        _emit 024h
        _emit 008h
        _emit 08Bh
        _emit 07Ch
        _emit 024h
        _emit 01Ch
        _emit 08Dh
        _emit 047h
        _emit 004h
        _emit 050h
        _emit 08Dh
        _emit 04Eh
        _emit 004h
        _emit 0C7h
        _emit 044h
        _emit 024h
        _emit 018h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 0C7h
        _emit 006h
        _emit 0F8h
        _emit 012h
        _emit 011h
        _emit 001h
        _emit 0E8h
        _emit 074h
        _emit 094h
        _emit 02Ah
        _emit 000h
        _emit 08Dh
        _emit 04Fh
        _emit 008h
        _emit 08Bh
        _emit 001h
        _emit 08Dh
        _emit 056h
        _emit 008h
        _emit 089h
        _emit 002h
        _emit 08Bh
        _emit 041h
        _emit 004h
        _emit 089h
        _emit 042h
        _emit 004h
        _emit 08Bh
        _emit 049h
        _emit 008h
        _emit 089h
        _emit 04Ah
        _emit 008h
        _emit 08Ah
        _emit 057h
        _emit 014h
        _emit 08Bh
        _emit 04Ch
        _emit 024h
        _emit 00Ch
        _emit 088h
        _emit 056h
        _emit 014h
        _emit 08Bh
        _emit 047h
        _emit 018h
        _emit 089h
        _emit 046h
        _emit 018h
        _emit 05Fh
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 064h
        _emit 089h
        _emit 00Dh
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 083h
        _emit 0C4h
        _emit 010h
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}
}
