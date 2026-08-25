// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Peer SDK -- piCancelJoinOperation, retail 0x0085F0A0, 97 bytes,
   reconstructed from the retail bytes; the declarations are local for the same
   reason peerHost.c's next door are.

   The connection is the PEER handle itself and the operation array sits at its
   +0x1798, holding pointers rather than operations -- the body dereferences
   what ArrayNth hands back before reading anything. An operation carries its
   type at +0x04, the room it names at +0x1C and the cancelled flag at +0x38.

   The two accepted types are tested 2 before 1, which is the order the source
   writes them, and the first match returns rather than sweeping the rest. */

#include <stdlib.h>

typedef void *PEER;

typedef struct piConnection
{
	unsigned char pad0[0x1798];
	void *operationList;				/* +0x1798 */
	int operationsAdded;				/* +0x179C */
	int operationsRemoved;				/* +0x17A0 */
} piConnection;

typedef struct piOperation
{
	unsigned char pad0[4];
	int type;					/* +0x04 */
	void *owned08;					/* +0x08 */
	unsigned char pad0c[0x1c - 0x0c];
	int roomID;					/* +0x1C */
	void *owned20;					/* +0x20 */
	void *owned24;					/* +0x24 */
	unsigned char pad28[0x2c - 0x28];
	unsigned int sock;				/* +0x2C */
	unsigned char pad30[0x34 - 0x30];
	int sockOpen;					/* +0x34 */
	int cancelled;					/* +0x38 */
} piOperation;

enum
{
	PI_JOIN_TITLE_ROOM = 1,
	PI_JOIN_GROUP_ROOM = 2
};

int ArrayLength(void *array);
void *ArrayNth(void *array, int index);

void piCancelJoinOperation(PEER peer, int group)
{
	piConnection *connection = (piConnection *)peer;
	piOperation *operation;
	int len;
	int i;

	if(!connection->operationList)
		return;

	len = ArrayLength(connection->operationList);
	for(i = 0 ; i < len ; i++)
	{
		operation = *(piOperation **)ArrayNth(connection->operationList, i);
		if(((operation->type == PI_JOIN_GROUP_ROOM) || (operation->type == PI_JOIN_TITLE_ROOM))
			&& (operation->roomID == group))
		{
			operation->cancelled = 1;
			return;
		}
	}
}

/* piRemoveOperation, retail 0x0085EFD0, 105 bytes.  Same list, same
   dereference: the array holds piOperation pointers, so the search compares
   what ArrayNth hands back through one indirection.  The list pointer is
   re-read from the connection on every iteration -- cached in a local the
   loop is shorter -- and the counter at +0x17A0 is named for the only thing
   any body reaches it for, which is being bumped once per removal. */
void ArrayDeleteAt(void *array, int index);

void piRemoveOperation(PEER peer, void *operation)
{
	piConnection *connection = (piConnection *)peer;
	int len;
	int i;

	if(!connection->operationList)
		return;

	len = ArrayLength(connection->operationList);
	for(i = 0 ; i < len ; i++)
	{
		if(*(void **)ArrayNth(connection->operationList, i) == operation)
		{
			ArrayDeleteAt(connection->operationList, i);
			connection->operationsRemoved++;
			return;
		}
	}
}

/* The list's own lifecycle.  ArrayNew is handed an element size of 4, which
   is the pointer width piRemoveOperation's extra dereference already implied,
   and the free callback it is handed is the body below.

   piOperationFree frees three members unconditionally -- +0x08, +0x20 and
   +0x24 -- so those three are owned heap pointers; what they hold is not
   determined by anything this file can see, so they are numbered rather than
   named.  The pair behind the flag at +0x34 IS determined: the call is
   closesocket, so +0x2C is a socket, and the winsock teardown follows it.

   The counters bracket each other -- +0x179C is bumped once per operation
   created and +0x17A0 once per operation removed -- and this is where both
   are zeroed. */

typedef enum
{
	PEERFalse,
	PEERTrue
} PEERBool;

void *ArrayNew(int elemSize, int initialCount, void (*elemFree)(void *elem));
void ArrayClear(void *array);
int __stdcall closesocket(unsigned int s);
int __stdcall WSACleanup(void);
#define gsifree free

static void piOperationFree(void *elem)
{
	piOperation *operation = *(piOperation **)elem;

	gsifree(operation->owned20);
	gsifree(operation->owned24);
	gsifree(operation->owned08);

	if(operation->sockOpen)
	{
		closesocket(operation->sock);
		WSACleanup();
	}

	gsifree(operation);
}

PEERBool piOperationsInit(PEER peer)
{
	piConnection *connection = (piConnection *)peer;

	connection->operationsAdded = 0;
	connection->operationsRemoved = 0;

	connection->operationList = ArrayNew(sizeof(piOperation *), 0, piOperationFree);

	return (PEERBool)(connection->operationList != 0);
}

void piClearOperations(PEER peer)
{
	piConnection *connection = (piConnection *)peer;

	if(connection->operationList)
		ArrayClear(connection->operationList);
}
