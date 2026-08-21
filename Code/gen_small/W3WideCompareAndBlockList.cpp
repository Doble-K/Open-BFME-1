// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: two wide-character comparison bodies and the block-list release
// loop, out of d_0001466e.asm.
//
// 0x0005C4B0 is a counted wide comparison: `ret 0xC` for three
// arguments -- pointer, pointer, count -- comparing ZERO-EXTENDED two-byte
// units, which is what says the ordering is unsigned even though the result is
// a signed int. The count is tested before the first load, which is why a zero
// or negative count returns 0 without touching either pointer.
//
// 0x0005C660 walks a singly linked list of heap blocks whose next pointer is the
// FIRST dword of each block -- it reloads the head from the object after every
// free, so the list head is a member and not a local copy -- and releases each
// one. It is the release half of the buffer bookkeeping the guarded stack
// allocations in this binary hang their overflow blocks on. The `free` slot is
// hoisted into a register before the loop, which is just MSVC lifting the
// dllimport indirection out of the loop body.
//
// Identity is address-derived.

#include <stdlib.h>

typedef unsigned short WCHAR;

// ?Rva0005C4B0CompareWide@@YGHPBG0H@Z
int __stdcall Rva0005C4B0CompareWide(const WCHAR *a, const WCHAR *b, int count)
{
	while (count > 0)
	{
		if (*a != *b)
		{
			return (int)(unsigned int)*a - (int)(unsigned int)*b;
		}

		++a;
		++b;
		--count;
	}

	return 0;
}

struct Rva0005C660Block
{
	Rva0005C660Block *m_next;							///< block+0x00
};

class Rva0005C660BlockList
{
public:
	void releaseAll(void);

private:
	Rva0005C660Block *m_head;							///< retail this+0x00
};

// ?releaseAll@Rva0005C660BlockList@@QAEXXZ
void Rva0005C660BlockList::releaseAll(void)
{
	while (m_head != 0)
	{
		Rva0005C660Block *block = m_head;

		m_head = block->m_next;
		free(block);
	}
}
