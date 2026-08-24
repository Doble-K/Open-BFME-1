// ?bfmeInsert@Gen_000d07a0@@QAEXABUBfmeSpliceValue@@@Z
// partial score=0.9 date=2026-08-25
// Eleven list splices in two shapes, all allocating a 0x10 node out of the
// shared __node_alloc body and linking it in front of a position node.
//
// The node is next at +0x00, prev at +0x04 and an eight-byte value at +0x08 --
// 0x10 in total. The value is copied as two plain dwords rather than through a
// constructor call, so it is a POD pair, and the null test in front of that
// copy is MSVC's placement-new codegen, not anything the source tests.
//
// The link order is the same in both: next takes the position, prev takes the
// position's prev, that prev's next takes the node, and the position's prev
// takes the node last.
//
// The six 53-byte bodies read the position from this+0x00 and return nothing.
// The five 61-byte ones take the position and the value as arguments and hand
// an iterator back by value -- the hidden return pointer is the first
// argument, which is why they clean twelve bytes and end by writing the node
// through it.

inline void *operator new(unsigned int, void *place)
{
	return place;
}

namespace _STL
{

class __new_alloc
{
public:
	static void *allocate(unsigned int size);			// retail 0x0082E540
};

}

struct BfmeSpliceValue
{
	BfmeSpliceValue(const BfmeSpliceValue &other)
	{
		m_bfmeFirst = other.m_bfmeFirst;
		m_bfmeSecond = other.m_bfmeSecond;
	}

	int m_bfmeFirst;
	int m_bfmeSecond;
};

struct BfmeSpliceNode
{
	BfmeSpliceNode *m_bfmeNext;					// +0x00
	BfmeSpliceNode *m_bfmePrev;					// +0x04
	BfmeSpliceValue m_bfmeValue;					// +0x08
};

struct BfmeSpliceIterator
{
	BfmeSpliceNode *m_bfmeNode;
};

class Gen_000d07a0
{
public:
	void bfmeInsert(const BfmeSpliceValue &value);

private:
	BfmeSpliceNode *m_bfmeNode;					// +0x00
};

class Gen_0010eca0
{
public:
	void bfmeInsert(const BfmeSpliceValue &value);

private:
	BfmeSpliceNode *m_bfmeNode;					// +0x00
};

class Gen_00151b00
{
public:
	void bfmeInsert(const BfmeSpliceValue &value);

private:
	BfmeSpliceNode *m_bfmeNode;					// +0x00
};

class Gen_002512a0
{
public:
	void bfmeInsert(const BfmeSpliceValue &value);

private:
	BfmeSpliceNode *m_bfmeNode;					// +0x00
};

class Gen_002571a0
{
public:
	void bfmeInsert(const BfmeSpliceValue &value);

private:
	BfmeSpliceNode *m_bfmeNode;					// +0x00
};

class Gen_00442820
{
public:
	void bfmeInsert(const BfmeSpliceValue &value);

private:
	BfmeSpliceNode *m_bfmeNode;					// +0x00
};

class Gen_000cf2f0
{
public:
	BfmeSpliceIterator bfmeInsert(BfmeSpliceNode *position, const BfmeSpliceValue &value);
};

class Gen_0010e2d0
{
public:
	BfmeSpliceIterator bfmeInsert(BfmeSpliceNode *position, const BfmeSpliceValue &value);
};

class Gen_00151ab0
{
public:
	BfmeSpliceIterator bfmeInsert(BfmeSpliceNode *position, const BfmeSpliceValue &value);
};

class Gen_00251010
{
public:
	BfmeSpliceIterator bfmeInsert(BfmeSpliceNode *position, const BfmeSpliceValue &value);
};

class Gen_00440480
{
public:
	BfmeSpliceIterator bfmeInsert(BfmeSpliceNode *position, const BfmeSpliceValue &value);
};

