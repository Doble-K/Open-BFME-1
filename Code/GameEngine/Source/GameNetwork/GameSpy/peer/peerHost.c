// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Peer SDK -- piSBFreeHostServer, retail 0x00864FB0, 38 bytes,
   reconstructed from the retail bytes rather than transcribed: the peer/
   module is not in the carrier this directory's siblings explain, so the
   declarations here are local as theirs are.

   The connection is the PEER handle itself and the hosted server pointer sits
   at its +0xB50. The free takes the address of that field, not its value --
   the body computes `connection + 0xB50` once and passes it -- and the field
   is cleared afterwards. */

typedef void *PEER;

typedef struct piConnection
{
	unsigned char pad0[0xb50];
	void *hostServer;				/* +0xB50 */
} piConnection;

void SBServerFree(void **server);

void piSBFreeHostServer(PEER peer)
{
	piConnection *connection = (piConnection *)peer;

	if(connection->hostServer)
	{
		SBServerFree(&connection->hostServer);
		connection->hostServer = 0;
	}
}
