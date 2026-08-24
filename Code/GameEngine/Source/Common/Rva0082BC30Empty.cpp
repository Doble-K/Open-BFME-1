// cl: /Od
// Retail at 0x0082BC30 is an empty void function: push ebp, mov ebp,esp,
// pop ebp, ret.  The owning identity was not recovered.
void Rva0082BC30()
{
}

void rva0082BC40Swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

class Rva0082BFD0Slot
{
public:
	Rva0082BFD0Slot *assignFrom(const int *src);

private:
	int m_value;
};

Rva0082BFD0Slot *Rva0082BFD0Slot::assignFrom(const int *src)
{
	int tmp = *src;
	m_value = tmp;
	return this;
}
