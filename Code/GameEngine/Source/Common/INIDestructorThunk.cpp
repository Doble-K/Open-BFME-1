// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: INI dtor. members @+0x04 and @+0x834.

class Buffer
{
public:
	~Buffer();
private:
	unsigned char m_pad[4];
};

class INIMemberA
{
public:
	~INIMemberA();
private:
	unsigned char m_pad[4];
};

class INI
{
public:
	~INI();
private:
	unsigned char m_gap0[4];
	Buffer m_a; // +0x04
	unsigned char m_gap[0x82c]; // to +0x834
	INIMemberA m_b; // +0x834
};

// ??1INI@@QAE@XZ
INI::~INI()
{
}
