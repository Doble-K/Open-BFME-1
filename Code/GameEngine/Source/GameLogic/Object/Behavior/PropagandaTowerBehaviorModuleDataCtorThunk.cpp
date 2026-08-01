// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class PropagandaTowerBehaviorModuleData
{
public:
    PropagandaTowerBehaviorModuleData();
};

__declspec(naked) PropagandaTowerBehaviorModuleData::PropagandaTowerBehaviorModuleData()
{
    __asm {
        _emit 0E9h
        _emit 02Fh
        _emit 0D1h
        _emit 027h
        _emit 000h
    }
}
