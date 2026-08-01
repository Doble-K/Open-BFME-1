// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

enum Relationship
{
    Relationship_Thunk
};

class Object
{
public:
    Relationship getRelationship(const Object *) const;
};

__declspec(naked) Relationship Object::getRelationship(const Object *) const
{
    __asm {
        _emit 0E9h
        _emit 032h
        _emit 0D2h
        _emit 017h
        _emit 000h
    }
}
