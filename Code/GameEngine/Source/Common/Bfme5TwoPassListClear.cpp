// A two-pass list clear.
//
// The list is walked twice: once deleting what every node owns, and once
// freeing the nodes themselves, before the head is pointed back at itself.
// Two passes rather than one is what the two loop heads say, and the second
// re-reads the head member from the object rather than reusing the first
// walk's copy.
//
// The freeing pass advances before it frees, which is what keeps the node in
// the callee-saved register; the deleting pass has no such need and simply
// steps on.

void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

class BfmeOwnedItem
{
public:
	virtual ~BfmeOwnedItem(void);				// slot +0x00
};

struct BfmeOwnNode
{
	BfmeOwnNode *m_bfmeNext;				// +0x00
	BfmeOwnNode *m_bfmePrev;				// +0x04
	BfmeOwnedItem *m_bfmeValue;				// +0x08
};

class Gen_00428020
{
public:
	void bfmeClear(void);

private:
	int m_bfmeHead;						// +0x00
	BfmeOwnNode *m_bfmeList;				// +0x04
};

// ?bfmeClear@Gen_00428020@@QAEXXZ
void Gen_00428020::bfmeClear(void)
{
	BfmeOwnNode *node = m_bfmeList->m_bfmeNext;

	while (node != m_bfmeList)
	{
		delete node->m_bfmeValue;

		node = node->m_bfmeNext;
	}

	BfmeOwnNode *walk = m_bfmeList->m_bfmeNext;

	while (walk != m_bfmeList)
	{
		BfmeOwnNode *current = walk;

		walk = walk->m_bfmeNext;

		bfmeDeallocate(current, sizeof(BfmeOwnNode));
	}

	m_bfmeList->m_bfmeNext = m_bfmeList;
	m_bfmeList->m_bfmePrev = m_bfmeList;
}
