// cl: /O2 /Ob0

class Rva0033B310
{
	char m_lead[0x0C];
	int *m_arr;

public:
	int get(int i);
};

int Rva0033B310::get(int i)
{
	return m_arr[i * 5];
}
