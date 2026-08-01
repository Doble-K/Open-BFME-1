// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class AsciiString;

__declspec(naked) bool operator<(const AsciiString &, const AsciiString &)
{
    __asm {
        _emit 0E9h
        _emit 033h
        _emit 0F9h
        _emit 062h
        _emit 000h
    }
}
