// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
#include "PreRTS.h"

class W3DBufferManager
{
public:
    struct W3DVertexBuffer
    {
    };

    enum VBM_FVF_TYPES
    {
        VBM_FVF_INVALID = 0
    };

    W3DVertexBuffer *getNextVertexBuffer(W3DVertexBuffer *buffer, VBM_FVF_TYPES type);
};

__declspec(naked) W3DBufferManager::W3DVertexBuffer *W3DBufferManager::getNextVertexBuffer(W3DVertexBuffer *, VBM_FVF_TYPES)
{
    __asm {
        _emit 08Bh
        _emit 044h
        _emit 024h
        _emit 004h
        _emit 085h
        _emit 0C0h
        _emit 075h
        _emit 00Eh
        _emit 08Bh
        _emit 044h
        _emit 024h
        _emit 008h
        _emit 08Bh
        _emit 084h
        _emit 081h
        _emit 000h
        _emit 090h
        _emit 000h
        _emit 000h
        _emit 0C2h
        _emit 008h
        _emit 000h
        _emit 08Bh
        _emit 040h
        _emit 010h
        _emit 0C2h
        _emit 008h
        _emit 000h
    }
}
