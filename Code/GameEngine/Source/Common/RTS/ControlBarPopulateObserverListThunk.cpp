// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class ControlBar
{
public:
    void populateObserverList();
};

__declspec(naked) void ControlBar::populateObserverList()
{
    __asm {
        _emit 0E9h
        _emit 02Ah
        _emit 031h
        _emit 047h
        _emit 000h
    }
}
