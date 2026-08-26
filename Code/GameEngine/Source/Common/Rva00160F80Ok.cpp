// cl: /O2 /Ob0

struct Rva00160F80Node
{
	char pad[0x0C];
	Rva00160F80Node *m_0C;
	int m_10;
	int m_14;
};

class Rva00160F80
{
	char pad[0x14];
	Rva00160F80Node *m_14;

public:
	bool ok();
};

bool Rva00160F80::ok()
{
	bool bad = false;
	for (Rva00160F80Node *p = m_14; p; p = p->m_0C)
	{
		if (p->m_14 > p->m_10)
			bad = true;
	}
	return !bad;
}
