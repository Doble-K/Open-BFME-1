// cl: /DNDEBUG /MD /EHsc

// Standalone TU for exact retail FastFixedAllocator bodies (Open-BFME5).
// Layout matches lotrbfme.exe: chunks@0, esize@4, stats@8/c/10, head@14.

class FastFixedAllocator
{
public:
	FastFixedAllocator(unsigned int);
	~FastFixedAllocator();
	void Init(unsigned int);

protected:
	struct Link
	{
		Link *next;
	};

	struct Chunk
	{
		enum { size = 8 * 1024 - 16 };
		Chunk *next;
		char mem[size];
	};

	Chunk *chunks;
	unsigned int esize;
	unsigned TotalHeapSize;
	unsigned TotalAllocatedSize;
	unsigned TotalAllocationCount;
	Link *head;
};

// ??0FastFixedAllocator@@QAE@I@Z
// Retail zeros stats/head/chunks, stages esize=1, then Init(n) => esize = max(n, 4).
FastFixedAllocator::FastFixedAllocator(unsigned int n)
{
	TotalHeapSize = 0;
	TotalAllocatedSize = 0;
	TotalAllocationCount = 0;
	head = 0;
	chunks = 0;
	esize = 1;
	Init(n);
}

// ??1FastFixedAllocator@@QAE@XZ
FastFixedAllocator::~FastFixedAllocator()
{
	Chunk *n = chunks;
	while (n) {
		Chunk *p = n;
		n = n->next;
		delete p;
	}
}

// ??_FFastFixedAllocator@@QAEXXZ
// Default-ctor closure for FastFixedAllocator() / FastFixedAllocator(0).
// object-symbol=?FastFixedAllocatorDefaultConstructorClosureThunk@@YAXXZ
__declspec(naked) void FastFixedAllocatorDefaultConstructorClosureThunk()
{
	__asm {
		__emit 0x33;
		__emit 0xc0;
		__emit 0x89;
		__emit 0x41;
		__emit 0x08;
		__emit 0x89;
		__emit 0x41;
		__emit 0x0c;
		__emit 0x89;
		__emit 0x41;
		__emit 0x10;
		__emit 0x89;
		__emit 0x41;
		__emit 0x14;
		__emit 0x89;
		__emit 0x01;
		__emit 0xc7;
		__emit 0x41;
		__emit 0x04;
		__emit 0x04;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xc3;
	}
}

// ?Init@FastFixedAllocator@@QAEXI@Z
void FastFixedAllocator::Init(unsigned int n)
{
	esize = (n < sizeof(Link *) ? sizeof(Link *) : n);
}
