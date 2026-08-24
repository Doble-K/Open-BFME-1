// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva000C94D0Vec
{
	int a;
	int b;
	int c;
};

class Rva000C94D0Inner
{
public:
	char m_pad[0x34];
	Rva000C94D0Vec m_v;
	unsigned char m_flag;
};

class Rva000C94D0
{
	char m_pad[0x220];
	Rva000C94D0Inner *m_inner;

public:
	unsigned char copy(Rva000C94D0Vec *dest);
};

unsigned char Rva000C94D0::copy(Rva000C94D0Vec *dest)
{
	Rva000C94D0Inner *p = m_inner;
	if (p)
	{
		*dest = p->m_v;
		return p->m_flag;
	}
	return 0;
}
