// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class DistLODClass
{
private:
    __declspec(dllexport) void Free();
};

__declspec(naked) void DistLODClass::Free()
{
    __asm {
        _emit 0E9h
        _emit 0A8h
        _emit 00Fh
        _emit 071h
        _emit 000h
    }
}
