// cl: /DNDEBUG /MD /EHsc

// FILE: SkirmishBattleHonorsLoyalGames.cpp ///////////////////////////////////
//
// SkirmishBattleHonors::setNumGamesLoyal, retail 0x0009DA60, and
// getNumGamesLoyal, retail 0x0009DA90.
//
// No port of SkirmishBattleHonors.cpp exists under Code/.  Both bodies were
// found by the string they push -- "LoyalGames" appears in exactly one
// reference source, and the function enclosing it names them.  Each is three
// lines: build an AsciiString key from the literal and hand it to the base
// class's setInt or getInt.
//
// AsciiString is spelled here with its constructor delegating to
// StringBase<char>, which is what BFME's really does and what
// reference/shims/campaignmanagerascii carries.  It is not cosmetic: a
// declared-only constructor leaves the by-value temporary opaque and MSVC then
// emits `mov ecx,esp' before the frame store rather than after, which is six
// bytes wrong in a thirty-six byte function.  See
// docs/lessons-archive.md on the by-value temporary transposition.
//
///////////////////////////////////////////////////////////////////////////////

typedef int Int;
// bool, not unsigned char: the retail symbols spell it _N, and E would be a
// different setBool and getBool entirely.
typedef bool Bool;

#define TRUE 1
#define FALSE 0

template <class Type>
class StringBase
{
private:
	// Private, not public: the ledger already names this body
	// decorated ??0?$StringBase@D@@AAE@PBD@Z, and a public declaration spells the
	// symbol QAE and need a pin of its own for no reason.
	StringBase(const char *s);
	StringBase(const StringBase &that);
	friend class AsciiString;
};

class AsciiString
{
public:

	AsciiString(const char *s)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(s);
	}

	// Declared so the temporary is built straight into the argument slot rather
	// than materialised somewhere else and re-pushed.
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
	}

	~AsciiString();

	static AsciiString TheEmptyString;

private:

	void *m_text;

};

class UserPreferences
{
public:

	// setAsciiString is VIRTUAL in BFME and the int and bool accessors are not:
	// retail reaches it as mov edx,[esi] / call [edx+0x1c] while setInt, getInt,
	// setBool and getBool are all direct calls.  Seven anonymous slots put it on
	// 0x1c; what they hold this file does not say.
	virtual void bfmeSlot00() = 0;
	virtual void bfmeSlot04() = 0;
	virtual void bfmeSlot08() = 0;
	virtual void bfmeSlot0C() = 0;
	virtual void bfmeSlot10() = 0;
	virtual void bfmeSlot14() = 0;
	virtual AsciiString getAsciiString(AsciiString key, AsciiString defaultValue) const = 0;	// @0x18
	virtual void setAsciiString(AsciiString key, AsciiString val) = 0;		// @0x1c

	Bool getBool(AsciiString key, Bool defaultValue) const;
	Int getInt(AsciiString key, Int defaultValue) const;
	void setBool(AsciiString key, Bool val);
	void setInt(AsciiString key, Int val);
};

class SkirmishBattleHonors : public UserPreferences
{
public:
	void setLastHouse(AsciiString val);
	AsciiString getLastHouse(void) const;
	void setBuiltSCUD(void);
	Bool builtSCUD(void) const;
	void setBuiltParticleCannon(void);
	Bool builtParticleCannon(void) const;
	void setBuiltNuke(void);
	Bool builtNuke(void) const;
	void setChallengeMedals(Int val);
	Int getChallengeMedals(void) const;
	void setHonors(Int which);
	Int getHonors(void) const;
	void setNumGamesLoyal(Int val);
	Int getNumGamesLoyal(void) const;
};

void SkirmishBattleHonors::setBuiltSCUD(void)
{
	setBool("SCUD", TRUE);
}

Bool SkirmishBattleHonors::builtSCUD(void) const
{
	return getBool("SCUD", FALSE);
}

void SkirmishBattleHonors::setBuiltParticleCannon(void)
{
	setBool("PPC", TRUE);
}

Bool SkirmishBattleHonors::builtParticleCannon(void) const
{
	return getBool("PPC", FALSE);
}

void SkirmishBattleHonors::setBuiltNuke(void)
{
	setBool("Nuke", TRUE);
}

Bool SkirmishBattleHonors::builtNuke(void) const
{
	return getBool("Nuke", FALSE);
}

void SkirmishBattleHonors::setChallengeMedals(Int val)
{
	setInt("Challenge", val);
}

Int SkirmishBattleHonors::getChallengeMedals(void) const
{
	return getInt("Challenge", 0);
}

void SkirmishBattleHonors::setHonors(Int which)
{
	Int honors = getInt("Honors", 0);
	setInt("Honors", honors | which);
}

Int SkirmishBattleHonors::getHonors(void) const
{
	return getInt("Honors", 0);
}

void SkirmishBattleHonors::setNumGamesLoyal(Int val)
{
	setInt("LoyalGames", val);
}

Int SkirmishBattleHonors::getNumGamesLoyal(void) const
{
	return getInt("LoyalGames", 0);
}

void SkirmishBattleHonors::setLastHouse(AsciiString val)
{
	setAsciiString("LastHouse", val);
}

AsciiString SkirmishBattleHonors::getLastHouse(void) const
{
	return getAsciiString("LastHouse", AsciiString::TheEmptyString);
}
