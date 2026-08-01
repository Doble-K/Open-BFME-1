class BFMENetworkQueueItem1
{
public:
	void copyFromQueueNode(void *);
};

class BFMENetworkQueueItem
{
public:
	void copyFromQueueNode(void *);
};

__declspec(naked) void BFMENetworkQueueItem1::copyFromQueueNode(void *)
{
	__asm {
		_emit 0E9h
		_emit 0D1h
		_emit 053h
		_emit 062h
		_emit 000h
	}
}

__declspec(naked) void BFMENetworkQueueItem::copyFromQueueNode(void *)
{
	__asm {
		_emit 0E9h
		_emit 07Bh
		_emit 080h
		_emit 062h
		_emit 000h
	}
}
