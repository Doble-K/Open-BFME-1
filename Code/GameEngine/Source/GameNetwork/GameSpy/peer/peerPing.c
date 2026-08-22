// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Peer SDK pinger shutdown path.  The globals are kept TU-local in
   the original SDK; they are extern here so the matcher can pin their retail
   addresses while the remainder of peerPing.c is recovered. */

#include <winsock.h>

typedef int GSIBool;
typedef void *DArray;

static GSIBool piInitialized;
static GSIBool piSettingData;
static SOCKET piSocket = INVALID_SOCKET;
static DArray piActivePingList;
static DArray piCallbacks;
static void *piPingerPinged;
static void *piPingerPingedParam;
static void *piPingerSetData;
static void *piPingerSetDataParam;
static GSIBool piUDPEnabled;
static unsigned short piNextID;
static int piLastThinkTime;

int __stdcall closesocket(SOCKET socket);
void SocketStartUp(void);
void SocketShutDown(void);
static int piSocketInit(const char *localAddress, unsigned short localPort)
{
	int rcode;
	SOCKADDR_IN sockaddr;
	int bFlag;

	SocketStartUp();

	memset(&sockaddr, 0, sizeof(SOCKADDR_IN));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(localPort);
	if (localAddress != 0)
	{
		unsigned int IP;
		IP = inet_addr(localAddress);
		if (IP == INADDR_NONE)
		{
			HOSTENT *hostent;
			hostent = gethostbyname(localAddress);
			if (hostent == 0)
				goto fail;
			IP = *(unsigned int *)hostent->h_addr_list[0];
		}
		sockaddr.sin_addr.s_addr = IP;
	}
	else
	{
		sockaddr.sin_addr.s_addr = INADDR_ANY;
	}

	piSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (piSocket == INVALID_SOCKET)
		goto fail;

	bFlag = 1;
	rcode = setsockopt(piSocket, SOL_SOCKET, SO_REUSEADDR, (const char *)&bFlag, sizeof(bFlag));

	rcode = bind(piSocket, (SOCKADDR *)&sockaddr, sizeof(SOCKADDR_IN));
	if (rcode == -1)
	{
		WSAGetLastError();
		goto fail;
	}
	goto success;

fail:
	return 0;

success:
	return 1;
}
DArray ArrayNew(int elemSize, int numElemsToAllocate, void *elemFreeFn);
void ArrayFree(DArray array);
void piProcessIncoming(void);
void piCheckTimeouts(void);
void piCallCallbacks(void);

int pingerInit(register const char *localAddress, register unsigned short localPort, void *pinged,
	void *pingedParam, void *setData, void *setDataParam)
{
	if (piInitialized)
		return 0;

	if (localAddress != 0 && localAddress[0] == '\0')
		localAddress = 0;

	piPingerPinged = pinged;
	piPingerPingedParam = pingedParam;
	piPingerSetData = setData;
	piPingerSetDataParam = setDataParam;
	piSettingData = 0;
	piUDPEnabled = (localPort != 0);
	piNextID = 1;
	piLastThinkTime = 0;

	piActivePingList = ArrayNew(0x20, 0, 0);
	if (piActivePingList == 0)
		return 0;

	piCallbacks = ArrayNew(0x1C, 0, 0);
	if (piCallbacks == 0)
	{
		ArrayFree(piActivePingList);
		return 0;
	}

	if (piUDPEnabled && !piSocketInit(localAddress, localPort))
	{
		if (piSocket != INVALID_SOCKET)
		{
			closesocket(piSocket);
			piSocket = INVALID_SOCKET;
		}

		SocketShutDown();
		ArrayFree(piActivePingList);
		ArrayFree(piCallbacks);
		return 0;
	}

	piInitialized = 1;
	return 1;
}

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
