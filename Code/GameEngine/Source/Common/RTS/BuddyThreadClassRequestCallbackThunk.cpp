// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class GPConnection;
struct GPRecvBuddyRequestArg;

class BuddyThreadClass
{
public:
    void requestCallback(GPConnection *, GPRecvBuddyRequestArg *);
};

__declspec(naked) void BuddyThreadClass::requestCallback(GPConnection *, GPRecvBuddyRequestArg *)
{
    __asm {
        _emit 0E9h
        _emit 0BCh
        _emit 0ACh
        _emit 060h
        _emit 000h
    }
}
