// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class Vector2
{
};

class W3DRoadBuffer
{
protected:
    bool insertY(Vector2 loc, int index1, float scale);
};

class W3DRoadBufferInsertYShim
{
public:
    bool insertY(Vector2, int, float);
};

bool W3DRoadBuffer::insertY(Vector2 loc, int index1, float scale)
{
    return ((W3DRoadBufferInsertYShim *)this)->insertY(loc, index1, scale);
}
