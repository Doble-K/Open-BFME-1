// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class AsciiString;
class Mapping;

class DataChunkTableOfContents
{
    Mapping *findMapping(const AsciiString &);
};

class DataChunkTableOfContentsFindMappingShim
{
public:
    Mapping *find(const AsciiString &name);
};

Mapping *DataChunkTableOfContents::findMapping(const AsciiString &name)
{
    return ((DataChunkTableOfContentsFindMappingShim *)this)->find(name);
}
