// cl: /DNDEBUG /MD /EHsc

class Gen005291F0Owner
{
public:
	virtual void bfmeSlot0(void) = 0;
	virtual void bfmeSlot1(void) = 0;
	virtual void bfmeSlot2(void) = 0;
	virtual void bfmeSlot3(void) = 0;
	virtual void bfmeSlot4(void) = 0;
	virtual void bfmeSlot5(void) = 0;
	virtual void bfmeSlot6(void) = 0;
	virtual void bfmeSlot7(void) = 0;
	virtual void bfmeSlot8(void) = 0;
	virtual bool bfmeContains(int value) = 0;
};

class Gen_005291F0
{
public:
	void bfmeRefresh(void);
	void bfmeGen00018C1E(int index);

private:
	unsigned char m_unmodelled[4];
	Gen005291F0Owner *m_owner;
	int m_first;
	int m_second;
	unsigned char m_unmodelled10[2];
	bool m_firstDirty;
	bool m_secondDirty;
	unsigned char m_unmodelled14[2];
	bool m_running;
};

// The helper keeps its retail ILT in its name because neither the call site nor
// the still-anonymous target body exposes a retail spelling.
// ?bfmeRefresh@Gen_005291F0@@QAEXXZ
void Gen_005291F0::bfmeRefresh(void)
{
	if (m_first && !m_owner->bfmeContains(m_first))
		m_first = 0;

	if (m_second && !m_owner->bfmeContains(m_second))
		m_second = 0;

	if (m_first && !m_running)
	{
		m_running = true;
		for (int index = 0; index < 8; ++index)
			bfmeGen00018C1E(index);

		m_firstDirty = true;
		m_secondDirty = true;
		m_running = false;
	}
}
