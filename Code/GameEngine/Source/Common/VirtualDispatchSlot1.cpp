// cl: /DNDEBUG /MD

class AddressThunk00105360
{
public:
	virtual void slot0();
	virtual void slot1();

	void forwardSlot1();
};

void AddressThunk00105360::forwardSlot1()
{
	slot1();
}
