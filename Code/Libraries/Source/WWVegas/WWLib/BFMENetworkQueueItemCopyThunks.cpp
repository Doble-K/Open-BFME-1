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

class BFMENetworkQueueItem1copyFromQueueNodeShim
{
public:
	void copyFromQueueNode(void * a0);
};

void BFMENetworkQueueItem1::copyFromQueueNode(void * a0)
{
	((BFMENetworkQueueItem1copyFromQueueNodeShim *)this)->copyFromQueueNode(a0);
}

class BFMENetworkQueueItemcopyFromQueueNodeShim
{
public:
	void copyFromQueueNode(void * a0);
};

void BFMENetworkQueueItem::copyFromQueueNode(void * a0)
{
	((BFMENetworkQueueItemcopyFromQueueNodeShim *)this)->copyFromQueueNode(a0);
}

