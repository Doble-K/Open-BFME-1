// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DTreeDrawModuleData dtor.
// Early derived vtbl; Buffers @+0x08/+0x0c/+0x28/+0x48; base vtbl.

class Buffer
{
public:
	~Buffer();
private:
	unsigned char m_pad[4];
};

class W3DTreeDrawModuleDataBase
{
public:
	virtual ~W3DTreeDrawModuleDataBase() {}
private:
	unsigned char m_pad[4];
};

class W3DTreeDrawModuleData : public W3DTreeDrawModuleDataBase
{
public:
	virtual ~W3DTreeDrawModuleData();
private:
	Buffer m_a;
	Buffer m_b;
	unsigned char m_gap1[0x18];
	Buffer m_c;
	unsigned char m_gap2[0x1c];
	Buffer m_d;
};

// ??1W3DTreeDrawModuleData@@UAE@XZ
W3DTreeDrawModuleData::~W3DTreeDrawModuleData()
{
}
