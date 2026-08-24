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

struct Rva00354400Elem
{
	char m_pad[0x0E];
	short m_0e;
	char m_tail[4];
};

class Rva00354400Arr
{
public:
	int get(int index);

	char m_pad[0x0C];
	Rva00354400Elem *m_items;
};

int Rva00354400Arr::get(int index)
{
	return m_items[index].m_0e;
}

struct Rva00354460Elem
{
	char m_pad[8];
	int m_08;
	char m_tail[8];
};

class Rva00354460Arr
{
public:
	int *addr(int index);

	char m_pad[0x0C];
	Rva00354460Elem *m_items;
};

int *Rva00354460Arr::addr(int index)
{
	return &m_items[index].m_08;
}

class Rva00354480Arr
{
public:
	unsigned char get(int index);

	char m_pad[0x0C];
	Rva003543E0Elem *m_items;
};

unsigned char Rva00354480Arr::get(int index)
{
	return m_items[index].m_0c;
}

class Rva003544A0Arr
{
public:
	int get(int index);

	char m_pad[0x0C];
	Rva00354400Elem *m_items;
};

int Rva003544A0Arr::get(int index)
{
	return m_items[index].m_0e;
}

class Rva00355660Arr
{
public:
	unsigned char get(int index);

	char m_pad[0x18];
	Rva003543E0Elem *m_items;
};

unsigned char Rva00355660Arr::get(int index)
{
	return m_items[index].m_0c;
}

class Rva00355680Arr
{
public:
	unsigned char get(int index);

	char m_pad[0x38];
	Rva003543E0Elem *m_items;
};

unsigned char Rva00355680Arr::get(int index)
{
	return m_items[index].m_0c;
}

struct Rva00355640Key
{
	int m_pad;
	int m_index;
};

class Rva00355640Arr
{
public:
	int *addr(const Rva00355640Key *key);

	char m_pad[0x18];
	Rva00354460Elem *m_items;
};

int *Rva00355640Arr::addr(const Rva00355640Key *key)
{
	return &m_items[key->m_index].m_08;
}
