// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class AsciiString;
class Mapping;

class DataChunkTableOfContents
{
    Mapping *findMapping(const AsciiString &);
};

__declspec(naked) Mapping *DataChunkTableOfContents::findMapping(const AsciiString &)
{
    __asm {
        _emit 0E9h
        _emit 021h
        _emit 0E4h
        _emit 00Eh
        _emit 000h
    }
}
