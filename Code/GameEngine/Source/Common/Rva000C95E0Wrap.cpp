// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Gen00005DF3
{
public:
	void handle(int a);
};

class Rva000C95E0
{
	char m_pad[0x220];
	Gen00005DF3 *m_inner;

public:
	void wrap(int a);
};

void Rva000C95E0::wrap(int a)
{
	if (m_inner)
		m_inner->handle(a);
}
