// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class OptionPreferences
{
public:
    OptionPreferences();
};

__declspec(naked) OptionPreferences::OptionPreferences()
{
    __asm {
        _emit 0E9h
        _emit 09Fh
        _emit 093h
        _emit 005h
        _emit 000h
    }
}