// ?bfmeInsert@Gen_000d07a0@@QAEXABUBfmeSpliceValue@@@Z
void Gen_000d07a0::bfmeInsert(const BfmeSpliceValue &value)
{
	BfmeSpliceNode *position = m_bfmeNode;
	BfmeSpliceNode *node = (BfmeSpliceNode *)_STL::__new_alloc::allocate(0x10);

	new (&node->m_bfmeValue) BfmeSpliceValue(value);

	BfmeSpliceNode *previous = position->m_bfmePrev;

	node->m_bfmeNext = position;
	node->m_bfmePrev = previous;
	previous->m_bfmeNext = node;
	position->m_bfmePrev = node;
}

// ?bfmeInsert@Gen_0010eca0@@QAEXABUBfmeSpliceValue@@@Z
void Gen_0010eca0::bfmeInsert(const BfmeSpliceValue &value)
{
	BfmeSpliceNode *position = m_bfmeNode;
	BfmeSpliceNode *node = (BfmeSpliceNode *)_STL::__new_alloc::allocate(0x10);

	new (&node->m_bfmeValue) BfmeSpliceValue(value);

	BfmeSpliceNode *previous = position->m_bfmePrev;

	node->m_bfmeNext = position;
	node->m_bfmePrev = previous;
	previous->m_bfmeNext = node;
	position->m_bfmePrev = node;
}

// ?bfmeInsert@Gen_00151b00@@QAEXABUBfmeSpliceValue@@@Z
void Gen_00151b00::bfmeInsert(const BfmeSpliceValue &value)
{
	BfmeSpliceNode *position = m_bfmeNode;
	BfmeSpliceNode *node = (BfmeSpliceNode *)_STL::__new_alloc::allocate(0x10);

	new (&node->m_bfmeValue) BfmeSpliceValue(value);

	BfmeSpliceNode *previous = position->m_bfmePrev;

	node->m_bfmeNext = position;
	node->m_bfmePrev = previous;
	previous->m_bfmeNext = node;
	position->m_bfmePrev = node;
}

// ?bfmeInsert@Gen_002512a0@@QAEXABUBfmeSpliceValue@@@Z
void Gen_002512a0::bfmeInsert(const BfmeSpliceValue &value)
{
	BfmeSpliceNode *position = m_bfmeNode;
	BfmeSpliceNode *node = (BfmeSpliceNode *)_STL::__new_alloc::allocate(0x10);

	new (&node->m_bfmeValue) BfmeSpliceValue(value);

	BfmeSpliceNode *previous = position->m_bfmePrev;

	node->m_bfmeNext = position;
	node->m_bfmePrev = previous;
	previous->m_bfmeNext = node;
	position->m_bfmePrev = node;
}

// ?bfmeInsert@Gen_002571a0@@QAEXABUBfmeSpliceValue@@@Z
void Gen_002571a0::bfmeInsert(const BfmeSpliceValue &value)
{
	BfmeSpliceNode *position = m_bfmeNode;
	BfmeSpliceNode *node = (BfmeSpliceNode *)_STL::__new_alloc::allocate(0x10);

	new (&node->m_bfmeValue) BfmeSpliceValue(value);

	BfmeSpliceNode *previous = position->m_bfmePrev;

	node->m_bfmeNext = position;
	node->m_bfmePrev = previous;
	previous->m_bfmeNext = node;
	position->m_bfmePrev = node;
}

// ?bfmeInsert@Gen_00442820@@QAEXABUBfmeSpliceValue@@@Z
void Gen_00442820::bfmeInsert(const BfmeSpliceValue &value)
{
	BfmeSpliceNode *position = m_bfmeNode;
	BfmeSpliceNode *node = (BfmeSpliceNode *)_STL::__new_alloc::allocate(0x10);

	new (&node->m_bfmeValue) BfmeSpliceValue(value);

	BfmeSpliceNode *previous = position->m_bfmePrev;

	node->m_bfmeNext = position;
	node->m_bfmePrev = previous;
	previous->m_bfmeNext = node;
	position->m_bfmePrev = node;
}

