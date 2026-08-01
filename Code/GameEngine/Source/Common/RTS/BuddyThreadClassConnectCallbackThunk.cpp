// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class GPConnection;
struct GPConnectResponseArg;

class BuddyThreadClass
{
public:
    void connectCallback(GPConnection *, GPConnectResponseArg *);
};

__declspec(naked) void BuddyThreadClass::connectCallback(GPConnection *, GPConnectResponseArg *)
{
    __asm {
        _emit 0E9h
        _emit 0DEh
        _emit 0CFh
        _emit 060h
        _emit 000h
    }
}
