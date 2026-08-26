// cl: /O2 /Ob0

class Obj005BE170
{
public:
	char pad[0x74];
	int m_74;
};

class Rva005BE170
{
	char pad[0xB8];
	int m_b8;

public:
	void set(Obj005BE170 *p);
};

void Rva005BE170::set(Obj005BE170 *p)
{
	if (p)
		m_b8 = p->m_74;
	else
		m_b8 = 0;
}
