// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Chat SDK -- chatLeaveChannel, retail 0x008609B0, 61 bytes,
   reconstructed from the retail bytes; the declarations are local for the same
   reason chatMain.c's are.

   The connection is the CHAT handle itself: the connected flag is its first
   word and the chat socket its +0x1C, both of which chatMain.c already has.
   A null reason becomes the empty string before the PART goes out, and the
   channel bookkeeping runs afterwards with the same channel pointer. */

typedef void *CHAT;

typedef struct ciConnection
{
	int connected;					/* +0x00 */
	unsigned char pad4[0x1c - 0x04];
	unsigned char chatSocket;			/* +0x1C */
} ciConnection;

void ciSocketSendf(void *chatSocket, const char *format, ...);
void ciChannelLeft(CHAT chat, const char *channel);

void chatLeaveChannel(CHAT chat, const char *channel, const char *reason)
{
	ciConnection *connection = (ciConnection *)chat;

	if(!chat)
		return;

	if(!connection->connected)
		return;

	if(!reason)
		reason = "";

	ciSocketSendf(&connection->chatSocket, "PART %s :%s", channel, reason);

	ciChannelLeft(chat, channel);
}
