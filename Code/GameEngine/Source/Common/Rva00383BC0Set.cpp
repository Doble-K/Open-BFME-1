// cl: /O2 /Ob0

class Rva00383BC0
{
	char m_pad[0x3C];
	int m_3C;
	char m_rest[0x1B0 - 0x40];
	struct Slot
	{
		int a;
		int b;
		char rest[0x14];
	} m_slots[8];

public:
	void set(int index, int value);
};

void Rva00383BC0::set(int index, int value)
{
	if (index < 0 || index >= 8)
		return;
	m_slots[index].a = value;
	m_slots[index].b = m_3C;
}
