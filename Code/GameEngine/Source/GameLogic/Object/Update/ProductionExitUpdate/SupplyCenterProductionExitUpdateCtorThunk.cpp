// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Thing;
class ModuleData;

class SupplyCenterProductionExitUpdate
{
public:
    SupplyCenterProductionExitUpdate(Thing *, const ModuleData *);
};

__declspec(naked) SupplyCenterProductionExitUpdate::SupplyCenterProductionExitUpdate(Thing *, const ModuleData *)
{
    __asm {
        _emit 0E9h
        _emit 0E5h
        _emit 0A7h
        _emit 02Ah
        _emit 000h
    }
}
