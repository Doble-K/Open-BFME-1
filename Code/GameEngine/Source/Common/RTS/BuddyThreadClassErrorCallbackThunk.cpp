// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class GPConnection;
struct GPErrorArg;

class BuddyThreadClass
{
public:
    void errorCallback(GPConnection *, GPErrorArg *);
};

__declspec(naked) void BuddyThreadClass::errorCallback(GPConnection *, GPErrorArg *)
{
    __asm {
        _emit 0E9h
        _emit 029h
        _emit 013h
        _emit 063h
        _emit 000h
    }
}
