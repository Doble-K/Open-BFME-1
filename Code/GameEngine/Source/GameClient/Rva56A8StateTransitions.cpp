// Address-derived state transitions. The owner is not recovered; the fields
// below are fixed by the retail receiver accesses at these two boundaries.
class Rva56A8StateOwner
{
public:
	void applyZeroState(int);
	void applyFourState(int);

private:
	char m_pad0[0x258];
	volatile int m_state;
	char m_pad25c[0x20];
	int m_auxiliaryState;
};

void Rva56A8StateOwner::applyZeroState(int)
{
	if (m_state == 0) {
		m_auxiliaryState = 1;
		m_state = 2;
	}
}

void Rva56A8StateOwner::applyFourState(int)
{
	if (m_state == 0) {
		m_auxiliaryState = 4;
		m_state = 2;
	}
}
