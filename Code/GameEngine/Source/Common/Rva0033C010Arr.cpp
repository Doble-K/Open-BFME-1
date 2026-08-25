// cl: /O2 /Ob0

class Rva0033C010
{
	char m_lead[0x38];
	int *m_arr;

public:
	int get(int i);
};

int Rva0033C010::get(int i)
{
	return m_arr[i * 5];
}
