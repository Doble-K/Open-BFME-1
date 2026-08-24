// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva003543C0Elem
{
	unsigned int a;
	unsigned int b;
	unsigned int c;
	unsigned int d;
	unsigned int e;
};

class Rva003543C0Arr
{
public:
	unsigned int at(int index);

	char m_pad[0x0C];
	Rva003543C0Elem *m_items;
};

unsigned int Rva003543C0Arr::at(int index)
{
	return m_items[index].a;
}
