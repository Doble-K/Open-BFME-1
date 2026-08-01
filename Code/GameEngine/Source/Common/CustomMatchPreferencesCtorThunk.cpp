// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class CustomMatchPreferences
{
public:
    CustomMatchPreferences();
};

__declspec(naked) CustomMatchPreferences::CustomMatchPreferences()
{
    __asm {
        _emit 0E9h
        _emit 0F6h
        _emit 006h
        _emit 00Ah
        _emit 000h
    }
}
