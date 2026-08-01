// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Thing;
class ModuleData;

class PropagandaTowerBehavior
{
public:
    PropagandaTowerBehavior(Thing *, const ModuleData *);
};

__declspec(naked) PropagandaTowerBehavior::PropagandaTowerBehavior(Thing *, const ModuleData *)
{
    __asm {
        _emit 0E9h
        _emit 0DFh
        _emit 03Fh
        _emit 01Fh
        _emit 000h
    }
}
