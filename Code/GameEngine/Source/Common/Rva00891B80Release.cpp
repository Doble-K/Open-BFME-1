// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva00891B80Pool
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern Rva00891B80Pool *g_pool01337A30;

struct Rva00891B80Block
{
	unsigned short m_ref;
};

class Rva00891B80
{
	Rva00891B80Block *m_block;

public:
	void release();
};

void Rva00891B80::release()
{
	Rva00891B80Block *block = m_block;
	if (--block->m_ref == 0)
		g_pool01337A30->free(block);
}
