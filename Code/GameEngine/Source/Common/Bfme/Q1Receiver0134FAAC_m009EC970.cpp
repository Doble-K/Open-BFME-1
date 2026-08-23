// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Q1Receiver0134FAAC::m009EC970, retail 0x009EC970, 45 bytes.
//
// A three-way switch that sets one of three adjacent flags at this+0x1EC,
// +0x1ED and +0x1EE. MSVC walks the cases with a subtract and two decrements
// rather than a table, and every arm returns on the spot.

typedef int Int;
typedef bool Bool;

class Q1Receiver0134FAAC
{
public:
	void m009EC970(Int which);

private:
	unsigned char m_unmodelled_000[0x1EC];
	Bool m_flag0;						// this+0x1EC
	Bool m_flag1;						// this+0x1ED
	Bool m_flag2;						// this+0x1EE
};

void Q1Receiver0134FAAC::m009EC970(Int which)
{
	switch (which)
	{
		case 0:
			m_flag0 = true;
			break;
		case 1:
			m_flag1 = true;
			break;
		case 2:
			m_flag2 = true;
			break;
	}
}
