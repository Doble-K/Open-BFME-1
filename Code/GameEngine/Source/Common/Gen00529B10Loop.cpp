// cl: /DNDEBUG /MD /EHsc

class Gen_00529B10
{
public:
	void bfmeLoop(void);
	void bfmeGen00029C35(int index);
	void bfmeGen0002EA91(int index, bool value);
	void bfmeGen0002D38A(int index);

private:
	unsigned char m_unmodelled[0x16];
	bool m_running;
};

// The three helper names preserve their retail ILT addresses because no retail
// spellings are exposed by the call sites or their still-anonymous bodies.
// ?bfmeLoop@Gen_00529B10@@QAEXXZ
void Gen_00529B10::bfmeLoop(void)
{
	if (!m_running)
	{
		m_running = true;
		for (int index = 0; index < 8; ++index)
		{
			bfmeGen00029C35(index);
			bfmeGen0002EA91(index, false);
			bfmeGen0002D38A(index);
		}
		m_running = false;
	}
}