// ?bfmeInsert@Gen_000cf2f0@@QAE?AUBfmeSpliceIterator@@PAUBfmeSpliceNode@@ABUBfmeSpliceValue@@@Z
BfmeSpliceIterator Gen_000cf2f0::bfmeInsert(BfmeSpliceNode *position, const BfmeSpliceValue &value)
{
	BfmeSpliceNode *node = (BfmeSpliceNode *)_STL::__new_alloc::allocate(0x10);

	new (&node->m_bfmeValue) BfmeSpliceValue(value);

	BfmeSpliceNode *previous = position->m_bfmePrev;

	node->m_bfmeNext = position;
	node->m_bfmePrev = previous;
	previous->m_bfmeNext = node;
	position->m_bfmePrev = node;

	BfmeSpliceIterator result;

	result.m_bfmeNode = node;

	return result;
}

// ?bfmeInsert@Gen_0010e2d0@@QAE?AUBfmeSpliceIterator@@PAUBfmeSpliceNode@@ABUBfmeSpliceValue@@@Z
BfmeSpliceIterator Gen_0010e2d0::bfmeInsert(BfmeSpliceNode *position, const BfmeSpliceValue &value)
{
	BfmeSpliceNode *node = (BfmeSpliceNode *)_STL::__new_alloc::allocate(0x10);

	new (&node->m_bfmeValue) BfmeSpliceValue(value);

	BfmeSpliceNode *previous = position->m_bfmePrev;

	node->m_bfmeNext = position;
	node->m_bfmePrev = previous;
	previous->m_bfmeNext = node;
	position->m_bfmePrev = node;

	BfmeSpliceIterator result;

	result.m_bfmeNode = node;

	return result;
}

// ?bfmeInsert@Gen_00151ab0@@QAE?AUBfmeSpliceIterator@@PAUBfmeSpliceNode@@ABUBfmeSpliceValue@@@Z
BfmeSpliceIterator Gen_00151ab0::bfmeInsert(BfmeSpliceNode *position, const BfmeSpliceValue &value)
{
	BfmeSpliceNode *node = (BfmeSpliceNode *)_STL::__new_alloc::allocate(0x10);

	new (&node->m_bfmeValue) BfmeSpliceValue(value);

	BfmeSpliceNode *previous = position->m_bfmePrev;

	node->m_bfmeNext = position;
	node->m_bfmePrev = previous;
	previous->m_bfmeNext = node;
	position->m_bfmePrev = node;

	BfmeSpliceIterator result;

	result.m_bfmeNode = node;

	return result;
}

// ?bfmeInsert@Gen_00251010@@QAE?AUBfmeSpliceIterator@@PAUBfmeSpliceNode@@ABUBfmeSpliceValue@@@Z
BfmeSpliceIterator Gen_00251010::bfmeInsert(BfmeSpliceNode *position, const BfmeSpliceValue &value)
{
	BfmeSpliceNode *node = (BfmeSpliceNode *)_STL::__new_alloc::allocate(0x10);

	new (&node->m_bfmeValue) BfmeSpliceValue(value);

	BfmeSpliceNode *previous = position->m_bfmePrev;

	node->m_bfmeNext = position;
	node->m_bfmePrev = previous;
	previous->m_bfmeNext = node;
	position->m_bfmePrev = node;

	BfmeSpliceIterator result;

	result.m_bfmeNode = node;

	return result;
}

// ?bfmeInsert@Gen_00440480@@QAE?AUBfmeSpliceIterator@@PAUBfmeSpliceNode@@ABUBfmeSpliceValue@@@Z
BfmeSpliceIterator Gen_00440480::bfmeInsert(BfmeSpliceNode *position, const BfmeSpliceValue &value)
{
	BfmeSpliceNode *node = (BfmeSpliceNode *)_STL::__new_alloc::allocate(0x10);

	new (&node->m_bfmeValue) BfmeSpliceValue(value);

	BfmeSpliceNode *previous = position->m_bfmePrev;

	node->m_bfmeNext = position;
	node->m_bfmePrev = previous;
	previous->m_bfmeNext = node;
	position->m_bfmePrev = node;

	BfmeSpliceIterator result;

	result.m_bfmeNode = node;

	return result;
}
