// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class WinInstanceData
{
public:
    void init();
};

__declspec(naked) void WinInstanceData::init()
{
    __asm {
        _emit 0E9h
        _emit 084h
        _emit 079h
        _emit 047h
        _emit 000h
    }
}
