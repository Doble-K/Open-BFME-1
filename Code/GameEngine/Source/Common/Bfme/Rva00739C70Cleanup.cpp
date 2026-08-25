// 23-byte and 32-byte cleanup routines, and 62-byte reset routine

class TextureBaseClass
{
public:
	void Release_Ref();
};

class VirtualReleaser00739E00
{
public:
	virtual void v0();
	virtual void v1();
	virtual unsigned long __stdcall Release();
};

class Member0C00739C70
{
public:
	VirtualReleaser00739E00 *m_obj;

	void clear();
	void reset()
	{
		if ( m_obj )
		{
			m_obj->Release();
			m_obj = 0;
		}
	}
};

class Rva00739C70
{
public:
	void cleanup();
	void reset();

	char             m_pad0[ 0x8 ];
	TextureBaseClass *m_ptr08;
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

void Rva00739C70::reset()
{
	cleanup();
	if ( m_ptr08 )
	{
		m_ptr08->Release_Ref();
		m_ptr08 = 0;
	}
	m_member0c.reset();
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
