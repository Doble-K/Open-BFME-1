// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: MetaMapRec dtor. dual CountUpBuffer @+0x1c/+0x20.

class CountUpBuffer
{
public:
	~CountUpBuffer();
private:
	unsigned char m_pad[4];
};

class MetaMapRec
{
public:
	~MetaMapRec();
private:
	unsigned char m_gap[0x1c];
	CountUpBuffer m_a;
	CountUpBuffer m_b;
};

// ??1MetaMapRec@@QAE@XZ
MetaMapRec::~MetaMapRec()
{
}
