// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class Object;
class UpdateModule;

class GameLogic
{
public:
    void friend_awakenUpdateModule(Object *, UpdateModule *, unsigned int);
};

class GameLogicAwakenUpdateModuleShim
{
public:
    void awaken(Object *obj, UpdateModule *mod, unsigned int sleep);
};

void GameLogic::friend_awakenUpdateModule(Object *obj, UpdateModule *mod, unsigned int sleep)
{
    ((GameLogicAwakenUpdateModuleShim *)this)->awaken(obj, mod, sleep);
}
