// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ lift of the retail Mission constructor.

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();

	static const AsciiString TheEmptyString;

private:
	char *m_data;
};

enum ObjectID {};

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName = AsciiString::TheEmptyString, ObjectID ownerID = (ObjectID)2);
	~AudioEventRTS();

private:
	unsigned char m_data[112];
};

class MemoryPoolObject
{
public:
	virtual void deleteInstance();
};

class Mission : public MemoryPoolObject
{
public:
	Mission();
	virtual ~Mission();

private:
	AsciiString m_name;
	AsciiString m_mapName;
	AsciiString m_nextMission;
	AsciiString m_movieLabel;
	AsciiString m_missionObjectivesLabel[5];
	AudioEventRTS m_briefingVoice;
	AsciiString m_locationNameLabel;
	AsciiString m_unitNames[3];
	int m_voiceLength;
};

Mission::Mission() : m_voiceLength(0)
{
}
