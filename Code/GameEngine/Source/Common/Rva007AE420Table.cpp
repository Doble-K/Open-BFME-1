// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned int UnsignedInt;

struct Rva007AE440Value
{
	UnsignedInt m_first;
	UnsignedInt m_second;
	UnsignedInt m_third;
};

struct Rva007AE420Entry
{
	unsigned char m_pad0[0x08];
	Rva007AE440Value m_data;
	unsigned char m_pad14[0x0c];
	float m_value;
};

class Rva007AE420Table
{
public:
	float getValue( UnsignedInt index ) const;
	void getEntry( UnsignedInt index, Rva007AE440Value *value ) const;

private:
	unsigned char m_pad0[0x58];
	Rva007AE420Entry *m_entries[1];
};

float Rva007AE420Table::getValue( UnsignedInt index ) const
{
	return m_entries[index]->m_value;
}

void Rva007AE420Table::getEntry( UnsignedInt index,
	Rva007AE440Value *value ) const
{
	Rva007AE420Entry *entry = m_entries[index];
	*value = entry->m_data;
}
