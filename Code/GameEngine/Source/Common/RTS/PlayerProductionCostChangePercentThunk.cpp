// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class AsciiString
{
};

class Player
{
public:
    float getProductionCostChangePercent(AsciiString buildTemplateName) const;
};

// ?getProductionCostChangePercent@Player@@QBEMVAsciiString@@@Z
__declspec(naked) float Player::getProductionCostChangePercent(AsciiString buildTemplateName) const
{
    __asm {
        __emit 0x51
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x00
        __emit 0x85
        __emit 0xc0
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x74
        __emit 0x05
        __emit 0x83
        __emit 0xc0
        __emit 0x08
        __emit 0xeb
        __emit 0x05
        __emit 0xb8
        __emit 0x8b
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0x00
        __emit 0xd6
        __emit 0x2e
        __emit 0x01
        __emit 0x50
        __emit 0xe8
        __emit 0xc3
        __emit 0x65
        __emit 0xf6
        __emit 0xff
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x08
        __emit 0x81
        __emit 0xc6
        __emit 0xcc
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x52
        __emit 0x8b
        __emit 0xce
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0xe8
        __emit 0x51
        __emit 0x91
        __emit 0xf4
        __emit 0xff
        __emit 0x8b
        __emit 0x0e
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x3b
        __emit 0xc1
        __emit 0x5e
        __emit 0x74
        __emit 0x07
        __emit 0xd9
        __emit 0x40
        __emit 0x14
        __emit 0x59
        __emit 0xc2
        __emit 0x04
        __emit 0x00
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x59
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}
