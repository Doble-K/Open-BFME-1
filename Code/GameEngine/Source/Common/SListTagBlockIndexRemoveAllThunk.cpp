// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: SList<TagBlockIndex>::Remove_All retail bucket cleanup.

class TagBlockIndex;

template <class T>
class SList
{
private:
	struct Node
	{
		Node *next;
		~Node();
	};

public:
	virtual void Remove_All();

private:
	Node *m_buckets[45007];
};

// ?Remove_All@?$SList@VTagBlockIndex@@@@UAEXXZ
template <>
void SList<TagBlockIndex>::Remove_All()
{
	for (int i = 0; i < 45007; ++i)
	{
		Node *node = m_buckets[i];
		while (node)
		{
			Node *next = node->next;
			delete node;
			node = next;
		}
		m_buckets[i] = 0;
	}
}
