// cl: /DNDEBUG /MD /EHsc

// ScriptConditions::evaluateTeamInsideAreaEntirely, 0x00324AC0, 213 bytes.
//
// The reference's body -- it is the TeamInside condition despite the name --
// with the one BFME change its sibling
// ScriptConditions_evaluateTeamCanPathToWaypoint.cpp already carries:
// getTeamNamed takes a second Bool the reference does not have.
//
// The two ScriptEngine slots are read off the call sites rather than guessed:
// getTeamNamed is vtable+0x44 (slot 17), which the sibling already pins, and
// getQualifiedTriggerAreaByName is vtable+0x58 (slot 22).
//
// Parameter::getString returns a const reference and getInt the Int at +0x08;
// both are inlined here, so the two by-value AsciiString arguments are built
// in the outgoing argument slots by StringBase<char>'s copy constructor. That
// is why AsciiString is the delegating slice the sibling uses -- a copy
// constructor that visibly forwards to StringBase<char> is what puts the
// __$SEHRec$ store ahead of `mov ecx, esp`.
//
// One callee is pinned rather than owned: ?allInside@Team@@QBE_NPAVPolygonTrigger@@I@Z
// at 0x000F5A30, the call this body makes on the team it looked up.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class PolygonTrigger;

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();
};

class AsciiString
{
public:
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString();

private:
	char *m_text;
};

class Parameter
{
public:
	Int getInt(void) const { return m_int; }
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeInt[8];
	Int m_int;						// this+0x08
	unsigned char m_beforeString[0x10 - 0x0C];
	AsciiString m_string;					// this+0x10
};

class Team
{
public:
	Bool allInside(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const;	// retail 0x000F5A30
};

class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual Team *getTeamNamed(AsciiString, Bool) = 0;		// slot 17, vtable+0x44
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString) = 0;	// slot 22, vtable+0x58
};

extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
	Bool evaluateTeamInsideAreaEntirely(Parameter *, Parameter *, Parameter *);
};

// ?evaluateTeamInsideAreaEntirely@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluateTeamInsideAreaEntirely(Parameter *pTeamParm, Parameter *pTriggerParm, Parameter *pTypeParm)
{// This is actually TeamInside(...)
	Team *theTeam = TheScriptEngine->getTeamNamed( pTeamParm->getString(), false );
	AsciiString triggerName = pTriggerParm->getString();
	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerParm->getString());

	if (pTrig == 0)
		return false;

	if (theTeam) {
		return theTeam->allInside(pTrig, (UnsignedInt)pTypeParm->getInt());
	}
	return false; // Non existent team isn't in trigger area. :)
}
