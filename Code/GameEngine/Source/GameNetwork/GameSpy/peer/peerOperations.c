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

typedef void *PEER;

typedef struct piConnection
{
	unsigned char pad0[0x1798];
	void *operationList;				/* +0x1798 */
	unsigned char pad179c[0x17a0 - 0x179c];
	int operationsRemoved;				/* +0x17A0 */
} piConnection;

typedef struct piOperation
{
	unsigned char pad0[4];
	int type;					/* +0x04 */
	unsigned char pad8[0x1c - 0x08];
	int roomID;					/* +0x1C */
	unsigned char pad20[0x38 - 0x20];
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
