// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class GameWindow;

void GadgetListBoxSetColors(GameWindow *, int, int, int, int, int, int, int, int, int, int, int, int);

class GadgetListBoxSetColorsShim
{
public:
    static void run(GameWindow *w,
        int a, int b, int c, int d, int e, int f,
        int g, int h, int i, int j, int k, int l);
};

void GadgetListBoxSetColors(GameWindow *w,
    int a, int b, int c, int d, int e, int f,
    int g, int h, int i, int j, int k, int l)
{
    GadgetListBoxSetColorsShim::run(w, a, b, c, d, e, f, g, h, i, j, k, l);
}
