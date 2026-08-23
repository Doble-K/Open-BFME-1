// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Q1Receiver0134FAAC::m009ECA30, retail 0x009ECA30, 22 bytes.
//
// A store and a floor: the argument lands at this+0x24 and is then replaced by
// 1 when it was below it -- the store happens either way, which is why the
// compare is scheduled between the load and the first store.

typedef int Int;

class Q1Receiver0134FAAC
{
public:
	void m009ECA30(Int value);

private:
	unsigned char m_unmodelled_000[0x24];
	Int m_value;						// this+0x24
};

void Q1Receiver0134FAAC::m009ECA30(Int value)
{
	m_value = value;
	if (value < 1)
		m_value = 1;
}
