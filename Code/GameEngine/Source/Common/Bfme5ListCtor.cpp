// A list-building constructor.
//
// The list member builds itself first -- null the sentinel pointer, allocate
// twelve bytes, self-link the block through the returned pointer and only then
// store it -- and the body that follows nulls a pointer, clears the list it
// just built, and sets two floats to one.
//
// Clearing a list that was constructed empty is dead work, but it is what the
// source says: the walk, the two self-links and every re-read of the sentinel
// member are all there. The unwind frame and the state going to zero exist
// because the list member has a destructor.

void *bfmeAllocNode(unsigned int bytes);			// retail 0x0082E540
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

struct BfmeCtorNode
{
	BfmeCtorNode *m_bfmeNext;				// +0x00
	BfmeCtorNode *m_bfmePrev;				// +0x04
	void *m_bfmeValue;					// +0x08
};

class BfmeCtorList
{
public:
	BfmeCtorList(void)
	{
		m_bfmeNode = 0;

		BfmeCtorNode *node = (BfmeCtorNode *)bfmeAllocNode(sizeof(BfmeCtorNode));

		node->m_bfmeNext = node;
		node->m_bfmePrev = node;

		m_bfmeNode = node;
	}

	~BfmeCtorList(void);

	void bfmeClear(void)
	{
		BfmeCtorNode *node = m_bfmeNode->m_bfmeNext;

		while (node != m_bfmeNode)
		{
			BfmeCtorNode *current = node;

			node = node->m_bfmeNext;

			bfmeDeallocate(current, sizeof(BfmeCtorNode));
		}

		m_bfmeNode->m_bfmeNext = m_bfmeNode;
		m_bfmeNode->m_bfmePrev = m_bfmeNode;
	}

	BfmeCtorNode *m_bfmeNode;				// +0x00
};

class Gen_004ADC80
{
public:
	Gen_004ADC80(void);

private:
	void *m_bfmeFirst;					// +0x00
	float m_bfmeScaleA;					// +0x04
	float m_bfmeScaleB;					// +0x08
	BfmeCtorList m_bfmeList;				// +0x0C
};

// ??0Gen_004ADC80@@QAE@XZ
Gen_004ADC80::Gen_004ADC80(void)
{
	m_bfmeFirst = 0;

	m_bfmeList.bfmeClear();

	m_bfmeScaleB = 1.0f;
	m_bfmeScaleA = 1.0f;
}
