// Byte-field getter at 0x000C9CF0.
//
//     mov al, byte ptr [ecx+0x296] / ret
//
// Identity is not recovered. The class name is the retail RVA.

class Rva000C9CF0
{
public:
	unsigned char get();
	char m_lead[0x296];
	unsigned char m_value;
};

unsigned char Rva000C9CF0::get()
{
	return m_value;
}
