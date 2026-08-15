// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME5: ScriptActions::doTeamSpinForFramecount, retail 0x002F11E0,
// zh_sweep packet 002f11e0.
//
// The reference body unchanged. One byte separated it from retail:
// ScriptEngine::getTeamNamed is vtable slot 26, [vtbl+0x68], where the vendored
// header puts it at slot 14. setSequentialTimer stays a direct call and is
// pinned at ILT 0x00027237; it is the last statement, so retail tail-jumps to
// it.
//
// Worth noting for whoever converts the neighbouring script actions: retail
// loads two *different* globals here, 0x012F076C for the getTeamNamed receiver
// and 0x012F0888 for the setSequentialTimer one, where the reference writes
// TheScriptEngine for both. Those are DIR32 sites and therefore masked, so the
// byte match cannot tell them apart and neither can this conversion -- but a
// body that needs both objects to be distinct will care.

typedef int Int;

class AsciiString;
class Team;

class ScriptEngine
{
public:
	// Only the one slot is named; the rest exist to place it.
	virtual void unused0( void ) = 0;
	virtual void unused1( void ) = 0;
	virtual void unused2( void ) = 0;
	virtual void unused3( void ) = 0;
	virtual void unused4( void ) = 0;
	virtual void unused5( void ) = 0;
	virtual void unused6( void ) = 0;
	virtual void unused7( void ) = 0;
	virtual void unused8( void ) = 0;
	virtual void unused9( void ) = 0;
	virtual void unused10( void ) = 0;
	virtual void unused11( void ) = 0;
	virtual void unused12( void ) = 0;
	virtual void unused13( void ) = 0;
	virtual void unused14( void ) = 0;
	virtual void unused15( void ) = 0;
	virtual void unused16( void ) = 0;
	virtual void unused17( void ) = 0;
	virtual void unused18( void ) = 0;
	virtual void unused19( void ) = 0;
	virtual void unused20( void ) = 0;
	virtual void unused21( void ) = 0;
	virtual void unused22( void ) = 0;
	virtual void unused23( void ) = 0;
	virtual void unused24( void ) = 0;
	virtual void unused25( void ) = 0;

	virtual Team *getTeamNamed( const AsciiString &name ) = 0;	///< slot 26, [vtbl+0x68]

	void setSequentialTimer( Team *team, Int frames );			///< ILT 0x00027237
};

extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doTeamSpinForFramecount( const AsciiString& teamName, Int waitForFrames );
};

//-------------------------------------------------------------------------------------------------
/** doTeamSpinForFramecount */
//-------------------------------------------------------------------------------------------------
// ?doTeamSpinForFramecount@ScriptActions@@IAEXABVAsciiString@@H@Z
void ScriptActions::doTeamSpinForFramecount( const AsciiString& teamName, Int waitForFrames )
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);
	if (!team) {
		return;
	}

	TheScriptEngine->setSequentialTimer(team, waitForFrames);
}
