class BFMENetworkQueue1
{
public:
	void popFront();
};

class BFMENetworkQueue
{
public:
	void popFront();
};

class BFMENetworkQueue1PopFrontShim
{
public:
	void popFront();
};

class BFMENetworkQueuePopFrontShim
{
public:
	void popFront();
};

void BFMENetworkQueue1::popFront()
{
	((BFMENetworkQueue1PopFrontShim *)this)->popFront();
}

void BFMENetworkQueue::popFront()
{
	((BFMENetworkQueuePopFrontShim *)this)->popFront();
}
