// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: the destructor of a second small-buffer conversion holder.
//
// Same layout and same test as the one in W3ConversionBufferRelease.cpp --
// pointer at this+0, inline buffer at this+4, release only when the pointer was
// moved off the buffer -- but this one does NOT inline the release: it tail
// JUMPS to the out-of-line release body at 0x0005C6B0 through the ILT thunk at
// 0x0002F0AE. A tail jump with `this` untouched in ecx is what proves the
// callee is a thiscall member of the same object, and the fact that retail
// calls at all proves the release stayed an opaque declaration here, i.e. it is
// defined in some other translation unit.
//
// Identity is address-derived.

class Rva0005C6B0Holder
{
public:
	~Rva0005C6B0Holder(void);
	void release(void);									///< retail 0x0005C6B0, out of line

private:
	char *m_text;										///< retail this+0x00
	char m_buffer[1];									///< retail this+0x04
};

// ??1Rva0005C6B0Holder@@QAE@XZ
Rva0005C6B0Holder::~Rva0005C6B0Holder(void)
{
	if (m_text != m_buffer)
	{
		release();
	}
}
