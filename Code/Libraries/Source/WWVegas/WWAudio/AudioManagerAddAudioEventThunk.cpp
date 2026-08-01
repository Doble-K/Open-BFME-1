// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

#include "PreRTS.h"

class AudioEventRTS;

class AudioManager
{
public:
    virtual unsigned int addAudioEvent(const AudioEventRTS *);
};

__declspec(naked) unsigned int AudioManager::addAudioEvent(const AudioEventRTS *)
{
    __asm {
        _emit 08Bh
        _emit 044h
        _emit 024h
        _emit 004h
        _emit 06Ah
        _emit 001h
        _emit 06Ah
        _emit 001h
        _emit 06Ah
        _emit 000h
        _emit 050h
        _emit 0E8h
        _emit 0B8h
        _emit 070h
        _emit 096h
        _emit 0FFh
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}
