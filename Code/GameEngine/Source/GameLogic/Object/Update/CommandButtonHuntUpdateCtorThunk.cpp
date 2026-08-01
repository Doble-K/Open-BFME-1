// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Thing;
class ModuleData;

class CommandButtonHuntUpdate
{
public:
    CommandButtonHuntUpdate(Thing *, const ModuleData *);
};

__declspec(naked) CommandButtonHuntUpdate::CommandButtonHuntUpdate(Thing *, const ModuleData *)
{
    __asm {
        _emit 0E9h
        _emit 04Dh
        _emit 09Dh
        _emit 026h
        _emit 000h
    }
}
