// ?bfmeFind@BfmeHashBucketTable@@QBEPAXI@Z
// partial score=0.6 date=2026-08-24
// cl: /DNDEBUG /MD /EHs-c-

// Retail 0x00786BD0, 70 bytes, carried only a machine byte-dump row. Five
// names are pinned at the address -- anyIntersectionWith and countIntersection
// on BitFlags, Drawable::draw, MemoryPool::freeBlock -- and none of them can be
// this body, which divides, indexes a bucket array and walks a chain. They are
// identical-code-folding aliases on the ILT.
//
// What it is: a hash lookup. The bucket array is a pointer pair at +0x0C and
// +0x10, its length comes from the difference shifted right by two, and the
// division is unsigned (xor edx,edx ahead of div) so the index is key modulo
// bucket count. Chain nodes are next at +0x00, key at +0x04, value at +0x08.
//
// The doubled exit is the shape of a find whose result is then tested: the
// walk falls out with a null node down one path and the match down the other,
// and the caller's own null check is the redundant test on the matched node.

typedef unsigned int UnsignedInt;

class BfmeHashNode
{
public:
	BfmeHashNode *m_bfmeNext;					// +0x00
	UnsignedInt m_bfmeKey;						// +0x04
	void *m_bfmeValue;						// +0x08
};

class BfmeHashBucketTable
{
public:
	void *bfmeFind(UnsignedInt key) const;

private:
	BfmeHashNode *bfmeFindNode(UnsignedInt key) const
	{
		BfmeHashNode *node = m_bfmeBucketsStart[key % (UnsignedInt)(m_bfmeBucketsFinish - m_bfmeBucketsStart)];

		while (node)
		{
			if (node->m_bfmeKey == key)
				return node;

			node = node->m_bfmeNext;
		}

		return 0;
	}

	char m_bfmeHead[0x0C];
	BfmeHashNode **m_bfmeBucketsStart;				// +0x0C
	BfmeHashNode **m_bfmeBucketsFinish;				// +0x10
};

// ?bfmeFind@BfmeHashBucketTable@@QBEPAXI@Z
void *BfmeHashBucketTable::bfmeFind(UnsignedInt key) const
{
	BfmeHashNode *node = bfmeFindNode(key);

	return node ? node->m_bfmeValue : 0;
}
