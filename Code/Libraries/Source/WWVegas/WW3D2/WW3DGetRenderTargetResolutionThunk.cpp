// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class WW3D
{
public:
    __declspec(dllexport) static void Get_Render_Target_Resolution(int &, int &, int &, bool &);
};

__declspec(naked) void WW3D::Get_Render_Target_Resolution(int &, int &, int &, bool &)
    {
        __asm {
            _emit 0E9h
            _emit 09Bh
            _emit 097h
            _emit 000h
            _emit 000h
        }
}
