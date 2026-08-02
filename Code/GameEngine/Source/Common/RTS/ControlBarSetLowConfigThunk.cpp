// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class ControlBar
{
protected:
    void setLowControlBarConfig();
};

class ControlBarSetLowConfigShim
{
public:
    void apply();
};

void ControlBar::setLowControlBarConfig()
{
    ((ControlBarSetLowConfigShim *)this)->apply();
}
