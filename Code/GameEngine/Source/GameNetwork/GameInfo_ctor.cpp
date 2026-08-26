// cl: /DNDEBUG /MD /EHsc

class AsciiString
{
public:
	__forceinline AsciiString() : m_data(0) {}
	~AsciiString();

private:
	char *m_data;
};

class GameSlot;

class Money
{
public:
	__forceinline Money() : m_value(0) {}

private:
	int m_value;
};

class GameInfo
{
public:
	GameInfo();
	virtual void reset();

private:
	int m_preorderMask;
	int m_crcInterval;
	unsigned char m_inGame;
	unsigned char m_inProgress;
	unsigned char m_oldFactionsOnly;
	unsigned char m_padding0f;
	int m_gameID;
	GameSlot *m_slots[8];
	Money m_startingCash;
	unsigned short m_superweaponRestriction;
	unsigned char m_padding3a[2];
	AsciiString m_mapName;
};

GameInfo::GameInfo()
	: m_superweaponRestriction(0)
{
	for (int i = 0; i < 8; ++i)
		m_slots[i] = 0;
	reset();
}
