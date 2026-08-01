// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class FlightDeckBehaviorModuleData
{
public:
    FlightDeckBehaviorModuleData();
};

__declspec(naked) FlightDeckBehaviorModuleData::FlightDeckBehaviorModuleData()
{
    __asm {
        _emit 0E9h
        _emit 06Dh
        _emit 065h
        _emit 020h
        _emit 000h
    }
}
