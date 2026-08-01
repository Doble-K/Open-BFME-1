// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Thing;
class ModuleData;

class StatusBitsUpgrade
{
public:
    StatusBitsUpgrade(Thing *, const ModuleData *);
};

__declspec(naked) StatusBitsUpgrade::StatusBitsUpgrade(Thing *, const ModuleData *)
{
    __asm {
        _emit 0E9h
        _emit 00Fh
        _emit 09Eh
        _emit 02Ch
        _emit 000h
    }
}
