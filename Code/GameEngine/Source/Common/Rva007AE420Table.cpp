// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned int UnsignedInt;

struct Rva007AE420Entry
{
	unsigned char m_pad0[0x20];
	float m_value;
};

class Rva007AE420Table
{
public:
	float getValue( UnsignedInt index ) const;

private:
	unsigned char m_pad0[0x58];
	Rva007AE420Entry *m_entries[1];
};

float Rva007AE420Table::getValue( UnsignedInt index ) const
{
	return m_entries[index]->m_value;
}
