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

class Rva001DCCA0
{
	char m_lead[8];
	BitFlags<69> m_kindOf;

public:
	bool isAnyKindOf(const Thing &mask) const;
};

bool Rva001DCCA0::isAnyKindOf(const Thing &mask) const
{
	return mask.isAnyKindOf(m_kindOf);
}
