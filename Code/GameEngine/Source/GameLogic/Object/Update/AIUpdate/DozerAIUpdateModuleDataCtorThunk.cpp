// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class DozerAIUpdateModuleData
{
public:
    DozerAIUpdateModuleData();
};

__declspec(naked) DozerAIUpdateModuleData::DozerAIUpdateModuleData()
{
    __asm {
        _emit 0E9h
        _emit 0D3h
        _emit 06Eh
        _emit 00Fh
        _emit 000h
    }
}
