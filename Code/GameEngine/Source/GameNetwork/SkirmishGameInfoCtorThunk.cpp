// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the retail skirmish slot-array constructor to C++.

class GameSlot
{
public:
	GameSlot();
	~GameSlot();
private:
	unsigned char m_storage[0x44];
};

class GameInfo
{
public:
	GameInfo();
	virtual ~GameInfo();
	void setSlotPointer(int index, GameSlot *slot);
private:
	unsigned char m_storage[0x54];
};

class Snapshot
{
public:
	virtual ~Snapshot();
};

class SkirmishGameInfo : public GameInfo, public Snapshot
{
public:
	SkirmishGameInfo();
	virtual ~SkirmishGameInfo();
private:
	virtual void crc(void *);
	virtual void xfer(void *);
	virtual void loadPostProcess();
	GameSlot m_skirmishSlot[8];
};

SkirmishGameInfo::SkirmishGameInfo()
{
	for (int i = 0; i < 8; ++i)
		setSlotPointer(i, &m_skirmishSlot[i]);
}
