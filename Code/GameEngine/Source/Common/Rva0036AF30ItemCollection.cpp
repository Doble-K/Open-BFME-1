extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Rva00367DC0Pair
{
	unsigned int m_key;
	unsigned int m_value;
};

class Rva00367DC0PairRange
{
public:
	bool find(unsigned int key, unsigned int *value) const;

private:
	Rva00367DC0Pair *m_first;
	Rva00367DC0Pair *m_last;
};

class Rva0036AF30Item
{
public:
	Rva00367DC0PairRange m_pairs;
	char m_unreconstructed08[ 0x0C ];
	int m_key;
	int m_value;
};

class Rva0036AF30ItemRange
{
public:
	unsigned int size(void) const { return m_end - m_begin; }
	Rva0036AF30Item *operator[](int index) const { return m_begin[index]; }

	Rva0036AF30Item **m_begin;
	Rva0036AF30Item **m_end;
};

class Rva0036AF30ItemCollection
{
public:
	char m_unreconstructed[ 8 ];
	Rva0036AF30ItemRange m_items;

	int indexOf(int key) const;
	int valueAt(int index) const;
	bool findPairAt(int index, unsigned int key, unsigned int *value) const;
};

int Rva0036AF30ItemCollection::indexOf(int key) const
{
	Rva0036AF30Item **cursor = m_items.m_begin;
	Rva0036AF30Item **end = m_items.m_end;
	int index = 0;
	while( cursor != end )
	{
		if( (*cursor)->m_key == key )
			return index;
		++cursor;
		++index;
	}
	return -1;
}

// @?indexOf@Rva0036AF30ItemCollection@@QBEHH@Z 0x0036AF30

int Rva0036AF30ItemCollection::valueAt(int index) const
{
	if( index < 0 || (unsigned int)index > m_items.size() - 1 )
		return 0;

	Rva0036AF30Item *item = m_items[index];
	return item ? item->m_value : 0;
}

// @?valueAt@Rva0036AF30ItemCollection@@QBEHH@Z 0x0036AF70

bool Rva0036AF30ItemCollection::findPairAt(
	int index,
	unsigned int key,
	unsigned int *value) const
{
	if( index < 0 || (unsigned int)index > m_items.size() - 1 )
		return false;

	Rva0036AF30Item **items = m_items.m_begin;
	if( items[index] == 0 )
		return false;
	// Retail independently evaluates the slot for the check and the dispatch.
	_ReadWriteBarrier();

	return items[index]->m_pairs.find(key, value);
}

// @?findPairAt@Rva0036AF30ItemCollection@@QBE_NHIPAI@Z 0x0036AFB0
