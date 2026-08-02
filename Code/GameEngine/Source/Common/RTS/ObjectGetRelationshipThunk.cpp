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

class ObjectGetRelationshipShim
{
public:
    Relationship get(const Object *other) const;
};

Relationship Object::getRelationship(const Object *other) const
{
    return ((const ObjectGetRelationshipShim *)this)->get(other);
}
