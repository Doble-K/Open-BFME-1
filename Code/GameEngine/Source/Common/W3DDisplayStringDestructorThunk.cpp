// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DDisplayString dtor (protected MAE).
// Early vtbl, members @+0x14/+0xe0/+0x1b0, base dtor.

class W3DDisplayStringMemberB
{
public:
	~W3DDisplayStringMemberB();
private:
	unsigned char m_pad[4];
};

class CountUpBuffer
{
public:
	~CountUpBuffer();
private:
	unsigned char m_pad[4];
};

class W3DDisplayStringBase
{
public:
	virtual ~W3DDisplayStringBase();
};

class W3DDisplayString : public W3DDisplayStringBase
{
protected:
	virtual ~W3DDisplayString();
private:
	unsigned char m_gap[0x10];
	W3DDisplayStringMemberB m_a;
	unsigned char m_gap2[0xc8];
	W3DDisplayStringMemberB m_b;
	unsigned char m_gap3[0xcc];
	CountUpBuffer m_c;
};

// ??1W3DDisplayString@@MAE@XZ
W3DDisplayString::~W3DDisplayString()
{
}
