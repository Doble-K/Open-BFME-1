// cl: /DNDEBUG /MD /EHsc

enum NameKeyType { };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Module;
class Object;

Module *rva0036BB10FindCastleMemberBehavior( const Object *object );

class Object
{
protected:
	Module *findModule( NameKeyType key ) const;

	friend Module *rva0036BB10FindCastleMemberBehavior( const Object *object );
};

Module *rva0036BB10FindCastleMemberBehavior( const Object *object )
{
	static NameKeyType key =
		TheNameKeyGenerator->nameToKey( "CastleMemberBehavior" );
	return object->findModule( key );
}
