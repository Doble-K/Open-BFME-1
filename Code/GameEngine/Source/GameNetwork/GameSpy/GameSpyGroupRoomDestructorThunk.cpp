// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GameSpyGroupRoom dtor. AsciiString @+0 then UnicodeString @+4.

class AsciiString
{
public:
	~AsciiString();

private:
	unsigned char m_pad[4];
};

class UnicodeString
{
public:
	~UnicodeString();

private:
	unsigned char m_pad[4];
};

class GameSpyGroupRoom
{
public:
	~GameSpyGroupRoom();

private:
	AsciiString m_ascii;
	UnicodeString m_unicode;
};

// ??1GameSpyGroupRoom@@QAE@XZ
GameSpyGroupRoom::~GameSpyGroupRoom()
{
}
