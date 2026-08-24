// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva000C9790S00
{
public:
	virtual void s00();
};

class Rva000C9790S04 : public Rva000C9790S00
{
public:
	virtual void s04();
};

class Rva000C9790S08 : public Rva000C9790S04
{
public:
	virtual void s08();
};

class Rva000C9790S0C : public Rva000C9790S08
{
public:
	virtual void s0C();
};

class Rva000C9790S10 : public Rva000C9790S0C
{
public:
	virtual void s10();
};

class Rva000C9790S14 : public Rva000C9790S10
{
public:
	virtual void s14();
};

class Rva000C9790S18 : public Rva000C9790S14
{
public:
	virtual void s18();
};

class Rva000C9790S1C : public Rva000C9790S18
{
public:
	virtual void s1C();
};

class Rva000C9790S20 : public Rva000C9790S1C
{
public:
	virtual void s20();
};

class Rva000C9790S24 : public Rva000C9790S20
{
public:
	virtual void s24();
};

class Rva000C9790Pointee : public Rva000C9790S24
{
public:
	virtual void dispatch(int, int, int);
};

class Rva000C9790
{
	char m_pad[0x220];
	Rva000C9790Pointee *m_pointee;

public:
	void call(int a, int b, int c);
};

void Rva000C9790::call(int a, int b, int c)
{
	if (m_pointee)
		m_pointee->dispatch(a, b, c);
}
