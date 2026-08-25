// 23-byte and 32-byte cleanup routines, 62-byte reset, and 109-byte update
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
	TextureBaseClass *methodA( int arg, int a, int b, int c, int d );
	TextureBaseClass *methodB( int arg, int a );
};

class Rva00739C70
{
public:
	void cleanup();
	void reset();
	TextureBaseClass *update( int arg );

	int               m_int0;
	int               m_int4;
	TextureBaseClass *m_ptr08;
	Member0C00739C70  m_member0c;
	int               m_flags;
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

TextureBaseClass *Rva00739C70::update( int arg )
{
	TextureBaseClass *result = 0;
	if ( m_flags & 1 )
	{
		m_member0c.clear();
		m_flags &= ~1;
	}
	if ( m_member0c.m_obj )
	{
		if ( !( m_flags & 0xC ) )
		{
			result = m_member0c.methodA( arg, 0, 0, m_int0, m_int4 );
		}
		else
		{
			result = m_member0c.methodB( arg, 1 );
		}
		m_flags |= 1;
	}
	return result;
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
