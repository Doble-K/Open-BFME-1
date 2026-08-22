// cl: /DNDEBUG /MD /GX /Od /GZ /GS
// EA's DirtySock again -- a module in the 0x00807900..0x00808600 span that the
// bytes do NOT name.  Every body here opens a frame for code with no register
// pressure, fills its locals with 0xCCCCCCCC and ends `cmp ebp,esp` into the
// stack-check helper at 0x009F7502, which is the same /Od /GZ signature the
// other files in this directory carry, and the only string reachable from the
// whole span is "$%08x".  The directory and the file name are therefore
// inferences; every function name below is derived from an address and asserts
// nothing about identity.
//
// sprintf is reached by a DIRECT rel32 to the import stub at 0x009F6DE2 rather
// than through __imp__sprintf, so this TU did not see <stdio.h> -- the same
// reason Y2ProtoMangleHelpers.cpp declares it itself.
extern "C" int sprintf( char *buffer, const char *format, ... );

// ------------------------------------------------------------------ callees
// Addresses read from the REL32 at the call sites; each is pinned in
// reverse/symbols.csv and derived from its address.
void *Rva007FDFF0Connect( const char *host, int timeout );  // 0x007FDFF0
int   Rva00807960( void *a, void *b );                      // 0x00807960
unsigned int Rva007FF9F0Swap32( unsigned int value );       // 0x007FF9F0
unsigned int Rva007EB410AdapterInfo( int selector, int a, int b );  // 0x007EB410

// Two 28-byte forwarders that do nothing but pass their two arguments through
// and let /GZ check the frame afterwards.  They are separate functions rather
// than one, and separate from their callees, which is all the bytes say.
void *Rva00807920( const char *host, int timeout )
{
	return Rva007FDFF0Connect( host, timeout );
}

int Rva00807940( void *a, void *b )
{
	return Rva00807960( a, b );
}

// 0x008081C0 IS A SWITCH WITH ONE CASE, and the copy into a stack temp is what
// says so: MSVC spills a switch expression to its own slot at /Od, while an
// `if` compares the parameter where it sits.  The single selector is
// 0x74746C76, i.e. the multi-character literal 'ttlv' -- the same DirtySock
// control-selector convention 0x007FDEB0's 'xmap'/'xdns' pair and 0x008053C0's
// 'bind' use -- and it stores its third argument at +0x38.  The receiver's
// layout is not known here, so the store is written through the address rather
// than given an invented field name.
void Rva008081C0( void *ref, int selector, int value )
{
	switch( selector )
	{
	case 'ttlv':
		*(int *)( (char *)ref + 0x38 ) = value;
		break;
	}
}

// 0x00807AB0 FORMATS A DWORD AS "$%08x", and the guard in front of it is an
// ALIGNMENT test: the source pointer is rejected when it is null OR when its
// low two bits are set, so the dword is read directly rather than byte-wise.
// Both rejections share one `return 0`, which is why retail's second test jumps
// FORWARD over that return instead of into it -- the `||` shape, not `&&`.
//
// The value passes through 0x007FF9F0 on the way.  Its sibling at 0x007FFAD0,
// already ledgered, is a byte swap over the same one-dword-in one-dword-out
// shape; nothing in THIS body proves that is what happens here, only that the
// value is transformed before it is printed.
int Rva00807AB0( char *dest, const void *src )
{
	unsigned int value;

	if( src == 0 || ( (unsigned int)src & 3 ) != 0 )
		return 0;

	value = Rva007FF9F0Swap32( *(const unsigned int *)src );
	sprintf( dest, "$%08x", value );
	return 1;
}

// 0x00807B10 asks the adapter query at 0x007EB410 for the selector 0x61646472
// -- 'addr' -- and runs the answer straight through the formatter above.  /GZ
// names the local uLocalAddr and guards it on both sides because its address is
// taken, which is what makes the frame 0x0C rather than 0x04.  The return is a
// constant 1: this body cannot fail, and does not look at whether either
// callee did.
int Rva00807B10( char *dest )
{
	unsigned int uLocalAddr;

	uLocalAddr = Rva007EB410AdapterInfo( 'addr', 0, 0 );
	Rva00807AB0( dest, &uLocalAddr );
	return 1;
}
