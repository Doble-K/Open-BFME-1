// Five 73-byte __cdecl functions that pull items one at a time out of a source
// object and feed them to a sink until the sink says stop or the source runs
// dry, carrying two byte flags by address across every call:
//
//     bool a = false, b = false;
//     item = source->next( 0 );
//     while ( item ) { if ( !sink->handle( item, &b, &a ) ) break;
//                      item = source->next( 0 ); }
//
// WHAT THE BYTES SHOW.  Nothing reads ecx on entry and the `ret` is bare, so
// these are __cdecl free functions, not members.  The single `push ecx` in the
// prologue is the four bytes of locals: both flags live in it, at [entry-1] and
// [entry-2], and both are zeroed BEFORE the first source call, so they are
// initialised at declaration rather than assigned in the loop.
//
// The source call is entered with ecx = the first parameter and one pushed
// dword that the CALLEE pops -- __thiscall, one argument, returning a pointer
// (`test eax,eax`).  The sink call is entered with ecx = a different parameter
// and three pushed dwords, returning one byte (`test al,al`).  Two addresses of
// the SAME two locals are handed over on every iteration, so the sink writes
// through them and the caller keeps the values alive across iterations.
//
// THE MIDDLE PARAMETER IS NEVER READ.  The sink pointer is fetched from
// [entry+0xC], not [entry+8], which leaves a whole dword of argument space
// untouched; only the argument OFFSETS can show this, and they do.
//
// The loop is the rotated `while`: the source call appears twice, once ahead of
// the entry test and once at the bottom feeding a `jne` back to the top.  A
// `do`/`while` would have one copy and no leading test.
//
// ONE AXIS: the sink's REL32.  The source callee, both parameter offsets, both
// flag slots and the whole control flow are identical in all five rows, and the
// five sinks are five distinct addresses.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the bytes
// do not say what is being drained, what the two flags mean, or whether the
// five sinks share a base.

class GenItem;

class Gen008509C0
{
public:
	GenItem *next( int flags );
};

#define S3_DRAIN( NAME, ADDR )                                            \
	class Gen##ADDR                                                       \
	{                                                                     \
	public:                                                               \
		bool handle( GenItem *item, bool *first, bool *second );          \
	};                                                                    \
	void NAME( Gen008509C0 *source, int unused, Gen##ADDR *sink )         \
	{                                                                     \
		bool first = false;                                               \
		bool second = false;                                              \
		GenItem *item = source->next( 0 );                                \
		while( item )                                                     \
		{                                                                 \
			if( !sink->handle( item, &first, &second ) )                  \
				break;                                                    \
			item = source->next( 0 );                                     \
		}                                                                 \
	}

S3_DRAIN( Rva001EB560, 00049A2B )
S3_DRAIN( Rva0029D3D0, 00006F78 )
S3_DRAIN( Rva00369AD0, 000140D8 )
S3_DRAIN( Rva00369B30, 0002E893 )
S3_DRAIN( Rva0061CD10, 000341FD )
