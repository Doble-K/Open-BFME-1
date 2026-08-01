// cl: /DNDEBUG /MD /EHsc

class File
{
};

namespace FXParticleSystem
{
template<int Category>
class DefaultModuleTemplate
{
};

template<>
class DefaultModuleTemplate<6>
{
public:
    virtual void writeINI(File &, unsigned int) const;
};

__declspec(naked) void DefaultModuleTemplate<6>::writeINI(File &, unsigned int) const
{
    __asm {
        _emit 056h
        _emit 08Bh
        _emit 074h
        _emit 024h
        _emit 008h
        _emit 08Dh
        _emit 044h
        _emit 024h
        _emit 00Ch
        _emit 050h
        _emit 056h
        _emit 051h
        _emit 0E8h
        _emit 048h
        _emit 028h
        _emit 0A5h
        _emit 0FFh
        _emit 08Dh
        _emit 04Ch
        _emit 024h
        _emit 018h
        _emit 051h
        _emit 056h
        _emit 0E8h
        _emit 000h
        _emit 029h
        _emit 0A5h
        _emit 0FFh
        _emit 083h
        _emit 0C4h
        _emit 014h
        _emit 05Eh
        _emit 0C2h
        _emit 008h
        _emit 000h
    }
}
}
