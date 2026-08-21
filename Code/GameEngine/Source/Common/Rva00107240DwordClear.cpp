// Retail at 0x00107240 writes 0 to the dword at this+0x1468 and callee-cleans
// one four-byte argument. The owning type was not recovered.
class Rva00107240
{
public:
	void apply(int);
	char m_lead[0x1468];
	unsigned int m_val;
};

void Rva00107240::apply(int)
{
	m_val = 0;
}
