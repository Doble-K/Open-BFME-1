// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class AsciiString;

class QuickMatchPreferences
{
public:
    void setLastLadder(const AsciiString &, unsigned short);
};

__declspec(naked) void QuickMatchPreferences::setLastLadder(const AsciiString &, unsigned short)
{
    __asm {
        _emit 0E9h
        _emit 005h
        _emit 036h
        _emit 008h
        _emit 000h
    }
}
