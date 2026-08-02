// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class DataChunkOutput
{
public:
    void openDataChunk(char *, unsigned short);
};

class DataChunkOutputOpenDataChunkShim
{
public:
    void open(char *name, unsigned short id);
};

void DataChunkOutput::openDataChunk(char *name, unsigned short id)
{
    ((DataChunkOutputOpenDataChunkShim *)this)->open(name, id);
}
