// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class Transport
{
public:
    bool doSend();
};

class TransportDoSendShim
{
public:
    bool send();
};

bool Transport::doSend()
{
    return ((TransportDoSendShim *)this)->send();
}
