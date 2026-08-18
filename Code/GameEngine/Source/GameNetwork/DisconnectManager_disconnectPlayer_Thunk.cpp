// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef int Int;
typedef unsigned int UnsignedInt;

class UnicodeString;

template <class T>
class StringBase
{
private:
	friend class UnicodeString;

	StringBase(const StringBase<T> &other);
	~StringBase();

	void *m_data;
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
};

enum PlayerLeaveCode
{
	PLAYERLEAVECODE_UNKNOWN
};

class GameSlot
{
public:
	void markAsDisconnected()
	{
		m_disconnected = true;
	}

private:
	unsigned char m_unreconstructed_00[0x40];
	bool m_disconnected;
};

class GameInfo
{
public:
	GameSlot *getSlot(Int slot);
};

class ConnectionManager
{
public:
	UnsignedInt getLocalPlayerID();
	UnicodeString getPlayerName(Int playerNum);
	PlayerLeaveCode disconnectPlayer(Int slot);
};

class RecorderClass
{
public:
	void logPlayerDisconnect(UnicodeString player, Int slot);
};

class DisconnectMenu
{
public:
	void removePlayer(Int slot, UnicodeString playerName);
};

extern GameInfo *TheGameInfo;
extern RecorderClass *TheRecorder;
extern DisconnectMenu *TheDisconnectMenu;

class DisconnectManager
{
protected:
	void disconnectPlayer(Int slot, ConnectionManager *conMgr);
};

// BFME's slot record places m_disconnected four bytes later than Zero Hour's.
void DisconnectManager::disconnectPlayer(Int slot, ConnectionManager *conMgr)
{
	if (slot < 0 || slot >= 8)
		return;

	if (TheGameInfo)
	{
		GameSlot *gameSlot = TheGameInfo->getSlot(slot);
		if (gameSlot)
			gameSlot->markAsDisconnected();
	}

	Int localSlot = conMgr->getLocalPlayerID();
	Int translatedSlot;
	if (slot < localSlot)
		translatedSlot = slot;
	else if (slot == localSlot)
		return;
	else
		translatedSlot = slot - 1;

	if (translatedSlot != -1)
	{
		UnicodeString playerName = conMgr->getPlayerName(slot);
		TheRecorder->logPlayerDisconnect(playerName, slot);
		if (TheDisconnectMenu)
			TheDisconnectMenu->removePlayer(translatedSlot, playerName);
		conMgr->disconnectPlayer(slot);
	}
}
