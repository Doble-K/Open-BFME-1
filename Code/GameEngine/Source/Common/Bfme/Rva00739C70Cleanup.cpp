// 23-byte and 32-byte cleanup routines

class Member0C00739C70
{
public:
	void clear();
};

class Rva00739C70
{
public:
	void cleanup();

	char             m_pad0[ 0xC ];
	Member0C00739C70 m_member0c;
	int              m_flags;
};

void Rva00739C70::cleanup()
{
	if ( m_flags & 1 )
	{
		m_member0c.clear();
		m_flags &= ~1;
	}
}

class Owner00739C90
{
public:
	void cleanup();

	char         m_pad0[ 0x28 ];
	bool         m_dirty28;
	char         m_pad29[ 0x1B ];
	Rva00739C70 *m_subObject;
};

void Owner00739C90::cleanup()
{
	m_subObject->cleanup();
	m_dirty28 = true;
}
