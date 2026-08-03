// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class __declspec(novtable) MultiplayerSettings
{
public:
    virtual ~MultiplayerSettings();
};

// ??1MultiplayerSettings@@UAE@XZ
__declspec(naked) MultiplayerSettings::~MultiplayerSettings()
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x4e
        __emit 0x59
        __emit 0xff
        __emit 0x00
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x8d
        __emit 0x4e
        __emit 0x64
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x33
        __emit 0x88
        __emit 0x7f
        __emit 0x00
        __emit 0x8d
        __emit 0x4e
        __emit 0x40
        __emit 0xc6
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x01
        __emit 0xe8
        __emit 0x26
        __emit 0x88
        __emit 0x7f
        __emit 0x00
        __emit 0x8d
        __emit 0x4e
        __emit 0x30
        __emit 0xc6
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0xe8
        __emit 0xf4
        __emit 0xae
        __emit 0xfb
        __emit 0xff
        __emit 0x8b
        __emit 0xce
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x0a
        __emit 0x29
        __emit 0x91
        __emit 0x00
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}
