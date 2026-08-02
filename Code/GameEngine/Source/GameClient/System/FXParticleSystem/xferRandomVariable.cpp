// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Xfer;
class GameClientRandomVariable;

void xferRandomVariable(Xfer &, GameClientRandomVariable &);

class XferRandomVariableShim
{
public:
    static void run(Xfer &xfer, GameClientRandomVariable &var);
};

void xferRandomVariable(Xfer &xfer, GameClientRandomVariable &var)
{
    XferRandomVariableShim::run(xfer, var);
}
