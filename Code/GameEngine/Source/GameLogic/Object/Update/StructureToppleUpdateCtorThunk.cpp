// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Thing;
class ModuleData;

class StructureToppleUpdate
{
public:
    StructureToppleUpdate(Thing *, const ModuleData *);
};

__declspec(naked) StructureToppleUpdate::StructureToppleUpdate(Thing *, const ModuleData *)
{
    __asm {
        _emit 0E9h
        _emit 0CAh
        _emit 0AAh
        _emit 027h
        _emit 000h
    }
}
