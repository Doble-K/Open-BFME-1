// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Address-derived reconstruction.  The retail body lazily allocates the
// seven-dword object stored at +0x54 and forwards its argument with a true
// flag.  Names remain descriptive because no trustworthy class identity is
// known.

extern int Gen01083E78;

class Rva001705A0Inner
{
public:
	Rva001705A0Inner();
	void apply( int value, bool enabled );

private:
	int *m_vtable;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
};

inline Rva001705A0Inner::Rva001705A0Inner()
{
	m_vtable = &Gen01083E78;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
}

class Rva001705A0Owner
{
public:
	void setValue( int value );

private:
	char m_pad00[ 0x54 ];
	Rva001705A0Inner *m_inner;
};

void Rva001705A0Owner::setValue( int value )
{
	if ( m_inner == 0 )
		m_inner = new Rva001705A0Inner;
	m_inner->apply( value, true );
}
