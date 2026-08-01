// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class AsciiString
{
};

class MapCache
{
public:
    AsciiString getUserMapDir() const;
};

__declspec(naked) AsciiString MapCache::getUserMapDir() const
{
    __asm {
        _emit 0E9h
        _emit 072h
        _emit 0DAh
        _emit 043h
        _emit 000h
    }
}
