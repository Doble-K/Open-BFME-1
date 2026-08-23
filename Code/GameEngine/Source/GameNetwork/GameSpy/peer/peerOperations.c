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
