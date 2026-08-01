// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class Vector2
{
};

class W3DRoadBuffer
{
protected:
    void insertTee(Vector2, int, float);
};

__declspec(naked) void W3DRoadBuffer::insertTee(Vector2, int, float)
{
    __asm {
        _emit 0E9h
        _emit 0D9h
        _emit 046h
        _emit 070h
        _emit 000h
    }
}
