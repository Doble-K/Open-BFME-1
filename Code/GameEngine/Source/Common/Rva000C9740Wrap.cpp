// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva000C9740S00
{
public:
	virtual void s00();
};

class Rva000C9740S04 : public Rva000C9740S00
{
public:
	virtual void s04();
};

class Rva000C9740S08 : public Rva000C9740S04
{
public:
	virtual void s08();
};

class Rva000C9740S0C : public Rva000C9740S08
{
public:
	virtual void s0C();
};

class Rva000C9740S10 : public Rva000C9740S0C
{
public:
	virtual void s10();
};

class Rva000C9740S14 : public Rva000C9740S10
{
public:
	virtual void s14();
};

class Rva000C9740S18 : public Rva000C9740S14
{
public:
	virtual void s18();
};

class Rva000C9740S1C : public Rva000C9740S18
{
public:
	virtual void s1C();
};

class Rva000C9740S20 : public Rva000C9740S1C
{
public:
	virtual void s20();
};

class Rva000C9740Pointee : public Rva000C9740S20
{
public:
	virtual void dispatch(int, int);
};

class Rva000C9740
{
	char m_pad[0x220];
	Rva000C9740Pointee *m_pointee;

public:
	void wrap(int a);
};

void Rva000C9740::wrap(int a)
{
	if (m_pointee)
		m_pointee->dispatch(a, 1);
}
