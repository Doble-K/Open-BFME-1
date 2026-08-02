// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class NetFileProgressCommandMsg
{
public:
    void setProgress(int percentage);
};

class NetFileProgressSetProgressShim
{
public:
    void set(int percentage);
};

void NetFileProgressCommandMsg::setProgress(int percentage)
{
    ((NetFileProgressSetProgressShim *)this)->set(percentage);
}
