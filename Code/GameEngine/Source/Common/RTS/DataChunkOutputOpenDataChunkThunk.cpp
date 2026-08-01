// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class DataChunkOutput
{
public:
    void openDataChunk(char *, unsigned short);
};

__declspec(naked) void DataChunkOutput::openDataChunk(char *, unsigned short)
{
    __asm {
        _emit 0E9h
        _emit 095h
        _emit 09Fh
        _emit 00Ch
        _emit 000h
    }
}
