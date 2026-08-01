// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class ScreenCrossFadeFilter
{
protected:
    bool updateFadeLevel();
};

__declspec(naked) bool ScreenCrossFadeFilter::updateFadeLevel()
{
    __asm {
        _emit 0E9h
        _emit 09Fh
        _emit 0C8h
        _emit 07Ch
        _emit 000h
    }
}
