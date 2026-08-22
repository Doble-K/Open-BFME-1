// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Peer SDK pinger shutdown path.  The globals are kept TU-local in
   the original SDK; they are extern here so the matcher can pin their retail
   addresses while the remainder of peerPing.c is recovered. */

#include <winsock.h>
#include <stdlib.h>
#include <string.h>

typedef int GSIBool;
typedef void *DArray;

typedef void (*pingerGotPing)(unsigned int, unsigned short, int, const char *, int, void *);

typedef struct piQueuedCallback
{
	unsigned int IP;
	unsigned short port;
	int ping;
	char *data;
	int len;
	void *param;
	pingerGotPing callback;
} piQueuedCallback;

typedef struct piActivePing
{
	GSIBool originator;
	unsigned short ID;
	unsigned short expectedTrip;
	unsigned int timestamp;
	unsigned int timeout;
	unsigned int remoteIP;
	unsigned short remotePort;
	pingerGotPing reply;
	void *replyParam;
} piActivePing;

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
		goto socket_error;

	bFlag = 1;
	rcode = setsockopt(piSocket, SOL_SOCKET, SO_REUSEADDR, (const char *)&bFlag, sizeof(bFlag));

	rcode = bind(piSocket, (SOCKADDR *)&sockaddr, sizeof(SOCKADDR_IN));
	if (rcode == -1)
	{
socket_error:
		WSAGetLastError();
fail:
		return 0;
	}

	return 1;
}
DArray ArrayNew(int elemSize, int numElemsToAllocate, void *elemFreeFn);
void ArrayAppend(DArray array, const void *newElem);
int ArrayLength(DArray array);
void *ArrayNth(DArray array, int index);
void ArrayDeleteAt(DArray array, int index);
void ArrayFree(DArray array);
void piProcessIncoming(void);
static void piCheckTimeouts(void);
static void piCallCallbacks(void);
unsigned int current_time(void);

static void piQueueCallback(unsigned int IP, unsigned short port, int ping,
	const char *data, int len, void *param, pingerGotPing callbackFunc)
{
	piQueuedCallback callback;

	if (!callbackFunc)
		return;

	callback.IP = IP;
	callback.port = port;
	callback.ping = ping;
	callback.len = len;
	callback.param = param;
	callback.callback = callbackFunc;

	if (data)
	{
		callback.data = (char *)malloc((unsigned int)len);
		if (!callback.data)
			return;
		memcpy(callback.data, data, (unsigned int)len);
	}
	else
	{
		callback.data = 0;
	}

	ArrayAppend(piCallbacks, &callback);
}

static void piCallCallbacks(void)
{
	piQueuedCallback *callback;
	piQueuedCallback callbackCopy;

	while (ArrayLength(piCallbacks) > 0)
	{
		callback = (piQueuedCallback *)ArrayNth(piCallbacks, 0);
		if (!callback)
			return;

		callbackCopy = *callback;
		callback = &callbackCopy;
		ArrayDeleteAt(piCallbacks, 0);
		callback->callback(callback->IP, callback->port, callback->ping,
			callback->data, callback->len, callback->param);
		free(callback->data);
	}
}

static void piCheckTimeouts(void)
{
	unsigned int now;
	piActivePing *activePing;
	int len;
	int n;

	len = ArrayLength(piActivePingList);
	if (len == 0)
		return;

	now = current_time();
	for (n = len - 1; n >= 0; --n)
	{
		activePing = (piActivePing *)ArrayNth(piActivePingList, n);
		if (activePing != 0 && activePing->timeout != 0 && activePing->timeout <= now)
		{
			if (activePing->originator && activePing->reply != 0)
			{
				piQueueCallback(activePing->remoteIP, activePing->remotePort, -1,
					0, 0, activePing->replyParam, activePing->reply);
			}
			ArrayDeleteAt(piActivePingList, n);
		}
	}
}

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
