// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Delete every element, clear the vector, then let the member and the base tear
// themselves down.
//
// The same shape as SpecialPowerStore with one difference visible in a single
// instruction: the comparisons here are jle and jl rather than jbe and jb, so
// the loop is signed and the size is compared as an int. The first test is the
// compiler's signed form of dividing the byte span by four -- test against
// 0xFFFFFFFC masks the low two bits off before checking the sign.
//
// The clear() is the degenerate erase(begin(), end()) again: comparing finish
// with itself, and a branch that can never be taken.
#include <vector>

class RankInfo
{
public:
	virtual ~RankInfo();
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	int m_04;
};

class RankInfoStore : public SubsystemInterface
{
public:
	virtual ~RankInfoStore();

private:
	std::vector<RankInfo *> m_ranks;
};

// ??1RankInfoStore@@UAE@XZ
RankInfoStore::~RankInfoStore()
{
	for (int i = 0; i < (int)m_ranks.size(); i++) {
		delete m_ranks[i];
	}

	m_ranks.clear();
}
