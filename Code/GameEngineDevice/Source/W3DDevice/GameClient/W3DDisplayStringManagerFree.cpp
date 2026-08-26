// cl: /DNDEBUG /MD /EHsc

class DisplayString
{
public:
	virtual ~DisplayString();
};

class DisplayStringManager
{
public:
	virtual ~DisplayStringManager();

protected:
	void unLink(DisplayString *string);

	unsigned char m_padding04[0x04];
	DisplayString *m_stringList;
	DisplayString *m_currentCheckpoint;
};

class W3DDisplayStringManager : public DisplayStringManager
{
public:
	virtual void freeDisplayString(DisplayString *string);
};

void W3DDisplayStringManager::freeDisplayString(DisplayString *string)
{
	if (!string) {
		return;
	}

	unLink(string);
	if (m_currentCheckpoint == string) {
		m_currentCheckpoint = 0;
	}
	delete string;
}
