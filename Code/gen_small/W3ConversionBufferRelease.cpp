// cl: /DNDEBUG /MD /EHs-c- /O1
// Open-BFME-1: the release half of the small-buffer conversion holder.
//
// It cleans its one pushed argument with `pop ecx` rather than `add esp,4`,
// which is the size-optimised spelling -- every other body in this family uses
// `add esp,4` -- so it was compiled with /O1 and cannot share a translation unit
// with them.
//
// The destructor shape: `add ecx,4 / cmp` compares the pointer against the address
// of the inline buffer that starts four bytes into the object, which is the same
// layout the two init bodies in W3AtlStringConversion.cpp fill -- pointer at
// this+0, buffer at this+4 -- and releases only when the pointer was moved off
// it. The free is inlined here, not a call to the out-of-line release at
// 0x0005C6B0 that the same layout also has.
//
// Identity is address-derived.

#include <stdlib.h>

class Rva0005D7B0Holder
{
public:
	~Rva0005D7B0Holder(void);

private:
	char *m_text;										///< retail this+0x00
	char m_buffer[1];									///< retail this+0x04
};

// ??1Rva0005D7B0Holder@@QAE@XZ
Rva0005D7B0Holder::~Rva0005D7B0Holder(void)
{
	if (m_text != m_buffer)
	{
		free(m_text);
	}
}
