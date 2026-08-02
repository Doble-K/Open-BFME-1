// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class GameSlot;

class NAT
{
protected:
    void sendMangledPortNumberToTarget(unsigned short mangledPort, GameSlot *targetSlot);
};

class NATSendMangledPortShim
{
public:
    void send(unsigned short mangledPort, GameSlot *targetSlot);
};

void NAT::sendMangledPortNumberToTarget(unsigned short mangledPort, GameSlot *targetSlot)
{
    ((NATSendMangledPortShim *)this)->send(mangledPort, targetSlot);
}
