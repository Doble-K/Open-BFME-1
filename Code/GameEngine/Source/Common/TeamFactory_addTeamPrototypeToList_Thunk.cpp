// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the TeamFactory::addTeamPrototypeToList naked dump to clean C++.
//
// Zero Hour's Team.cpp body with one structural change: ZH keys the prototype
// map on a single NameKeyType, while BFME keys it on a pair. Retail hashes two
// AsciiStrings from the prototype -- the one at +0x14 first, then the one at
// +0x10 -- and stores them into a two-dword key built on the stack, so the map
// is keyed by both names rather than one. Only the offsets are proven here; the
// names below are the plausible reading of which is which.
//
// ZH's early return collapses because the DEBUG_ASSERTCRASH it guards is
// compiled out, so what is left is the positive form: insert only when the
// lookup came back empty.
//
// operator[] returns the mapped slot by reference, which is why retail stores
// through the returned pointer rather than passing the value in.
//
// Retail pins the layout: the map is at this+0x0C and its first word is the end
// sentinel, and str() inlines to "m_data ? m_data+8 : empty".

class AsciiStringData
{
public:
	unsigned char m_unreconstructed_00[8];
	char m_chars[1];									///< retail this+0x08
};

class AsciiString
{
public:
	const char *str(void) const { return m_data ? m_data->m_chars : ""; }

private:
	AsciiStringData *m_data;
};

enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);			///< ILT thunk at 0x0003ADD7
};

extern NameKeyGenerator *TheNameKeyGenerator;			///< retail [0x012ED600]

#define NAMEKEY(x) (TheNameKeyGenerator->nameToKey((x).str()))

class TeamPrototype
{
public:
	const AsciiString &getName(void) const { return m_name; }
	const AsciiString &getOwnerName(void) const { return m_ownerName; }

private:
	unsigned char m_unreconstructed_00[0x10];
	AsciiString m_name;									///< retail this+0x10
	AsciiString m_ownerName;							///< retail this+0x14
};

struct TeamPrototypeKey
{
	TeamPrototypeKey(NameKeyType name, NameKeyType owner) : m_name(name), m_owner(owner) {}

	NameKeyType m_name;									///< retail key+0x00
	NameKeyType m_owner;								///< retail key+0x04
};

struct TeamPrototypeNode;

class TeamPrototypeMap
{
public:
	TeamPrototypeNode *find(const TeamPrototypeKey &key) const;		///< ILT thunk at 0x00011CB6
	TeamPrototype *&operator[](const TeamPrototypeKey &key);			///< ILT thunk at 0x00003B20

	TeamPrototypeNode *end(void) const { return m_end; }

private:
	TeamPrototypeNode *m_end;							///< retail this+0x00
};

class TeamFactory
{
public:
	void addTeamPrototypeToList(TeamPrototype *team);

private:
	unsigned char m_unreconstructed_00[0x0C];
	TeamPrototypeMap m_prototypes;						///< retail this+0x0C
};

// ?addTeamPrototypeToList@TeamFactory@@QAEXPAVTeamPrototype@@@Z
void TeamFactory::addTeamPrototypeToList(TeamPrototype* team)
{
	// sequenced: retail hashes the owner name and calls, then the team name and
	// calls. Passing both as constructor arguments lets MSVC hoist the two str()
	// computations together ahead of both calls, which retail does not do.
	NameKeyType ownerKey = NAMEKEY(team->getOwnerName());
	NameKeyType nameKey = NAMEKEY(team->getName());
	TeamPrototypeKey nk(nameKey, ownerKey);
	TeamPrototypeNode *it = m_prototypes.find(nk);
	if (it == m_prototypes.end())
	{
		m_prototypes[nk] = team;
	}
}
