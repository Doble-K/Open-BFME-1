// cl: /DNDEBUG /MD /EHsc

class Rva56E070StateOwner
{
public:
	char m_pad0[0x258];
	int m_state;
	int m_direction;
	char m_pad260[0x1c];
	int m_auxiliaryState;

	void finishState14();
	void finishState15();
	void finishState16();
	void dispatchLateState(int unused);
};

void Rva56E070StateOwner::dispatchLateState(int unused)
{
	if (m_state == 14) {
		if (m_auxiliaryState == 4) {
			finishState14();
			return;
		}
		m_state = 3;
		return;
	}
	if (m_state == 15) {
		finishState15();
		return;
	}
	if (m_state == 16) {
		finishState16();
		return;
	}
	if (m_state == 17) {
		m_state = m_direction != 0 ? 3 : 1;
	}
}
