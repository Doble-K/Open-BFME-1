// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Thing;
class ModuleData;

class SupplyWarehouseDockUpdate
{
public:
    SupplyWarehouseDockUpdate(Thing *, const ModuleData *);
};

__declspec(naked) SupplyWarehouseDockUpdate::SupplyWarehouseDockUpdate(Thing *, const ModuleData *)
{
    __asm {
        _emit 0E9h
        _emit 0F9h
        _emit 00Eh
        _emit 02Bh
        _emit 000h
    }
}
