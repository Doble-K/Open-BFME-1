// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

struct FieldParse;

class DieMuxData
{
public:
    static const FieldParse *getFieldParse();
};

__declspec(naked) const FieldParse *DieMuxData::getFieldParse()
{
    __asm {
        _emit 0E9h
        _emit 015h
        _emit 0BEh
        _emit 023h
        _emit 000h
    }
}
