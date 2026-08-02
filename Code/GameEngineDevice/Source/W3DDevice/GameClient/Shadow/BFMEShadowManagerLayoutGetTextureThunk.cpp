// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class W3DShadowTexture;

class BFMEShadowManagerLayout
{
public:
    W3DShadowTexture *getTexture(const char *name);
};

class BFMEShadowManagerLayoutGetTextureShim
{
public:
    W3DShadowTexture *getTexture(const char *);
};

W3DShadowTexture *BFMEShadowManagerLayout::getTexture(const char *name)
{
    return ((BFMEShadowManagerLayoutGetTextureShim *)this)->getTexture(name);
}
