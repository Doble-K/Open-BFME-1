// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva000C95A0Pointee
{
public:
	char m_lead[0x1C];
	int m_value;
};

class Rva000C95A0
{
	char m_lead[0x220];
	Rva000C95A0Pointee *m_pointee;

public:
	void set(int value);
};

void Rva000C95A0::set(int value)
{
	if (m_pointee)
		m_pointee->m_value = value;
}
