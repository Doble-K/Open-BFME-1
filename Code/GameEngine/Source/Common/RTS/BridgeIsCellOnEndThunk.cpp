// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

struct Region2D;

class Bridge
{
public:
    bool isCellOnEnd(const Region2D *);
};

__declspec(naked) bool Bridge::isCellOnEnd(const Region2D *)
{
    __asm {
        _emit 0E9h
        _emit 0FEh
        _emit 049h
        _emit 019h
        _emit 000h
    }
}
