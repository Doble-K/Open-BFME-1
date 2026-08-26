// cl: /O2 /Ob0

class Rva00383B90
{
	char m_pad[0x1B0];
	struct Slot
	{
		char rest[0x1C];
	} m_slots[8];

public:
	void *get(int index);
};

void *Rva00383B90::get(int index)
{
	if (index < 0 || index >= 8)
		return 0;
	return &m_slots[index];
}
