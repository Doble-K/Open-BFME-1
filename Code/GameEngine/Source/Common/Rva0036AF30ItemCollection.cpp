class Rva0036AF30Item
{
public:
	char m_unreconstructed[ 0x14 ];
	int m_key;
	int m_value;
};

class Rva0036AF30ItemCollection
{
public:
	char m_unreconstructed[ 8 ];
	Rva0036AF30Item **m_begin;
	Rva0036AF30Item **m_end;

	int indexOf(int key) const;
};

int Rva0036AF30ItemCollection::indexOf(int key) const
{
	Rva0036AF30Item **cursor = m_begin;
	Rva0036AF30Item **end = m_end;
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
