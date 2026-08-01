// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class BattlePlanUpdateModuleData
{
public:
    BattlePlanUpdateModuleData();
};

__declspec(naked) BattlePlanUpdateModuleData::BattlePlanUpdateModuleData()
{
    __asm {
        _emit 0E9h
        _emit 070h
        _emit 04Ch
        _emit 01Dh
        _emit 000h
    }
}
