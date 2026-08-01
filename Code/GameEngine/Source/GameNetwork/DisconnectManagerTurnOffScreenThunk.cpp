// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class DisconnectManager
{
protected:
    void turnOffScreen(int screen);
};

__declspec(naked) void DisconnectManager::turnOffScreen(int)
{
    __asm {
        _emit 0E9h
        _emit 09Bh
        _emit 067h
        _emit 062h
        _emit 000h
    }
}
