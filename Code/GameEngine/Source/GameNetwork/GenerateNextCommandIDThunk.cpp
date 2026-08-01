// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

typedef unsigned short UnsignedShort;

UnsignedShort GenerateNextCommandID();

__declspec(naked) UnsignedShort GenerateNextCommandID()
{
    __asm {
        _emit 0E9h
        _emit 0B3h
        _emit 027h
        _emit 065h
        _emit 000h
    }
}
