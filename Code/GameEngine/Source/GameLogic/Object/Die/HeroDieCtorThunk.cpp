// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class HeroDie
{
public:
    HeroDie(Thing *, const ModuleData *);
};

__declspec(naked) HeroDie::HeroDie(Thing *, const ModuleData *)
{
    __asm _emit(0x8B);
    __asm _emit(0x44);
    __asm _emit(0x24);
    __asm _emit(0x08);
    __asm _emit(0x56);
    __asm _emit(0x8B);
    __asm _emit(0xF1);
    __asm _emit(0x8B);
    __asm _emit(0x4C);
    __asm _emit(0x24);
    __asm _emit(0x08);
    __asm _emit(0x50);
    __asm _emit(0x51);
    __asm _emit(0x8B);
    __asm _emit(0xCE);
    __asm _emit(0xE8);
    __asm _emit(0x60);
    __asm _emit(0x1A);
    __asm _emit(0xDC);
    __asm _emit(0xFF);
    __asm _emit(0xC7);
    __asm _emit(0x46);
    __asm _emit(0x0C);
    __asm _emit(0xD0);
    __asm _emit(0xC9);
    __asm _emit(0x09);
    __asm _emit(0x01);
    __asm _emit(0xC7);
    __asm _emit(0x46);
    __asm _emit(0x10);
    __asm _emit(0x7C);
    __asm _emit(0x25);
    __asm _emit(0x0A);
    __asm _emit(0x01);
    __asm _emit(0xC7);
    __asm _emit(0x06);
    __asm _emit(0x2C);
    __asm _emit(0x31);
    __asm _emit(0x0B);
    __asm _emit(0x01);
    __asm _emit(0xC7);
    __asm _emit(0x46);
    __asm _emit(0x0C);
    __asm _emit(0x68);
    __asm _emit(0x30);
    __asm _emit(0x0B);
    __asm _emit(0x01);
    __asm _emit(0xC7);
    __asm _emit(0x46);
    __asm _emit(0x10);
    __asm _emit(0x64);
    __asm _emit(0x30);
    __asm _emit(0x0B);
    __asm _emit(0x01);
    __asm _emit(0x8B);
    __asm _emit(0xC6);
    __asm _emit(0x5E);
    __asm _emit(0xC2);
    __asm _emit(0x08);
    __asm _emit(0x00);
}
