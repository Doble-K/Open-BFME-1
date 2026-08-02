// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class FellBeastSwoopPower
{
public:
    FellBeastSwoopPower(Thing *, const ModuleData *);
};

__declspec(naked) FellBeastSwoopPower::FellBeastSwoopPower(Thing *, const ModuleData *)
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
    __asm _emit(0x0E);
    __asm _emit(0x65);
    __asm _emit(0xDB);
    __asm _emit(0xFF);
    __asm _emit(0xC7);
    __asm _emit(0x06);
    __asm _emit(0xE8);
    __asm _emit(0x4E);
    __asm _emit(0x0B);
    __asm _emit(0x01);
    __asm _emit(0xC7);
    __asm _emit(0x46);
    __asm _emit(0x0C);
    __asm _emit(0x20);
    __asm _emit(0x4E);
    __asm _emit(0x0B);
    __asm _emit(0x01);
    __asm _emit(0xC7);
    __asm _emit(0x46);
    __asm _emit(0x10);
    __asm _emit(0x10);
    __asm _emit(0x4E);
    __asm _emit(0x0B);
    __asm _emit(0x01);
    __asm _emit(0xC7);
    __asm _emit(0x46);
    __asm _emit(0x20);
    __asm _emit(0xE4);
    __asm _emit(0x4D);
    __asm _emit(0x0B);
    __asm _emit(0x01);
    __asm _emit(0xC6);
    __asm _emit(0x86);
    __asm _emit(0xE8);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x00);
    __asm _emit(0x8B);
    __asm _emit(0xC6);
    __asm _emit(0x5E);
    __asm _emit(0xC2);
    __asm _emit(0x08);
    __asm _emit(0x00);
}
