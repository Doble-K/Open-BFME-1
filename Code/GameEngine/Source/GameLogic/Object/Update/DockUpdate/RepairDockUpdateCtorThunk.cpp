// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Thing;
class ModuleData;

class RepairDockUpdate
{
public:
    RepairDockUpdate(Thing *, const ModuleData *);
};

__declspec(naked) RepairDockUpdate::RepairDockUpdate(Thing *, const ModuleData *)
{
    __asm {
        _emit 0E9h
        _emit 04Bh
        _emit 004h
        _emit 02Bh
        _emit 000h
    }
}
