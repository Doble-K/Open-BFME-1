// cl: /O2 /Ob0

class GlobalData
{
public:
	char m_pad[0xDBD];
	unsigned char m_DBD;
};

extern GlobalData *TheWritableGlobalData;

class Rva002F08C0
{
public:
	void set(unsigned char value);
};

void Rva002F08C0::set(unsigned char value)
{
	TheWritableGlobalData->m_DBD = value;
}
