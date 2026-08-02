// cl: /DNDEBUG /MD /EHsc

namespace FXParticleSystem
{
class RenderObjectDrawModuleInfo
{
public:
    RenderObjectDrawModuleInfo();
};

__declspec(naked) RenderObjectDrawModuleInfo::RenderObjectDrawModuleInfo()
{
    __asm {
        __emit 0x8b;
        __emit 0xc1;
        __emit 0x33;
        __emit 0xc9;
        __emit 0xc7;
        __emit 0x00;
        __emit 0xb8;
        __emit 0x12;
        __emit 0x11;
        __emit 0x01;
        __emit 0x89;
        __emit 0x48;
        __emit 0x10;
        __emit 0x89;
        __emit 0x48;
        __emit 0x20;
        __emit 0x89;
        __emit 0x48;
        __emit 0x30;
        __emit 0xba;
        __emit 0x08;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x88;
        __emit 0x48;
        __emit 0x0c;
        __emit 0x89;
        __emit 0x48;
        __emit 0x14;
        __emit 0x89;
        __emit 0x48;
        __emit 0x18;
        __emit 0x89;
        __emit 0x50;
        __emit 0x1c;
        __emit 0x89;
        __emit 0x48;
        __emit 0x24;
        __emit 0x89;
        __emit 0x48;
        __emit 0x28;
        __emit 0x89;
        __emit 0x50;
        __emit 0x2c;
        __emit 0x89;
        __emit 0x48;
        __emit 0x34;
        __emit 0x89;
        __emit 0x48;
        __emit 0x38;
        __emit 0x89;
        __emit 0x50;
        __emit 0x3c;
        __emit 0x88;
        __emit 0x48;
        __emit 0x04;
        __emit 0x89;
        __emit 0x48;
        __emit 0x08;
        __emit 0xc3;
    }
}
}
