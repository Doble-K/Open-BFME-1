// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

typedef unsigned short UnsignedShort;

class NetFileProgressCommandMsg
{
public:
    void setFileID(UnsignedShort fileID);
};

class NetFileProgressSetFileIDShim
{
public:
    void set(UnsignedShort fileID);
};

void NetFileProgressCommandMsg::setFileID(UnsignedShort fileID)
{
    ((NetFileProgressSetFileIDShim *)this)->set(fileID);
}
