// cl: /DNDEBUG /MD /GX /Od /GZ /GS
// Another module in the 0x00806480..0x00806B10 span, carrying the same /Od /GZ
// signature as the rest of this directory -- a frame pointer for code with no
// register pressure and `cmp ebp,esp` into the stack-check helper at 0x009F7502.
// Nothing in these four bodies names it: there is no string and no selector, so
// the file name and every function name are derived from addresses and assert
// nothing.  What the bodies DO show is that they share one record layout, which
// is why they share a file.

// 0x0080B070, the teardown all three destructors here hand the record's first
// pointer to; address-derived and pinned.
void Rva0080B070Destroy( void *object );

// 0x007F0030, the one-argument release the rest of this directory uses.
void Rva007F0030Free( void *block );

// An import thunk the ledger already names; the C spelling is what this call
// site needs.
extern "C" void Rva0081BDE4( void );

__declspec(dllimport) void __stdcall Rva01358F30Sleep( unsigned int ms );

// Only the five offsets these bodies touch are evidence.  +0x00 is a sub-object
// with its own teardown, +0x70 and +0x7C are plain blocks, +0x5C takes a state
// constant and +0x8C a boolean.  Everything between is padding and names nothing.
struct Rva00806580Record
{
	void *m_field00;             // +0x00
	char  m_pad04[ 0x58 ];
	int   m_field5C;             // +0x5C
	char  m_pad60[ 0x10 ];
	void *m_field70;             // +0x70
	char  m_pad74[ 0x08 ];
	void *m_field7C;             // +0x7C
	char  m_pad80[ 0x0C ];
	short m_field8C;             // +0x8C
};

// 0x00806580 IS THE FULL TEARDOWN and the sleep in the middle is the whole
// story: it tears the sub-object down, WAITS 50 MILLISECONDS, calls an import,
// and only then frees the two blocks and the record.  A destructor that has to
// pause before releasing memory is waiting for something else to stop touching
// it -- the sub-object almost certainly owns a thread -- and the pause is
// unconditional, taken even when there was no sub-object to tear down.
//
// The record's own pointer is NOT nulled on the way out, unlike in the two
// bodies below; nothing can read it again, because the record is freed.
void Rva00806580( Rva00806580Record *record )
{
	if( record->m_field00 != 0 )
		Rva0080B070Destroy( record->m_field00 );

	Rva01358F30Sleep( 50 );
	Rva0081BDE4();

	if( record->m_field7C != 0 )
		Rva007F0030Free( record->m_field7C );

	if( record->m_field70 != 0 )
		Rva007F0030Free( record->m_field70 );

	Rva007F0030Free( record );
}

// 0x008068B0 and 0x00806A10 ARE BYTE-IDENTICAL apart from the displacements of
// their own two calls, and retail carries both.  That is not identical-code
// folding failing: folding would have left ONE body and two names pointing at
// it, and these are two bodies at two addresses.  So the source really does say
// this twice, and it is written out twice here rather than aliased.
//
// Both are the partial reset the full teardown above is the destructive form of:
// same sub-object, same +0x70 block, but each pointer is NULLED after release
// and the record survives with its state set to 4.
int Rva008068B0( Rva00806580Record *record )
{
	if( record->m_field00 != 0 )
	{
		Rva0080B070Destroy( record->m_field00 );
		record->m_field00 = 0;
	}

	if( record->m_field70 != 0 )
	{
		Rva007F0030Free( record->m_field70 );
		record->m_field70 = 0;
	}

	record->m_field5C = 4;
	return 0;
}

int Rva00806A10( Rva00806580Record *record )
{
	if( record->m_field00 != 0 )
	{
		Rva0080B070Destroy( record->m_field00 );
		record->m_field00 = 0;
	}

	if( record->m_field70 != 0 )
	{
		Rva007F0030Free( record->m_field70 );
		record->m_field70 = 0;
	}

	record->m_field5C = 4;
	return 0;
}

// 0x00806A70 stores a comparison, not its argument: the flag at +0x8C is set
// only when the value handed in is exactly 1, and it is stored SIXTEEN BITS
// WIDE.  Any other value -- including 2 -- clears it.
void Rva00806A70( Rva00806580Record *record, int value )
{
	record->m_field8C = (short)( value == 1 );
}
