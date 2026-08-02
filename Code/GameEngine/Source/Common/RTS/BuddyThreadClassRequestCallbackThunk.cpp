// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class GPConnection;
struct GPRecvBuddyRequestArg;

class BuddyThreadClass
{
public:
    void requestCallback(GPConnection *, GPRecvBuddyRequestArg *);
};

class BuddyThreadClassRequestCallbackShim
{
public:
    void run(GPConnection *conn, GPRecvBuddyRequestArg *arg);
};

void BuddyThreadClass::requestCallback(GPConnection *conn, GPRecvBuddyRequestArg *arg)
{
    ((BuddyThreadClassRequestCallbackShim *)this)->run(conn, arg);
}
