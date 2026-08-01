// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class GPConnection;
struct GPRecvBuddyStatusArg;

class BuddyThreadClass
{
public:
    void statusCallback(GPConnection *, GPRecvBuddyStatusArg *);
};

__declspec(naked) void BuddyThreadClass::statusCallback(GPConnection *, GPRecvBuddyStatusArg *)
{
    __asm {
        _emit 0E9h
        _emit 060h
        _emit 0ECh
        _emit 05Fh
        _emit 000h
    }
}
