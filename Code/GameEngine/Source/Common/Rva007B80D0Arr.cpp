// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva007B80D0Triple
{
	unsigned int a;
	unsigned int b;
	unsigned int c;
};

class Rva007B80D0Arr
{
public:
	Rva007B80D0Triple *at(int index);

	char m_pad[0x10];
	Rva007B80D0Triple *m_items;
};

Rva007B80D0Triple *Rva007B80D0Arr::at(int index)
{
	return m_items + index;
}
