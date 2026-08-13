// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: Team::getControllingPlayer lifted from the BFME retail layout.

class Player;

class TeamPrototype
{
	unsigned char m_pad[8];
public:
	Player *m_controllingPlayer;
};

class Team
{
public:
	virtual ~Team();
	Player *getControllingPlayer() const;

private:
	TeamPrototype *m_proto;
};

Player *Team::getControllingPlayer() const
{
	TeamPrototype *proto = m_proto;
	if (!proto)
		return reinterpret_cast<Player *>(proto);
	return proto->m_controllingPlayer;
}
