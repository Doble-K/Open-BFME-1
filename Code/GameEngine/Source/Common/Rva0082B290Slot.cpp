// cl: /Od /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva0082B290Slot
{
public:
	Rva0082B290Slot *set(int value);

private:
	int m_value;
};

Rva0082B290Slot *Rva0082B290Slot::set(int value)
{
	m_value = value;
	return this;
}
