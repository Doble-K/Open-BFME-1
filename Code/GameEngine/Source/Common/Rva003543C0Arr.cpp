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

struct Rva003543E0Elem
{
	char m_pad[0x0C];
	unsigned char m_0c;
	char m_tail[7];
};

class Rva003543E0Arr
{
public:
	unsigned char get(int index);

	char m_pad[0x0C];
	Rva003543E0Elem *m_items;
};

unsigned char Rva003543E0Arr::get(int index)
{
	return m_items[index].m_0c;
}
