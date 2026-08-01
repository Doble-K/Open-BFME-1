// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class QuickMatchPreferences
{
public:
    QuickMatchPreferences();
};

__declspec(naked) QuickMatchPreferences::QuickMatchPreferences()
{
    __asm {
        _emit 0E9h
        _emit 0C9h
        _emit 0CEh
        _emit 007h
        _emit 000h
    }
}
