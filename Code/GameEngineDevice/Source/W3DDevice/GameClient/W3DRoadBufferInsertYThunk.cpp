// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class Vector2
{
};

class W3DRoadBuffer
{
protected:
    bool insertY(Vector2 loc, int index1, float scale);
};

__declspec(naked) bool W3DRoadBuffer::insertY(Vector2, int, float)
{
    __asm {
        _emit 0E9h
        _emit 054h
        _emit 0FAh
        _emit 06Eh
        _emit 000h
    }
}
