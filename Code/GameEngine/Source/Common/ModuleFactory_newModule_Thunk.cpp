// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class Module;
class Thing;
class AsciiString
{
public:
	unsigned char pad[16];
};
class ModuleData;
enum ModuleType { MODULE_TYPE_PLACEHOLDER = 0 };
class ModuleFactory
{
public:
	Module * newModule(Thing *, const AsciiString &, const ModuleData *, ModuleType);
};

// ?newModule@ModuleFactory@@QAEPAVModule@@PAVThing@@ABVAsciiString@@PBVModuleData@@W4ModuleType@@@Z
__declspec(naked) Module * ModuleFactory::newModule(Thing *, const AsciiString &, const ModuleData *, ModuleType)
{
	__asm {
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x8b
        __emit 0x01
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x4d
        __emit 0x66
        __emit 0x83
        __emit 0x78
        __emit 0x04
        __emit 0x00
        __emit 0x74
        __emit 0x46
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x50
        __emit 0x51
        __emit 0xe8
        __emit 0x1a
        __emit 0x36
        __emit 0xf2
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x18
        __emit 0x83
        __emit 0xc6
        __emit 0x0c
        __emit 0x52
        __emit 0x8b
        __emit 0xce
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0xe8
        __emit 0x1a
        __emit 0x42
        __emit 0xee
        __emit 0xff
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x3b
        __emit 0x06
        __emit 0x74
        __emit 0x18
        __emit 0x83
        __emit 0xc0
        __emit 0x14
        __emit 0x74
        __emit 0x13
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x10
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x08
        __emit 0x51
        __emit 0x52
        __emit 0xff
        __emit 0x10
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x5e
        __emit 0xc2
        __emit 0x10
        __emit 0x00
        __emit 0x33
        __emit 0xc0
        __emit 0x5e
        __emit 0xc2
        __emit 0x10
        __emit 0x00
	}
}
