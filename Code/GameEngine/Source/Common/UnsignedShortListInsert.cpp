#include <new>

struct BFMEUnsignedShortListNode
{
	BFMEUnsignedShortListNode *next;
	BFMEUnsignedShortListNode *previous;
	unsigned short value;
};

struct BFMEUnsignedShortListIterator
{
	BFMEUnsignedShortListNode *node;
};

class BFMEUnsignedShortListABI
{
public:
	BFMEUnsignedShortListIterator insert(BFMEUnsignedShortListIterator position,
		const unsigned short &value);
};

// ?d_000cf200@@YAXXZ
BFMEUnsignedShortListIterator BFMEUnsignedShortListABI::insert(
	BFMEUnsignedShortListIterator position, const unsigned short &value)
{
	BFMEUnsignedShortListNode *node =
		static_cast<BFMEUnsignedShortListNode *>(::operator new(sizeof(BFMEUnsignedShortListNode)));
	new (&node->value) unsigned short(value);
	BFMEUnsignedShortListNode *previous = position.node->previous;
	node->next = position.node;
	node->previous = previous;
	previous->next = node;
	position.node->previous = node;

	BFMEUnsignedShortListIterator result = { node };
	return result;
}
