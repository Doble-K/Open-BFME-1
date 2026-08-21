// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: the out-of-line release the destructor at 0x0005E1E0 tail jumps
// into. One pushed argument cleaned with `pop ecx`, and the pointer loaded into
// a register before the push rather than pushed straight from memory.
//
// Identity is address-derived.

#include <stdlib.h>

class Rva0005C6B0Holder
{
public:
	void release(void);

private:
	char *m_text;										///< retail this+0x00
	char m_buffer[1];									///< retail this+0x04
};

// ?release@Rva0005C6B0Holder@@QAEXXZ
void Rva0005C6B0Holder::release(void)
{
	free(m_text);
}
