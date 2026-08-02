// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class GPConnection;
struct GPRecvBuddyStatusArg;

class BuddyThreadClass
{
public:
    void statusCallback(GPConnection *, GPRecvBuddyStatusArg *);
};

class BuddyThreadClassStatusCallbackShim
{
public:
    void run(GPConnection *conn, GPRecvBuddyStatusArg *arg);
};

void BuddyThreadClass::statusCallback(GPConnection *conn, GPRecvBuddyStatusArg *arg)
{
    ((BuddyThreadClassStatusCallbackShim *)this)->run(conn, arg);
}
