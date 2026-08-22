// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Peer SDK pinger shutdown path.  The globals are kept TU-local in
   the original SDK; they are extern here so the matcher can pin their retail
   addresses while the remainder of peerPing.c is recovered. */

typedef int GSIBool;
typedef unsigned int SOCKET;
typedef void *DArray;

#define INVALID_SOCKET ((SOCKET)-1)

extern GSIBool piInitialized;
extern GSIBool piSettingData;
extern SOCKET piSocket;
extern DArray piActivePingList;
extern DArray piCallbacks;

int __stdcall closesocket(SOCKET socket);
void SocketShutDown(void);
void ArrayFree(DArray array);
void piProcessIncoming(void);
void piCheckTimeouts(void);
void piCallCallbacks(void);

void pingerShutdown(void)
{
	if (!piInitialized || piSettingData)
		return;

	if (piSocket != INVALID_SOCKET)
	{
		closesocket(piSocket);
		piSocket = INVALID_SOCKET;
	}

	SocketShutDown();
	ArrayFree(piActivePingList);
	ArrayFree(piCallbacks);
	piInitialized = 0;
}

void pingerThink(void)
{
	if (!piInitialized || piSettingData)
		return;

	piProcessIncoming();
	piCheckTimeouts();
	piCallCallbacks();
}
