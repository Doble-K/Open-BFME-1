// ?bfmeInsertUnique@Gen_0008FAB0@@QAE?AUBfmeInsertResultA@@PBUBfmeHashValue@@@Z
// partial score=0.95 date=2026-08-25
// Six hash-table unique inserts: 0x0008FAB0, 0x005A82F0, 0x006A0A10,
// 0x006A0BB0, 0x006A0D50 and 0x00852760.
//
// The bucket index is an unsigned div of the key by (finish - start) >> 2, so
// the bucket array holds pointers and the modulus is unsigned even though the
// count is computed with a signed shift. The chain walk compares the value's
// FIRST dword, so the key is the first member of the value, and the node is
// twelve bytes: a next pointer and an eight-byte value.
//
// The answer is a nine-byte record returned through a hidden pointer -- node,
// table, flag -- which is why the frame cleans eight bytes for two arguments.
// The new node has its next cleared BEFORE the value is constructed and set to
// the old chain head afterwards, and the bucket array is re-read for the
// store, since the construct call could have touched it.

void *bfmeAllocNode(unsigned int bytes);			// retail 0x0082E540

struct BfmeHashValue
{
	unsigned int m_bfmeKey;					// +0x00
	int m_bfmeSecond;					// +0x04
};

struct BfmeHashNode
{
	BfmeHashNode *m_bfmeNext;				// +0x00
	BfmeHashValue m_bfmeValue;				// +0x04
};


void bfmeConstructA(BfmeHashValue *slot, const BfmeHashValue *source);	// 0x0003BAB1

void bfmeConstructB(BfmeHashValue *slot, const BfmeHashValue *source);	// 0x000079A0

void bfmeConstructC(BfmeHashValue *slot, const BfmeHashValue *source);	// 0x00001AB9

void bfmeConstructD(BfmeHashValue *slot, const BfmeHashValue *source);	// 0x0002C098

void bfmeConstructE(BfmeHashValue *slot, const BfmeHashValue *source);	// 0x0001E696

void bfmeConstructF(BfmeHashValue *slot, const BfmeHashValue *source);	// 0x00852240

class Gen_0008FAB0;

struct BfmeInsertResultA
{
	BfmeInsertResultA(BfmeHashNode *node, Gen_0008FAB0 *table, bool inserted)
	{
		m_bfmeNode = node;
		m_bfmeTable = table;
		m_bfmeInserted = inserted;
	}

	BfmeHashNode *m_bfmeNode;				// +0x00
	Gen_0008FAB0 *m_bfmeTable;					// +0x04
	bool m_bfmeInserted;					// +0x08
};

class Gen_0008FAB0
{
public:
	BfmeInsertResultA bfmeInsertUnique(const BfmeHashValue *value);

private:
	char m_bfmeHead[4];
	BfmeHashNode **m_bfmeBucketsStart;			// +0x04
	BfmeHashNode **m_bfmeBucketsFinish;			// +0x08
	char m_bfmeGap[4];
	int m_bfmeCount;					// +0x10
};

class Gen_005A82F0;

struct BfmeInsertResultB
{
	BfmeInsertResultB(BfmeHashNode *node, Gen_005A82F0 *table, bool inserted)
	{
		m_bfmeNode = node;
		m_bfmeTable = table;
		m_bfmeInserted = inserted;
	}

	BfmeHashNode *m_bfmeNode;				// +0x00
	Gen_005A82F0 *m_bfmeTable;					// +0x04
	bool m_bfmeInserted;					// +0x08
};

class Gen_005A82F0
{
public:
	BfmeInsertResultB bfmeInsertUnique(const BfmeHashValue *value);

private:
	char m_bfmeHead[4];
	BfmeHashNode **m_bfmeBucketsStart;			// +0x04
	BfmeHashNode **m_bfmeBucketsFinish;			// +0x08
	char m_bfmeGap[4];
	int m_bfmeCount;					// +0x10
};

class Gen_006A0A10;

struct BfmeInsertResultC
{
	BfmeInsertResultC(BfmeHashNode *node, Gen_006A0A10 *table, bool inserted)
	{
		m_bfmeNode = node;
		m_bfmeTable = table;
		m_bfmeInserted = inserted;
	}

	BfmeHashNode *m_bfmeNode;				// +0x00
	Gen_006A0A10 *m_bfmeTable;					// +0x04
	bool m_bfmeInserted;					// +0x08
};

class Gen_006A0A10
{
public:
	BfmeInsertResultC bfmeInsertUnique(const BfmeHashValue *value);

private:
	char m_bfmeHead[4];
	BfmeHashNode **m_bfmeBucketsStart;			// +0x04
	BfmeHashNode **m_bfmeBucketsFinish;			// +0x08
	char m_bfmeGap[4];
	int m_bfmeCount;					// +0x10
};

