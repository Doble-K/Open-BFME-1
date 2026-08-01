// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
#include "PreRTS.h"

enum ObjectID { OBJECT_ID_INVALID = 0 };

class Player
{
public:
    virtual void repairStructure(ObjectID structureID);
};

__declspec(naked) void Player::repairStructure(ObjectID)
{
    __asm {
        _emit 08Bh
        _emit 081h
        _emit 020h
        _emit 002h
        _emit 000h
        _emit 000h
        _emit 085h
        _emit 0C0h
        _emit 074h
        _emit 007h
        _emit 08Bh
        _emit 0C8h
        _emit 08Bh
        _emit 001h
        _emit 0FFh
        _emit 060h
        _emit 03Ch
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}
