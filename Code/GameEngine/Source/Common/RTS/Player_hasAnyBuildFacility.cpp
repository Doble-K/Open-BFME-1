// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: Player::hasAnyBuildFacility, retail 0x000CE100, 48 bytes.
//
// The reference's body unchanged: ask each team prototype in turn. The
// prototype list is at this+0x288 and the loop reloads the list header each
// iteration for the end test, the call in between being enough to make it.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef bool Bool;

class TeamPrototype
{
public:
	Bool hasAnyBuildFacility(void) const;			// ILT 0x00032C81
};

typedef _STL::list<TeamPrototype *> PlayerTeamList;

class Player
{
public:
	Bool hasAnyBuildFacility(void) const;

private:
	char m_slice_pad[0x288];				// retail this+0x00 .. +0x287, untouched
	PlayerTeamList m_playerTeamPrototypes;			// this+0x288
};

Bool Player::hasAnyBuildFacility(void) const
{
	for (PlayerTeamList::const_iterator it = m_playerTeamPrototypes.begin();
			 it != m_playerTeamPrototypes.end(); ++it)
	{
		if ((*it)->hasAnyBuildFacility()) {
			return true;
		}
	}
	return false;
}
