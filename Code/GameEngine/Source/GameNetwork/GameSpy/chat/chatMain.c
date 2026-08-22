// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Chat SDK -- the ciSendGetKey body from chatMain.c.
   Reconstructed from the 2007 SDK (nitrocaster/GameSpy,
   src/GameSpy/Chat/chatMain.c), whose function body is unchanged from the
   2004-vintage implementation compiled into lotrbfme.exe.  The surrounding
   declarations are local because the matching 2004 Chat headers are not in
   hand; see ../PROVENANCE.txt for the source and permission record.

   Retail identifies the body independently: its GETKEY format string is
   referenced only at 0x00861860, and the final call targets ciSocketSend at
   0x0085AC90 with &connection->chatSocket (connection + 0x1c). */

#include <assert.h>
#include <stdio.h>
#include <string.h>

typedef void *CHAT;

typedef struct ciConnection
{
	unsigned char beforeChatSocket[0x1c];
	unsigned char chatSocket;
} ciConnection;

void ciSocketSend(void *chatSocket, const char *buffer);

static void ciSendGetKey(CHAT chat,
						 const char *target,
						 const char *cookie,
						 int num,
						 const char **keys)
{
	char buffer[512];
	int len;
	int i;
	int j;
	int keyLen;
	ciConnection *connection = (ciConnection *)chat;

	assert(target && target[0]);
	assert(cookie && cookie[0]);
	assert(num >= 1);
	assert(keys);

	sprintf(buffer, "GETKEY %s %s 0 :", target, cookie);
	len = (int)strlen(buffer);

	for(i = 0 ; i < num ; i++)
	{
		if(!keys[i] || !keys[i][0])
			continue;

		keyLen = (int)strlen(keys[i]);
		if((len + keyLen + 1) >= (int)sizeof(buffer))
			return;

		buffer[len++] = '\\';
		memcpy(buffer + len, keys[i], (unsigned int)keyLen);
		for(j = len ; j < (len + keyLen) ; j++)
			if(buffer[j] == '\\')
				buffer[j] = '/';
		len += keyLen;
		buffer[len] = '\0';
	}

	ciSocketSend(&connection->chatSocket, buffer);
}

/* Keep the TU-local SDK helper reachable in this partial reconstruction.  In
   the complete SDK chatGetGlobalKeys calls it; retaining a caller also lets
   VC7.1 reproduce the helper's internal register argument assignment. */
void ciSendGetKeyAnchor(CHAT chat,
						const char *target,
						const char *cookie,
						int num,
						const char **keys)
{
	ciSendGetKey(chat, target, cookie, num, keys);
}
