// A constructor that remembers how many elements it was asked for, starts
// empty and takes a block of that many words.

extern "C" __declspec(dllimport) void * __cdecl malloc(unsigned int bytes);

class Gen_008A3070
{
public:
	Gen_008A3070(int count);

private:
	int m_bfmeCount;					// +0x00
	int m_bfmeUsed;						// +0x04
	void *m_bfmeBlock;					// +0x08
};

// ??0Gen_008A3070@@QAE@H@Z
Gen_008A3070::Gen_008A3070(int count)
{
	m_bfmeCount = count;

	m_bfmeUsed = 0;

	m_bfmeBlock = malloc(count * 4);
}
