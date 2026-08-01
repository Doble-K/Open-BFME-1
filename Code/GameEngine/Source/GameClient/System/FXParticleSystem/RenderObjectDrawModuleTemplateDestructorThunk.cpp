// cl: /DNDEBUG /MD /EHsc

namespace FXParticleSystem
{
class RenderObjectDrawModuleTemplate
{
public:
    ~RenderObjectDrawModuleTemplate();
};

__declspec(naked) RenderObjectDrawModuleTemplate::~RenderObjectDrawModuleTemplate()
{
    __asm {
        _emit 06Ah
        _emit 0FFh
        _emit 068h
        _emit 0D8h
        _emit 0AEh
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
        _emit 089h
        _emit 074h
        _emit 024h
        _emit 004h
        _emit 085h
        _emit 0F6h
        _emit 0C7h
        _emit 044h
        _emit 024h
        _emit 010h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 074h
        _emit 005h
        _emit 08Dh
        _emit 04Eh
        _emit 008h
        _emit 0EBh
        _emit 002h
        _emit 033h
        _emit 0C9h
        _emit 0E8h
        _emit 03Eh
        _emit 044h
        _emit 0A4h
        _emit 0FFh
        _emit 085h
        _emit 0F6h
        _emit 074h
        _emit 009h
        _emit 0C7h
        _emit 046h
        _emit 004h
        _emit 07Ch
        _emit 0F9h
        _emit 010h
        _emit 001h
        _emit 0EBh
        _emit 008h
        _emit 033h
        _emit 0C0h
        _emit 0C7h
        _emit 000h
        _emit 07Ch
        _emit 0F9h
        _emit 010h
        _emit 001h
        _emit 08Bh
        _emit 04Ch
        _emit 024h
        _emit 008h
        _emit 0C7h
        _emit 006h
        _emit 058h
        _emit 037h
        _emit 007h
        _emit 001h
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
        _emit 0C3h
    }
}
}
