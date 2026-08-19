// cl: /DNDEBUG /MD /EHsc

// StateMachine::getGoalObject, retail 0x000A1490. Sixteen bytes: read the goal
// id at +0x20 and hand it to TheGameLogic's lookup, as a tail call - the id is
// pushed before the global is even loaded, and nothing is done with the result.

typedef int ObjectID;

class Object;

class GameLogic
{
public:
	Object *findObjectByID( ObjectID id );
};

extern GameLogic *TheGameLogic;				// 0x012F0898

class StateMachine
{
public:
	Object *getGoalObject( void );

private:
	unsigned char m_unmodelled_00[ 0x20 ];
	ObjectID m_goalObjectID;				// +0x20
};

// ?getGoalObject@StateMachine@@QAEPAVObject@@XZ
Object *StateMachine::getGoalObject( void )
{
	return TheGameLogic->findObjectByID( m_goalObjectID );
}
