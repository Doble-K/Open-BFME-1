// cl: /DNDEBUG /MD /EHsc

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
	UnicodeString(const UnicodeString &other)
		: StringBase<unsigned short>(other)
	{
	}

	~UnicodeString() {}
};

class ConnectionManager
{
public:
	UnicodeString getPlayerName(Int player);
	UnsignedInt getLocalPlayerID();
};

class DisconnectMenu
{
public:
	void setPlayerName(Int slot, UnicodeString name);
	void updateVotes(Int slot, Int votes);
};

extern DisconnectMenu *TheDisconnectMenu;

class DisconnectManager
{
protected:
	void populateDisconnectScreen(ConnectionManager *connectionManager);
	Int countVotesForPlayer(Int player, ConnectionManager *connectionManager);
};

// ?populateDisconnectScreen@DisconnectManager@@IAEXPAVConnectionManager@@@Z
void DisconnectManager::populateDisconnectScreen(ConnectionManager *connectionManager)
{
	if (!TheDisconnectMenu)
		return;

	for (Int player = 0; player < 8; ++player)
	{
		UnicodeString name = connectionManager->getPlayerName(player);
		Int localPlayer = connectionManager->getLocalPlayerID();
		Int slot;
		if (player < localPlayer)
			slot = player;
		else if (player == localPlayer)
			continue;
		else
			slot = player - 1;

		if (slot != -1)
		{
			TheDisconnectMenu->setPlayerName(slot, name);
			Int votes = countVotesForPlayer(player, connectionManager);
			TheDisconnectMenu->updateVotes(slot, votes);
		}
	}
}
