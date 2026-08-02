// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

float GetGameLogicRandomValueReal(float, float, char *, int);

class GetGameLogicRandomValueRealShim
{
public:
    static float run(float lo, float hi, char *file, int line);
};

float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line)
{
    return GetGameLogicRandomValueRealShim::run(lo, hi, file, line);
}
