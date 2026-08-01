// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class GPConnection;
struct GPRecvBuddyMessageArg;

class BuddyThreadClass
{
public:
    void messageCallback(GPConnection *, GPRecvBuddyMessageArg *);
};

__declspec(naked) void BuddyThreadClass::messageCallback(GPConnection *, GPRecvBuddyMessageArg *)
{
    __asm {
        _emit 0E9h
        _emit 0D1h
        _emit 0E4h
        _emit 062h
        _emit 000h
    }
}
