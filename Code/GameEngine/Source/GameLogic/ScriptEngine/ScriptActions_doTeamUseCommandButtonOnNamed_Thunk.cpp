// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class AIGroup;
class Object;
class Team;
struct Coord3D;

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

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

enum GUICommandType
{
	GUI_COMMAND_NONE = 0
};

class Overridable
{
public:
	Overridable *friend_getFinalOverride()
	{
		if (m_nextOverride) {
			return m_nextOverride->friend_getFinalOverride();
		}
		return this;
	}
	const Overridable *friend_getFinalOverride() const
	{
		if (m_nextOverride) {
			return m_nextOverride->friend_getFinalOverride();
		}
		return this;
	}

private:
	void *m_memoryPoolVTable;
	Overridable *m_nextOverride;
	Bool m_isOverride;
};

class SpecialPowerTemplate : public Overridable
{
public:
	UnsignedInt getID() const
	{
		return getFinalOverride()->m_id;
	}

private:
	const SpecialPowerTemplate *getFinalOverride() const
	{
		return (const SpecialPowerTemplate *)friend_getFinalOverride();
	}
	AsciiString m_name;
	UnsignedInt m_id;
};

class CommandButton
{
public:
	GUICommandType getCommandType() const { return m_command; }
	const SpecialPowerTemplate *getSpecialPowerTemplate() const { return m_specialPower; }
	Bool isValidToUseOn(const Object *, const Object *, const Coord3D *, CommandSourceType) const;

private:
	unsigned char m_beforeCommand[0x10];
	GUICommandType m_command;
	unsigned char m_beforeSpecialPower[0x20];
	const SpecialPowerTemplate *m_specialPower;
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
	virtual Team *getTeamNamed(AsciiString, Bool) = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &) = 0;
};

class AI
{
public:
	AIGroup *createGroup();
};

class Team
{
public:
	void getTeamAsAIGroup(AIGroup *);
};

class AIGroup
{
public:
	void groupDoCommandButtonAtObject(const CommandButton *, Object *, CommandSourceType);
	Object *getSpecialPowerSourceObject(UnsignedInt);
	Object *getCommandButtonSourceObject(GUICommandType);
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &);
};

extern AI *TheAI;
extern ControlBar *TheControlBar;
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doTeamUseCommandButtonOnNamed(
		const AsciiString &, const AsciiString &, const AsciiString &);
};

// ?doTeamUseCommandButtonOnNamed@ScriptActions@@IAEXABVAsciiString@@00@Z
void ScriptActions::doTeamUseCommandButtonOnNamed(
	const AsciiString &teamName, const AsciiString &commandAbility, const AsciiString &unitName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team) {
		return;
	}

	AIGroup *theGroup = TheAI->createGroup();
	team->getTeamAsAIGroup(theGroup);

	const CommandButton *commandButton = TheControlBar->findCommandButton(commandAbility);
	if (!commandButton) {
		return;
	}

	Object *srcObj = 0;
	if (commandButton->getSpecialPowerTemplate()) {
		srcObj = theGroup->getSpecialPowerSourceObject(
			commandButton->getSpecialPowerTemplate()->getID());
	} else {
		srcObj = theGroup->getCommandButtonSourceObject(commandButton->getCommandType());
	}

	if (!srcObj) {
		return;
	}

	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (!obj) {
		return;
	}

	if (commandButton->isValidToUseOn(srcObj, obj, 0, CMD_FROM_SCRIPT)) {
		theGroup->groupDoCommandButtonAtObject(commandButton, obj, CMD_FROM_SCRIPT);
	}
}
