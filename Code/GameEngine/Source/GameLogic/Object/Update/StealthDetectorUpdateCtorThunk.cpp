// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Thing;
class ModuleData;

class StealthDetectorUpdate
{
public:
    StealthDetectorUpdate(Thing *, const ModuleData *);
};

__declspec(naked) StealthDetectorUpdate::StealthDetectorUpdate(Thing *, const ModuleData *)
{
    __asm {
        _emit 0E9h
        _emit 08Fh
        _emit 04Ah
        _emit 027h
        _emit 000h
    }
}
