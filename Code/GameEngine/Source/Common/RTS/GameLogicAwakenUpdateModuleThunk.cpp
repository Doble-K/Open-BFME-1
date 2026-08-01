// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class Object;
class UpdateModule;

class GameLogic
{
public:
    void friend_awakenUpdateModule(Object *, UpdateModule *, unsigned int);
};

__declspec(naked) void GameLogic::friend_awakenUpdateModule(Object *, UpdateModule *, unsigned int)
{
    __asm {
        _emit 0E9h
        _emit 027h
        _emit 03Fh
        _emit 038h
        _emit 000h
    }
}
