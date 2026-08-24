// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: Shadow::setSize, retail 0x001E4250, 117 bytes, from the thunk
// queue -- the name sat on a five-byte thunk and this is the body it jumps to.
//
// Two four-entry pointer arrays at +0x94 and +0xA4 are walked together, one
// index at a time, and every live entry is given the pair of sizes. Then the
// list at +0x538 is walked and the object each node carries at +0x08 gets the
// same pair through slot nine of its table.
//
// The two arrays share one stepping pointer -- the second array's base, with
// the first reached at minus sixteen -- and the count runs down from four,
// which is what a single loop over both gives. The list end is re-read from
// this on every trip, so this is spilled to the frame across the calls.

typedef int Int;
typedef float Real;

class BfmeShadowPart
{
public:
	void bfmeSetSize(Real width, Real height);		// ILT 0x00022D86
};

class BfmeShadowClient
{
public:
	virtual void _bfme_slot0(void) = 0;
	virtual void _bfme_slot1(void) = 0;
	virtual void _bfme_slot2(void) = 0;
	virtual void _bfme_slot3(void) = 0;
	virtual void _bfme_slot4(void) = 0;
	virtual void _bfme_slot5(void) = 0;
	virtual void _bfme_slot6(void) = 0;
	virtual void _bfme_slot7(void) = 0;
	virtual void _bfme_slot8(void) = 0;
	virtual void bfmeSetSize(Real width, Real height) = 0;	// slot 9, vtable+0x24
};

struct BfmeShadowNode
{
	BfmeShadowNode *m_bfmeNext;				// +0x00
	BfmeShadowNode *m_bfmePrev;				// +0x04
	BfmeShadowClient *m_bfmeClient;				// +0x08
};

class Shadow
{
public:
	void setSize(Real width, Real height);

private:
	char m_bfmeHeadA[0x94];
	BfmeShadowPart *m_bfmeFirst[4];				// +0x094
	BfmeShadowPart *m_bfmeSecond[4];			// +0x0A4
	char m_bfmeHeadB[0x538 - 0xB4];
	BfmeShadowNode *m_bfmeClients;				// +0x538
};

// ?setSize@Shadow@@QAEXMM@Z
void Shadow::setSize(Real width, Real height)
{
	Int i;

	for (i = 0; i < 4; ++i)
	{
		if (m_bfmeFirst[i])
			m_bfmeFirst[i]->bfmeSetSize(width, height);

		if (m_bfmeSecond[i])
			m_bfmeSecond[i]->bfmeSetSize(width, height);
	}

	for (BfmeShadowNode *node = m_bfmeClients->m_bfmeNext;
			node != m_bfmeClients;
			node = node->m_bfmeNext)
	{
		// Held in a local: read straight from the node into the test, the
		// compiler lands it in eax and copies it into ecx for the call.
		BfmeShadowClient *client = node->m_bfmeClient;

		if (client)
			client->bfmeSetSize(width, height);
	}
}
