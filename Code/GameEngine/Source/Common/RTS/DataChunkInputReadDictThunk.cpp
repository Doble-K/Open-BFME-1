// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class Dict
{
};

class DataChunkInput
{
public:
    Dict readDict();
};

__declspec(naked) Dict DataChunkInput::readDict()
{
    __asm {
        _emit 0E9h
        _emit 038h
        _emit 013h
        _emit 00Eh
        _emit 000h
    }
}
