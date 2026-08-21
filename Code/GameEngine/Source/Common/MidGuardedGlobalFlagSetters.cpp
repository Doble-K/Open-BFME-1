// 22 identical 22-byte __cdecl predicates:
//
//     mov eax,[<DIR32>] / test eax,eax / je +7
//     mov byte ptr [eax+<OFF>],<0|1> / mov eax,1 / ret
//
// WHAT THE BYTES SHOW.  All 22 read the SAME global pointer (0x012ED5C8), skip
// the store when it is null, and return 1 either way -- the return value does
// not report whether the store happened, so it is a fixed success code, not the
// flag.  `mov eax,1` rather than `mov al,1` proves an int-width return: a `bool`
// return of `true` compiles to `mov al,1` at 3 bytes and would be two bytes
// shorter.  The store is byte-wide, so the flag is a byte member.
//
// TWO AXES: the byte offset (22 distinct values from 0xA74 to 0x11FC) and the
// stored value (0 in three members, 1 in the other nineteen).  Because the same
// global is named by every member, one extern serves all 22 and the DIR32
// consistency check sees a single symbol resolving to a single address.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the offsets
// are spelled as indices into an opaque byte block rather than named fields.

class MidGuardedFlagBlock
{
public:
	char m_bytes[ 0x1200 ];
};

extern MidGuardedFlagBlock *g_midGuardedFlagBlock;

#define BFME_GUARDED_FLAG_SET( NAME, OFFSET, VALUE )                      \
	int NAME( void )                                                      \
	{                                                                     \
		if( g_midGuardedFlagBlock )                                       \
			g_midGuardedFlagBlock->m_bytes[ OFFSET ] = VALUE;             \
		return 1;                                                         \
	}

BFME_GUARDED_FLAG_SET( Rva000608E0, 0xBC4, 0 )
BFME_GUARDED_FLAG_SET( Rva000609E0, 0xE54, 1 )
BFME_GUARDED_FLAG_SET( Rva00060AE0, 0xA7D, 1 )
BFME_GUARDED_FLAG_SET( Rva00060B00, 0xA7E, 1 )
BFME_GUARDED_FLAG_SET( Rva00060D80, 0xB7D, 1 )
BFME_GUARDED_FLAG_SET( Rva00060DA0, 0xA7F, 0 )
BFME_GUARDED_FLAG_SET( Rva00060DC0, 0xAAC, 1 )
BFME_GUARDED_FLAG_SET( Rva00060DE0, 0xA74, 1 )
BFME_GUARDED_FLAG_SET( Rva00060E00, 0xA95, 1 )
BFME_GUARDED_FLAG_SET( Rva00060E20, 0xA97, 1 )
BFME_GUARDED_FLAG_SET( Rva00060E40, 0xA9C, 1 )
BFME_GUARDED_FLAG_SET( Rva00060E60, 0xA9D, 1 )
BFME_GUARDED_FLAG_SET( Rva00060E80, 0xA9E, 1 )
BFME_GUARDED_FLAG_SET( Rva00060EA0, 0xA9F, 1 )
BFME_GUARDED_FLAG_SET( Rva00060EC0, 0xAA0, 1 )
BFME_GUARDED_FLAG_SET( Rva00060F20, 0xBC5, 1 )
BFME_GUARDED_FLAG_SET( Rva00060F80, 0xA7C, 1 )
BFME_GUARDED_FLAG_SET( Rva00060FE0, 0xC0A, 1 )
BFME_GUARDED_FLAG_SET( Rva000610D0, 0xC70, 1 )
BFME_GUARDED_FLAG_SET( Rva000610F0, 0xDBC, 1 )
BFME_GUARDED_FLAG_SET( Rva00061160, 0xA8F, 0 )
BFME_GUARDED_FLAG_SET( Rva00061560, 0x11FC, 1 )
