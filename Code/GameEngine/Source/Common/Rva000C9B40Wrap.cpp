// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Gen0004AFAC
{
public:
	void handle(int a);
};

class Rva000C9B40
{
	char m_pad[0x67C];
	Gen0004AFAC *m_inner;

public:
	void wrap(int a);
};

void Rva000C9B40::wrap(int a)
{
	if (m_inner)
		m_inner->handle(a);
}
