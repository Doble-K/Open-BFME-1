// ?bfmeSkipToNext@Gen_00460da0@@QAEPAVBfmeHashNode@@XZ
// partial score=0.85 date=2026-08-25
// Two 65-byte bodies at 0x00460DA0 and 0x00461480, both of which
// reverse/reloc_names.csv gives the SAME decorated name -- the
// _M_skip_to_next of a hashtable iterator over
// pair<const AsciiString, AudioEventInfo *>. One name cannot claim two
// addresses, and reproducing that six-parameter template mangling exactly
// would take more scaffolding than the bytes justify, so both rows take
// address-derived names and the real one is recorded here and in the notes.
//
// The shape is STLport's: ask the hashtable which bucket the current node's
// value belongs to, then walk forward from there to the first bucket that is
// not empty, and hand back whatever is in it -- null if the walk runs off the
// end.
//
// Two things the bytes fix. The bucket count is computed TWICE, once for the
// call and once for the walk, with the hashtable pointer re-read in between;
// and the comparison that ends the walk is jae, so the bucket index is
// unsigned.

typedef unsigned int UnsignedInt;

class BfmeHashNode
{
public:
	BfmeHashNode *m_bfmeNext;					// +0x00
	char m_bfmeValue[8];						// +0x04
};

class BfmeHashtable
{
public:
	char m_bfmeHead[0x04];
	BfmeHashNode **m_bfmeBucketsStart;				// +0x04
	BfmeHashNode **m_bfmeBucketsFinish;				// +0x08
};

UnsignedInt bfmeBucketNumForKey(const void *value, UnsignedInt bucketCount);	// ILT 0x00012909

class Gen_00460da0
{
public:
	BfmeHashNode *bfmeSkipToNext(void);

private:
	BfmeHashNode *m_bfmeCur;					// +0x00
	BfmeHashtable *m_bfmeHt;					// +0x04
};

class Gen_00461480
{
public:
	BfmeHashNode *bfmeSkipToNext(void);

private:
	BfmeHashNode *m_bfmeCur;					// +0x00
	BfmeHashtable *m_bfmeHt;					// +0x04
};

// ?bfmeSkipToNext@Gen_00460da0@@QAEPAVBfmeHashNode@@XZ
BfmeHashNode *Gen_00460da0::bfmeSkipToNext(void)
{
	UnsignedInt bucket = bfmeBucketNumForKey(&m_bfmeCur->m_bfmeValue,
		(UnsignedInt)(m_bfmeHt->m_bfmeBucketsFinish - m_bfmeHt->m_bfmeBucketsStart));

	UnsignedInt count = (UnsignedInt)(m_bfmeHt->m_bfmeBucketsFinish - m_bfmeHt->m_bfmeBucketsStart);

	BfmeHashNode *node = 0;

	while (node == 0 && ++bucket < count)
		node = m_bfmeHt->m_bfmeBucketsStart[bucket];

	return node;
}

// ?bfmeSkipToNext@Gen_00461480@@QAEPAVBfmeHashNode@@XZ
BfmeHashNode *Gen_00461480::bfmeSkipToNext(void)
{
	UnsignedInt bucket = bfmeBucketNumForKey(&m_bfmeCur->m_bfmeValue,
		(UnsignedInt)(m_bfmeHt->m_bfmeBucketsFinish - m_bfmeHt->m_bfmeBucketsStart));

	UnsignedInt count = (UnsignedInt)(m_bfmeHt->m_bfmeBucketsFinish - m_bfmeHt->m_bfmeBucketsStart);

	BfmeHashNode *node = 0;

	while (node == 0 && ++bucket < count)
		node = m_bfmeHt->m_bfmeBucketsStart[bucket];

	return node;
}
