// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ reconstruction of positional named-unit audio.

class AsciiString;
enum ObjectID {};

class Player
{
public:
	int getPlayerIndex() const { return m_playerIndex; }
	unsigned char m_pad[0x24];
	int m_playerIndex;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	ObjectID getID() const { return m_id; }
	unsigned char m_pad[0x74];
	ObjectID m_id;
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &, ObjectID);
	virtual ~AudioEventRTS();
	void setIsLogicalAudio(bool);
	void setPlayerIndex(int);
private:
	unsigned char m_data[0x6C];
};

class ScriptEngine
{
public:
	virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
	virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
	virtual void slot8(); virtual void slot9(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual Object *getUnitNamed(const AsciiString &name);
};

class AudioManager
{
public:
	virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
	virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
	virtual void slot8(); virtual void slot9(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16();
	virtual void addAudioEvent(const AudioEventRTS *event);
};

extern ScriptEngine *TheScriptEngine;
extern AudioManager *TheAudio;

class ScriptActions
{
protected:
	void doSoundPlayFromNamed(const AsciiString &, const AsciiString &);
};

void ScriptActions::doSoundPlayFromNamed(const AsciiString &soundName, const AsciiString &unitName)
{
	Object *unit = TheScriptEngine->getUnitNamed(unitName);
	if (!unit)
		return;

	AudioEventRTS event(soundName, unit->getID());
	event.setIsLogicalAudio(true);
	Player *player = unit->getControllingPlayer();
	if (player)
		event.setPlayerIndex(player->getPlayerIndex());
	TheAudio->addAudioEvent(&event);
}
