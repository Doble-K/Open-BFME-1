// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

typedef unsigned short UnsignedShort;

UnsignedShort GenerateNextCommandID();

class GenerateNextCommandIDShim
{
public:
    static UnsignedShort next();
};

UnsignedShort GenerateNextCommandID()
{
    return GenerateNextCommandIDShim::next();
}
