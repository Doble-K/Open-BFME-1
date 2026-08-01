// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class W3DShadowTexture;

class BFMEShadowManagerLayout
{
public:
    W3DShadowTexture *getTexture(const char *name);
};

__declspec(naked) W3DShadowTexture *BFMEShadowManagerLayout::getTexture(const char *)
{
    __asm {
        _emit 0E9h
        _emit 080h
        _emit 0F4h
        _emit 076h
        _emit 000h
    }
}
