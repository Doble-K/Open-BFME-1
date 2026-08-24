// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva004097F0Inner
{
	char m_pad[0x44];
	unsigned char m_44;
};

class Rva004097F0
{
	char m_pad0[0xC];
	int m_C;
	char m_pad1[8];
	Rva004097F0Inner *m_18;

public:
	void set(unsigned char value);
};

void Rva004097F0::set(unsigned char value)
{
	if (m_C == 1)
	{
		if (m_18)
			m_18->m_44 = value;
	}
}
