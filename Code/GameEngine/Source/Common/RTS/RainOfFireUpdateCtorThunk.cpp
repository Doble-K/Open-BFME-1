// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Thing;
class ModuleData;

class RainOfFireUpdate
{
public:
    RainOfFireUpdate(Thing *, const ModuleData *);
};

__declspec(naked) RainOfFireUpdate::RainOfFireUpdate(Thing *, const ModuleData *)
{
    __asm {
        _emit 0E9h
        _emit 039h
        _emit 068h
        _emit 029h
        _emit 000h
    }
}