class Gen_006A0BB0;

struct BfmeInsertResultD
{
	BfmeInsertResultD(BfmeHashNode *node, Gen_006A0BB0 *table, bool inserted)
	{
		m_bfmeNode = node;
		m_bfmeTable = table;
		m_bfmeInserted = inserted;
	}

	BfmeHashNode *m_bfmeNode;				// +0x00
	Gen_006A0BB0 *m_bfmeTable;					// +0x04
	bool m_bfmeInserted;					// +0x08
};

class Gen_006A0BB0
{
public:
	BfmeInsertResultD bfmeInsertUnique(const BfmeHashValue *value);

private:
	char m_bfmeHead[4];
	BfmeHashNode **m_bfmeBucketsStart;			// +0x04
	BfmeHashNode **m_bfmeBucketsFinish;			// +0x08
	char m_bfmeGap[4];
	int m_bfmeCount;					// +0x10
};

class Gen_006A0D50;

struct BfmeInsertResultE
{
	BfmeInsertResultE(BfmeHashNode *node, Gen_006A0D50 *table, bool inserted)
	{
		m_bfmeNode = node;
		m_bfmeTable = table;
		m_bfmeInserted = inserted;
	}

	BfmeHashNode *m_bfmeNode;				// +0x00
	Gen_006A0D50 *m_bfmeTable;					// +0x04
	bool m_bfmeInserted;					// +0x08
};

class Gen_006A0D50
{
public:
	BfmeInsertResultE bfmeInsertUnique(const BfmeHashValue *value);

private:
	char m_bfmeHead[4];
	BfmeHashNode **m_bfmeBucketsStart;			// +0x04
	BfmeHashNode **m_bfmeBucketsFinish;			// +0x08
	char m_bfmeGap[4];
	int m_bfmeCount;					// +0x10
};

class Gen_00852760;

struct BfmeInsertResultF
{
	BfmeInsertResultF(BfmeHashNode *node, Gen_00852760 *table, bool inserted)
	{
		m_bfmeNode = node;
		m_bfmeTable = table;
		m_bfmeInserted = inserted;
	}

	BfmeHashNode *m_bfmeNode;				// +0x00
	Gen_00852760 *m_bfmeTable;					// +0x04
	bool m_bfmeInserted;					// +0x08
};

class Gen_00852760
{
public:
	BfmeInsertResultF bfmeInsertUnique(const BfmeHashValue *value);

private:
	char m_bfmeHead[4];
	BfmeHashNode **m_bfmeBucketsStart;			// +0x04
	BfmeHashNode **m_bfmeBucketsFinish;			// +0x08
	char m_bfmeGap[4];
	int m_bfmeCount;					// +0x10
};

// ?bfmeInsertUnique@Gen_0008FAB0@@QAE?AUBfmeInsertResultA@@PBUBfmeHashValue@@@Z
BfmeInsertResultA Gen_0008FAB0::bfmeInsertUnique(const BfmeHashValue *value)
{
	unsigned int key = value->m_bfmeKey;
	BfmeHashNode **buckets = m_bfmeBucketsStart;
	unsigned int index = key % (unsigned int)(m_bfmeBucketsFinish - buckets);
	BfmeHashNode *first = buckets[index];

	for (BfmeHashNode *node = first; node; node = node->m_bfmeNext)
	{
		if (node->m_bfmeValue.m_bfmeKey == key)
			return BfmeInsertResultA(node, this, false);
	}

	BfmeHashNode *created = (BfmeHashNode *)bfmeAllocNode(sizeof(BfmeHashNode));

	created->m_bfmeNext = 0;
	bfmeConstructA(&created->m_bfmeValue, value);
	created->m_bfmeNext = first;
	m_bfmeBucketsStart[index] = created;
	++m_bfmeCount;

	return BfmeInsertResultA(created, this, true);
}

// ?bfmeInsertUnique@Gen_005A82F0@@QAE?AUBfmeInsertResultB@@PBUBfmeHashValue@@@Z
BfmeInsertResultB Gen_005A82F0::bfmeInsertUnique(const BfmeHashValue *value)
{
	unsigned int key = value->m_bfmeKey;
	BfmeHashNode **buckets = m_bfmeBucketsStart;
	unsigned int index = key % (unsigned int)(m_bfmeBucketsFinish - buckets);
	BfmeHashNode *first = buckets[index];

	for (BfmeHashNode *node = first; node; node = node->m_bfmeNext)
	{
		if (node->m_bfmeValue.m_bfmeKey == key)
			return BfmeInsertResultB(node, this, false);
	}

	BfmeHashNode *created = (BfmeHashNode *)bfmeAllocNode(sizeof(BfmeHashNode));

	created->m_bfmeNext = 0;
	bfmeConstructB(&created->m_bfmeValue, value);
	created->m_bfmeNext = first;
	m_bfmeBucketsStart[index] = created;
	++m_bfmeCount;

	return BfmeInsertResultB(created, this, true);
}

