// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class WW3D
{
public:
    __declspec(dllexport) static void Get_Render_Target_Resolution(int &, int &, int &, bool &);
};

class WW3DGetRenderTargetResolutionShim
{
public:
    static void get(int &, int &, int &, bool &);
};

void WW3D::Get_Render_Target_Resolution(int &width, int &height, int &depth, bool &windowed)
{
    WW3DGetRenderTargetResolutionShim::get(width, height, depth, windowed);
}
