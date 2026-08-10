// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: TextTypeTransition destructor lifted to clean C++.

class UnicodeString
{
public:
	~UnicodeString();

private:
	unsigned char m_pad[4];
};

class DisplayString;

class DisplayStringManager
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void freeDisplayString(DisplayString *string);
};

extern DisplayStringManager *TheDisplayStringManager;

class CountUpTransitionBase
{
public:
	virtual ~CountUpTransitionBase();
};

class TextTypeTransition : public CountUpTransitionBase
{
public:
	virtual ~TextTypeTransition();

private:
	unsigned char m_gap0[8];
	void *m_win;
	unsigned char m_gap1[0x1c];
	UnicodeString m_fullText;
	UnicodeString m_partialText;
	DisplayString *m_dStr;
};

// ??1TextTypeTransition@@UAE@XZ
TextTypeTransition::~TextTypeTransition()
{
	m_win = 0;
	if (m_dStr)
		TheDisplayStringManager->freeDisplayString(m_dStr);
	m_dStr = 0;
}