// ?bfmeInsertUnique@Gen_006A0A10@@QAE?AUBfmeInsertResultC@@PBUBfmeHashValue@@@Z
BfmeInsertResultC Gen_006A0A10::bfmeInsertUnique(const BfmeHashValue *value)
{
	unsigned int key = value->m_bfmeKey;
	BfmeHashNode **buckets = m_bfmeBucketsStart;
	unsigned int index = key % (unsigned int)(m_bfmeBucketsFinish - buckets);
	BfmeHashNode *first = buckets[index];

	for (BfmeHashNode *node = first; node; node = node->m_bfmeNext)
	{
		if (node->m_bfmeValue.m_bfmeKey == key)
			return BfmeInsertResultC(node, this, false);
	}

	BfmeHashNode *created = (BfmeHashNode *)bfmeAllocNode(sizeof(BfmeHashNode));

	created->m_bfmeNext = 0;
	bfmeConstructC(&created->m_bfmeValue, value);
	created->m_bfmeNext = first;
	m_bfmeBucketsStart[index] = created;
	++m_bfmeCount;

	return BfmeInsertResultC(created, this, true);
}

// ?bfmeInsertUnique@Gen_006A0BB0@@QAE?AUBfmeInsertResultD@@PBUBfmeHashValue@@@Z
BfmeInsertResultD Gen_006A0BB0::bfmeInsertUnique(const BfmeHashValue *value)
{
	unsigned int key = value->m_bfmeKey;
	BfmeHashNode **buckets = m_bfmeBucketsStart;
	unsigned int index = key % (unsigned int)(m_bfmeBucketsFinish - buckets);
	BfmeHashNode *first = buckets[index];

	for (BfmeHashNode *node = first; node; node = node->m_bfmeNext)
	{
		if (node->m_bfmeValue.m_bfmeKey == key)
			return BfmeInsertResultD(node, this, false);
	}

	BfmeHashNode *created = (BfmeHashNode *)bfmeAllocNode(sizeof(BfmeHashNode));

	created->m_bfmeNext = 0;
	bfmeConstructD(&created->m_bfmeValue, value);
	created->m_bfmeNext = first;
	m_bfmeBucketsStart[index] = created;
	++m_bfmeCount;

	return BfmeInsertResultD(created, this, true);
}

// ?bfmeInsertUnique@Gen_006A0D50@@QAE?AUBfmeInsertResultE@@PBUBfmeHashValue@@@Z
BfmeInsertResultE Gen_006A0D50::bfmeInsertUnique(const BfmeHashValue *value)
{
	unsigned int key = value->m_bfmeKey;
	BfmeHashNode **buckets = m_bfmeBucketsStart;
	unsigned int index = key % (unsigned int)(m_bfmeBucketsFinish - buckets);
	BfmeHashNode *first = buckets[index];

	for (BfmeHashNode *node = first; node; node = node->m_bfmeNext)
	{
		if (node->m_bfmeValue.m_bfmeKey == key)
			return BfmeInsertResultE(node, this, false);
	}

	BfmeHashNode *created = (BfmeHashNode *)bfmeAllocNode(sizeof(BfmeHashNode));

	created->m_bfmeNext = 0;
	bfmeConstructE(&created->m_bfmeValue, value);
	created->m_bfmeNext = first;
	m_bfmeBucketsStart[index] = created;
	++m_bfmeCount;

	return BfmeInsertResultE(created, this, true);
}

// ?bfmeInsertUnique@Gen_00852760@@QAE?AUBfmeInsertResultF@@PBUBfmeHashValue@@@Z
BfmeInsertResultF Gen_00852760::bfmeInsertUnique(const BfmeHashValue *value)
{
	unsigned int key = value->m_bfmeKey;
	BfmeHashNode **buckets = m_bfmeBucketsStart;
	unsigned int index = key % (unsigned int)(m_bfmeBucketsFinish - buckets);
	BfmeHashNode *first = buckets[index];

	for (BfmeHashNode *node = first; node; node = node->m_bfmeNext)
	{
		if (node->m_bfmeValue.m_bfmeKey == key)
			return BfmeInsertResultF(node, this, false);
	}

	BfmeHashNode *created = (BfmeHashNode *)bfmeAllocNode(sizeof(BfmeHashNode));

	created->m_bfmeNext = 0;
	bfmeConstructF(&created->m_bfmeValue, value);
	created->m_bfmeNext = first;
	m_bfmeBucketsStart[index] = created;
	++m_bfmeCount;

	return BfmeInsertResultF(created, this, true);
}
