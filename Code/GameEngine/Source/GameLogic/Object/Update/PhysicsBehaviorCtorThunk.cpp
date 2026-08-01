// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Thing;
class ModuleData;

class PhysicsBehavior
{
public:
    PhysicsBehavior(Thing *, const ModuleData *);
};

__declspec(naked) PhysicsBehavior::PhysicsBehavior(Thing *, const ModuleData *)
{
    __asm {
        _emit 0E9h
        _emit 0A5h
        _emit 093h
        _emit 01Ch
        _emit 000h
    }
}
