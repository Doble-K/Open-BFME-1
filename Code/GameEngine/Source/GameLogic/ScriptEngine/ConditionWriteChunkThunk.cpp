// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class DataChunkOutput;
class Condition
{
public:
    __declspec(dllexport) static void WriteConditionDataChunk(DataChunkOutput &, Condition *);
};

class ConditionWriteChunkShim
{
public:
    static void write(DataChunkOutput &out, Condition *cond);
};

void Condition::WriteConditionDataChunk(DataChunkOutput &out, Condition *cond)
{
    ConditionWriteChunkShim::write(out, cond);
}
