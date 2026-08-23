// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Chat SDK -- three small helpers from chatCallbacks.c, reconstructed
   from the retail bytes rather than from the SDK text: the declarations here
   are local for the same reason chatMain.c's are, and the connection layout is
   read off the offsets these bodies touch.

     0x0086C310  ciGetNextID           38 bytes
     0x0086C340  ciCheckFiltersForID   39 bytes
     0x008702C0  ciInitCallbacks       40 bytes

   The connection is the CHAT handle itself -- every one of them indexes
   straight off the incoming pointer with no adjustment -- and carries the
   filter list at +0x814, the next ID at +0x81C and the callback array at
   +0x820. A filter carries its ID at +0x20 and its next link at +0x24. */

#include <limits.h>

typedef void *CHAT;

typedef enum
{
	CHATFalse,
	CHATTrue
} CHATBool;

typedef struct ciFilter
{
	unsigned char pad0[0x20];
	int ID;						/* +0x20 */
	struct ciFilter *next;				/* +0x24 */
} ciFilter;

typedef struct ciConnection
{
	unsigned char pad0[0x814];
	ciFilter *filterList;				/* +0x814 */
	unsigned char pad818[0x81c - 0x818];
	int nextID;					/* +0x81C */
	void *callbackList;				/* +0x820 */
} ciConnection;

/* the callback array element; only its size reaches this file */
typedef struct ciCallback
{
	unsigned char pad0[0x18];
} ciCallback;

void *ArrayNew(int elemsize, int initialcount, void (*elemfreefn)(void *elem));
void ciCallbackFree(void *elem);

int ciGetNextID(CHAT chat)
{
	ciConnection *connection = (ciConnection *)chat;
	int ID;

	ID = connection->nextID;
	if(ID == INT_MAX)
		connection->nextID = 1;
	else
		connection->nextID = ID + 1;

	return ID;
}

CHATBool ciCheckFiltersForID(CHAT chat, int ID)
{
	ciConnection *connection = (ciConnection *)chat;
	ciFilter *filter;

	for(filter = connection->filterList ; filter ; filter = filter->next)
		if(filter->ID == ID)
			return CHATTrue;

	return CHATFalse;
}

/* ciInitCallbacks present-unmatched */
CHATBool ciInitCallbacks(CHAT chat)
{
	ciConnection *connection = (ciConnection *)chat;

	connection->callbackList = ArrayNew(sizeof(ciCallback), 128, ciCallbackFree);

	return (CHATBool)(connection->callbackList != 0);
}
