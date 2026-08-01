// cl: /DNDEBUG /MD /EHsc

class OBBoxIntersectionTestClass
{
};

class MeshGeometryClass
{
public:
    bool Intersect_OBBox(OBBoxIntersectionTestClass &);
};

__declspec(naked) bool MeshGeometryClass::Intersect_OBBox(OBBoxIntersectionTestClass &boxtest)
{
    __asm {
        _emit 08Bh
        _emit 081h
        _emit 090h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 085h
        _emit 0C0h
        _emit 074h
        _emit 013h
        _emit 08Bh
        _emit 04Ch
        _emit 024h
        _emit 004h
        _emit 08Bh
        _emit 050h
        _emit 00Ch
        _emit 051h
        _emit 052h
        _emit 08Bh
        _emit 0C8h
        _emit 0E8h
        _emit 0C6h
        _emit 037h
        _emit 004h
        _emit 000h
        _emit 0C2h
        _emit 004h
        _emit 000h
        _emit 0E9h
        _emit 09Eh
        _emit 0F2h
        _emit 0FFh
        _emit 0FFh
    }
}
