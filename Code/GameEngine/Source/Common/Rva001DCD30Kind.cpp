// cl: /O2 /Ob0

template <int N>
class BitFlags
{
};

class Thing
{
public:
	bool isAnyKindOf(const BitFlags<69> &) const;
};

class Rva001DCD30
{
	char m_lead[8];
	BitFlags<69> m_kindOf;

public:
	int isNotAnyKindOf(const Thing &mask) const;
};

int Rva001DCD30::isNotAnyKindOf(const Thing &mask) const
{
	return !mask.isAnyKindOf(m_kindOf);
}
