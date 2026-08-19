// cl: /DNDEBUG /MD /EHsc

// INI::parseObjectCreationList, retail 0x000B8F10. A field parser: read the next
// token, look it up in the store at 0x012EF70C, and write the result through the
// store pointer. Nothing is checked - a missing list is stored as null.
//
// The name was on 0x0007C370, fourteen bytes aliased to
// GameLODManager::getStaticGameLODLevelName. A field parser that calls
// getNextToken and a store lookup is not fourteen bytes.

class ObjectCreationList;

class INI
{
public:
	const char *getNextToken( const char *seps = 0 );

	static void parseObjectCreationList( INI *ini, void *instance, void *store, const void *userData );
};

class ObjectCreationListStore
{
public:
	const ObjectCreationList *findObjectCreationList( const char *name ) const;
};

extern ObjectCreationListStore *TheObjectCreationListStore;		// 0x012EF70C

// ?parseObjectCreationList@INI@@SAXPAV1@PAX1PBX@Z
/*static*/ void INI::parseObjectCreationList( INI *ini, void * /*instance*/, void *store, const void * /*userData*/ )
{
	*(const ObjectCreationList **)store = TheObjectCreationListStore->findObjectCreationList( ini->getNextToken() );
}
