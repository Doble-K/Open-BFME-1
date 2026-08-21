// Byte-field getter at 0x000C9700.
//
//     mov al, byte ptr [ecx+0x29C] / ret
//
// Identity is not recovered. The class name is the retail RVA.

class Rva000C9700
{
public:
	unsigned char get();
	char m_lead[0x29C];
	unsigned char m_value;
};

unsigned char Rva000C9700::get()
{
	return m_value;
}
