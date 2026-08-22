// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Peer SDK pinger shutdown path.  The globals are kept TU-local in
   the original SDK; they are extern here so the matcher can pin their retail
   addresses while the remainder of peerPing.c is recovered. */

typedef int GSIBool;
typedef unsigned int SOCKET;
typedef void *DArray;

#define INVALID_SOCKET ((SOCKET)-1)

extern GSIBool pingerInitialized;
extern GSIBool pingerShuttingDown;
extern SOCKET pingerSocket;
extern DArray pingerOutstanding;
extern DArray pingerCompleted;

int __stdcall closesocket(SOCKET socket);
void SocketShutDown(void);
void ArrayFree(DArray array);

void pingerShutdown(void)
{
	if (!pingerInitialized || pingerShuttingDown)
		return;

	if (pingerSocket != INVALID_SOCKET)
	{
		closesocket(pingerSocket);
		pingerSocket = INVALID_SOCKET;
	}

	SocketShutDown();
	ArrayFree(pingerCompleted);
	ArrayFree(pingerOutstanding);
	pingerInitialized = 0;
}
