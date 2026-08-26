// cl: /O2 /Ob0

struct Rva005BDE00Vec
{
	int x;
	int y;
	int z;
};

class Rva005BDE00
{
	char m_pad[0xCC];
	int m_CC;
	char m_mid1[0xDC - 0xD0];
	int m_DC;
	char m_mid2[0xEC - 0xE0];
	int m_EC;
	char m_mid3[0x1A4 - 0xF0];
	char m_1A4;

public:
	void set(const Rva005BDE00Vec *p);
};

void Rva005BDE00::set(const Rva005BDE00Vec *p)
{
	m_CC = p->x;
	m_DC = p->y;
	m_EC = p->z;
	m_1A4 = 0;
}
