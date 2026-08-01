// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class DataChunkOutput;
class Condition
{
public:
    __declspec(dllexport) static void WriteConditionDataChunk(DataChunkOutput &, Condition *);
};

__declspec(naked) void Condition::WriteConditionDataChunk(DataChunkOutput &, Condition *)
{
    __asm {
        _emit 0E9h
        _emit 01Ah
        _emit 053h
        _emit 031h
        _emit 000h
    }
}
