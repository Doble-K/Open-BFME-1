// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class GameWindow;

void GadgetListBoxSetColors(GameWindow *, int, int, int, int, int, int, int, int, int, int, int, int);

__declspec(naked) void GadgetListBoxSetColors(GameWindow *, int, int, int, int, int, int, int, int, int, int, int, int)
{
    __asm {
        _emit 0E9h
        _emit 090h
        _emit 05Ch
        _emit 047h
        _emit 000h
    }
}
