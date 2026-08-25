// 24-byte setter and 15-byte subobject virtual tail-call

class SubObject0073B9A0
{
public:
	virtual void v0();
	virtual void handle();
};

class Rva0073B8C0
{
public:
	void set( int a, int b );
	void go();

	char              m_pad00[ 0x60 ];
	int               m_field60;
	int               m_field64;
	char              m_pad68[ 0x215 ];
	bool              m_flag27D;
	char              m_pad27E[ 0x223A ];
	SubObject0073B9A0 m_subObject;
};

void Rva0073B8C0::set( int a, int b )
{
	m_field60 = a;
	m_field64 = b;
	m_flag27D = true;
}

void Rva0073B8C0::go()
{
	m_subObject.handle();
}
