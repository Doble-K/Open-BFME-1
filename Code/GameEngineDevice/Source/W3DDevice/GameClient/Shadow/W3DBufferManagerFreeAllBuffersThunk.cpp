// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME5: W3DBufferManager::freeAllBuffers, retail 0x007ADAD0, converted out
// of a machine byte dump. The reference body ports unchanged.
//
// The 140 bytes date the manager and both buffer records:
//
//   manager +0x09000  m_W3DVertexBuffers, and the loop counter is 18, so
//                     MAX_FVF is 18
//           +0x253CC  m_numEmptyVertexBuffersAllocated
//           +0x263D0  m_W3DIndexBuffers
//           +0x42658  m_numEmptyIndexBuffersAllocated
//   vertex buffer +0x10 m_nextVB, +0x14 m_DX8VertexBuffer
//   index buffer  +0x0C m_nextIB, +0x10 m_DX8IndexBuffer
//
// REF_PTR_RELEASE is spelled out both times: test the pointer, decrement the
// reference count at +0x04, call slot 0 when it reaches zero, and store NULL.
// The store is INSIDE the null test, not after it -- both `je`s clear the
// release block and the `mov [esi+0x14], ebp` that follows it, three bytes
// further than an unconditional clear would reach.

typedef int Int;

#define NULL 0

class RefCountClass
{
public:
	virtual void Delete_Self( void );						///< slot 0

	void Release_Ref( void ) { if (--NumRefs == 0) Delete_Self(); }

protected:
	Int NumRefs;											///< +0x04
};

class DX8VertexBufferClass : public RefCountClass { };
class DX8IndexBufferClass : public RefCountClass { };

#define REF_PTR_RELEASE(p)									\
	{														\
		if (p)												\
		{													\
			(p)->Release_Ref();								\
			(p) = NULL;										\
		}													\
	}

struct W3DVertexBuffer
{
	unsigned char m_unreconstructed_00[0x10];
	W3DVertexBuffer *m_nextVB;								///< +0x10
	DX8VertexBufferClass *m_DX8VertexBuffer;				///< +0x14
};

struct W3DIndexBuffer
{
	unsigned char m_unreconstructed_00[0x0C];
	W3DIndexBuffer *m_nextIB;								///< +0x0C
	DX8IndexBufferClass *m_DX8IndexBuffer;					///< +0x10
};

enum { MAX_FVF = 18 };

class W3DBufferManager
{
public:
	void freeAllSlots( void );
	void freeAllBuffers( void );

private:
	unsigned char m_unreconstructed_00[0x9000];
	W3DVertexBuffer *m_W3DVertexBuffers[MAX_FVF];			///< +0x09000
	unsigned char m_unreconstructed_9048[0x253CC - 0x9048];
	Int m_numEmptyVertexBuffersAllocated;					///< +0x253CC
	unsigned char m_unreconstructed_253d0[0x263D0 - 0x253D0];
	W3DIndexBuffer *m_W3DIndexBuffers;						///< +0x263D0
	unsigned char m_unreconstructed_263d4[0x42658 - 0x263D4];
	Int m_numEmptyIndexBuffersAllocated;					///< +0x42658
};

// ?freeAllBuffers@W3DBufferManager@@QAEXXZ
void W3DBufferManager::freeAllBuffers(void)
{
	Int i;

	//Make sure all slots are free
	freeAllSlots();	///<release all slots to pool.

	for (i=0; i<MAX_FVF; i++)
	{
		W3DVertexBuffer *vb = m_W3DVertexBuffers[i];
		while (vb)
		{
			REF_PTR_RELEASE(vb->m_DX8VertexBuffer);
			m_numEmptyVertexBuffersAllocated--;
			vb=vb->m_nextVB;	//get next vertex buffer of this type
		}
		m_W3DVertexBuffers[i]=NULL;
	}

	W3DIndexBuffer *ib = m_W3DIndexBuffers;
	while (ib)
	{
		REF_PTR_RELEASE(ib->m_DX8IndexBuffer);
		m_numEmptyIndexBuffersAllocated--;
		ib=ib->m_nextIB;	//get next vertex buffer of this type
	}
	m_W3DIndexBuffers=NULL;
}
