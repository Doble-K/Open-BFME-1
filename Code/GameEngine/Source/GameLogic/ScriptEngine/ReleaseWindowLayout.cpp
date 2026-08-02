// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class WindowLayout;

void ReleaseWindowLayout(WindowLayout *);

class ReleaseWindowLayoutShim
{
public:
    static void run(WindowLayout *layout);
};

void ReleaseWindowLayout(WindowLayout *layout)
{
    ReleaseWindowLayoutShim::run(layout);
}
