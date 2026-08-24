// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva007AECC0Item
{
	char m_pad[0x68];
	int m_value;
};

class Rva007AECC0Slot
{
public:
	void set(unsigned int index, int value);

	char m_pad[0x58];
	Rva007AECC0Item *m_items[1];
};

void Rva007AECC0Slot::set(unsigned int index, int value)
{
	Rva007AECC0Item *item = m_items[index];
	if (item)
		item->m_value = value;
}
