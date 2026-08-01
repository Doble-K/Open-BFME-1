// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Thing;
class ModuleData;

class AutoHealBehavior
{
public:
    AutoHealBehavior(Thing *, const ModuleData *);
};

__declspec(naked) AutoHealBehavior::AutoHealBehavior(Thing *, const ModuleData *)
{
    __asm {
        _emit 0E9h
        _emit 0ADh
        _emit 05Dh
        _emit 01Ah
        _emit 000h
    }
}
