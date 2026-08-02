// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class Vector2
{
};

class W3DRoadBuffer
{
protected:
    void insertTee(Vector2, int, float);
};

class W3DRoadBufferInsertTeeShim
{
public:
    void insert(Vector2 loc, int roadType, float width);
};

void W3DRoadBuffer::insertTee(Vector2 loc, int roadType, float width)
{
    ((W3DRoadBufferInsertTeeShim *)this)->insert(loc, roadType, width);
}
