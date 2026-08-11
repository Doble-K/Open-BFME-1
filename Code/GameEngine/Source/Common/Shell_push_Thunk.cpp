// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ reconstruction of the shell layout push path.

struct AsciiStringData
{
	unsigned short m_refCount;
	unsigned short m_allocated;
	unsigned short m_length;
};

class AsciiString
{
public:
	~AsciiString();
	AsciiString &operator=(const AsciiString &);
	bool isEmpty() const { return m_data == 0 || m_data->m_length == 0; }
private:
	AsciiStringData *m_data;
};

class WindowLayout
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void runShutdown(bool *immediate);
	unsigned char m_pad[0x10];
	bool m_hidden;
};

extern void *TheGameSpyInfo;
void GameSpyCloseAllOverlays();

class Shell
{
public:
	void push(AsciiString filename, bool shutdownImmediate);
	void shutdownComplete(WindowLayout *layout, int unknown);
private:
	unsigned char m_unknown0[4];
	WindowLayout *m_screenStack[17];
	int m_screenCount;
	bool m_pendingPush;
	unsigned char m_gap[7];
	AsciiString m_pendingPushName;
};

void Shell::push(AsciiString filename, bool shutdownImmediate)
{
	if (filename.isEmpty())
		return;

	if (TheGameSpyInfo)
		GameSpyCloseAllOverlays();

	if (m_screenCount >= 16)
		return;

	AsciiString *pendingName = &m_pendingPushName;
	m_pendingPush = true;
	*pendingName = filename;

	WindowLayout *currentTop = m_screenCount ? m_screenStack[m_screenCount] : 0;
	if (currentTop && !currentTop->m_hidden)
		currentTop->runShutdown(&shutdownImmediate);
	else
		shutdownComplete(0, 0);
}
