// cl: /O2 /Ob0

class Rva00722120Base
{
public:
	Rva00722120Base();
	virtual void handle();

private:
	char m_pad[0x20];
};

class Rva00722120 : public Rva00722120Base
{
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	int m_3C;
	int m_40;

public:
	Rva00722120();
};

Rva00722120::Rva00722120()
{
	m_24 = 0;
	m_28 = 0;
	m_2C = 0;
	m_30 = 0;
	m_34 = 0;
	m_38 = 0;
	m_3C = 0;
	m_40 = 0x00FFEEDD;
}
