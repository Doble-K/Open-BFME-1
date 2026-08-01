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

__declspec(naked) void BFMENetworkQueue1::popFront()
{
	__asm {
		_emit 0E9h
		_emit 039h
		_emit 036h
		_emit 063h
		_emit 000h
	}
}

__declspec(naked) void BFMENetworkQueue::popFront()
{
	__asm {
		_emit 0E9h
		_emit 041h
		_emit 022h
		_emit 063h
		_emit 000h
	}
}
