// cl: /O2 /Ob0

class BfmeSubB
{
public:
	BfmeSubB(const BfmeSubB &other);

private:
	void *m_item;
};

struct Pod12
{
	int a;
	int b;
	int c;
};

class Rva0008E470
{
	BfmeSubB m_00;
	Pod12 m_04;
	int m_10;
	Pod12 m_14;
	int m_20;

public:
	Rva0008E470(const Rva0008E470 &other);
};

Rva0008E470::Rva0008E470(const Rva0008E470 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_10(other.m_10)
	, m_14(other.m_14)
	, m_20(other.m_20)
{
}
