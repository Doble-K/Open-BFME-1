// cl: /O2 /Ob0

class Made002DF2B0
{
public:
	Made002DF2B0();
	virtual void handle();

private:
	char m_pad[0x54];
};

class Rva002DCBA0 : public Made002DF2B0
{
	char m_58;
	char m_59;
	int m_5C;
	int m_60;
	int m_64;
	int m_68;
	float m_6C;

public:
	Rva002DCBA0();
};

Rva002DCBA0::Rva002DCBA0()
{
	m_59 = 0;
	m_5C = 0;
	m_60 = 0;
	m_64 = 0;
	m_68 = 0;
	m_58 = 1;
	m_6C = 1.0f;
}
