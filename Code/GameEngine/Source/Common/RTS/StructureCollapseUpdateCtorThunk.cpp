// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Thing;
class ModuleData;

class StructureCollapseUpdate
{
public:
    StructureCollapseUpdate(Thing *, const ModuleData *);
};

__declspec(naked) StructureCollapseUpdate::StructureCollapseUpdate(Thing *, const ModuleData *)
{
    __asm {
        _emit 0E9h
        _emit 0B6h
        _emit 03Eh
        _emit 026h
        _emit 000h
    }
}
