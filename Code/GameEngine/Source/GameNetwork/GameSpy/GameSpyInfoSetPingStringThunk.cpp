// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: GameSpyInfo::setPingString

class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &);
};

class GameSpyInfo
{
public:
	virtual void setPingString(const AsciiString &ping);

private:
	unsigned char m_pad[0x10];
	AsciiString m_ping;
};

// ?setPingString@GameSpyInfo@@UAEXABVAsciiString@@@Z
void GameSpyInfo::setPingString(const AsciiString &ping)
{
	m_ping = ping;
}
