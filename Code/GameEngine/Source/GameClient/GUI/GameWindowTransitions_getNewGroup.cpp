#include <stddef.h>

inline void *operator new( size_t, void *where ) { return where; }

template <typename T> class StringBase
{
friend class BFMETransitionAsciiString;
private:
	StringBase( const StringBase<T> &other );
	void releaseBuffer( void );
};

class BFMETransitionAsciiString
{
public:
	BFMETransitionAsciiString( const BFMETransitionAsciiString &other )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other );
	}
	~BFMETransitionAsciiString()
	{
		((StringBase<char> *)this)->StringBase<char>::releaseBuffer();
	}
	bool isEmpty() const
	{
		return m_data == 0 || *(unsigned short *)(m_data + 4) == 0;
	}
private:
	char *m_data;
};

class BFMETransitionGroup
{
public:
	BFMETransitionGroup();
	void setName( BFMETransitionAsciiString name );
private:
	char m_unmodelled[0x14];
};

struct BFMETransitionGroupNode
{
	BFMETransitionGroupNode *m_next;
	BFMETransitionGroupNode *m_previous;
	BFMETransitionGroup *m_value;
};

class BFMETransitionHandler
{
public:
	BFMETransitionGroup *getNewGroup( BFMETransitionAsciiString name );
	BFMETransitionGroup *findGroup( BFMETransitionAsciiString name );
private:
	char m_unmodelled[0x1c];
	BFMETransitionGroupNode *m_groupHead;
};

BFMETransitionGroup *BFMETransitionHandler::getNewGroup( BFMETransitionAsciiString name )
{
	if ( name.isEmpty() )
		return 0;
	if ( findGroup( name ) != 0 )
		return 0;

	BFMETransitionGroup *group = new BFMETransitionGroup;
	group->setName( name );

	BFMETransitionGroupNode *head = m_groupHead;
	BFMETransitionGroupNode *node = new BFMETransitionGroupNode;
	new ( &node->m_value ) BFMETransitionGroup *( group );
	BFMETransitionGroupNode *previous = head->m_previous;
	node->m_previous = previous;
	node->m_next = head;
	previous->m_next = node;
	head->m_previous = node;
	return group;
}
