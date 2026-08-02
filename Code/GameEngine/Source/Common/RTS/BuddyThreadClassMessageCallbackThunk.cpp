// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class GPConnection;
struct GPRecvBuddyMessageArg;

class BuddyThreadClass
{
public:
    void messageCallback(GPConnection *, GPRecvBuddyMessageArg *);
};

class BuddyThreadClassMessageCallbackShim
{
public:
    void run(GPConnection *conn, GPRecvBuddyMessageArg *arg);
};

void BuddyThreadClass::messageCallback(GPConnection *conn, GPRecvBuddyMessageArg *arg)
{
    ((BuddyThreadClassMessageCallbackShim *)this)->run(conn, arg);
}
