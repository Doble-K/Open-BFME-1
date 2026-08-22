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
// WHAT THE SPAN DOES SAY ABOUT ITSELF: 0x00807A00 logs a line beginning
// "dirtyaddr: output buffer too small", which is DirtySock naming its address
// module by its own source file.  That covers the three bodies here that
// convert an address between its binary and "$%08x" text forms; it says
// nothing about the other two, which is why the file is still named for its
// address.
//
// sprintf is reached by a DIRECT rel32 to the import stub at 0x009F6DE2 rather
// than through __imp__sprintf, so this TU did not see <stdio.h> -- the same
// reason Y2ProtoMangleHelpers.cpp declares it itself.
extern "C" int sprintf( char *buffer, const char *format, ... );

// ------------------------------------------------------------------ callees
// Addresses read from the REL32 at the call sites; each is pinned in
// reverse/symbols.csv and derived from its address.
void *Rva007FDFF0Connect( const char *host, int timeout );  // 0x007FDFF0
int   Rva00807960( const char *host, int timeout );         // 0x00807960
unsigned int Rva007FF9F0Swap32( unsigned int value );       // 0x007FF9F0
unsigned int Rva007EB410AdapterInfo( int selector, int a, int b );  // 0x007EB410
unsigned int Rva007FFAD0( unsigned int value );             // 0x007FFAD0

// Both reached by a direct rel32 to their import stubs, like sprintf above.
extern "C" unsigned int strtoul( const char *text, char **end, int base );
extern "C" void *memcpy( void *dest, const void *src, unsigned int count );

void Rva007FE780Printf( const char *format, ... );          // 0x007FE780
int  Rva00808220( void *a, unsigned int b, void *c, void *d, int e );  // 0x00808220
void Rva007FD3F0SocketClose( void *socket );                // 0x007FD3F0
void Rva007F0030Free( void *block );                        // 0x007F0030
void Rva007FEAA0ListReset( void *list );                    // 0x007FEAA0

// Two 28-byte forwarders that do nothing but pass their two arguments through
// and let /GZ check the frame afterwards.  They are separate functions rather
// than one, and separate from their callees, which is all the bytes say.
void *Rva00807920( const char *host, int timeout )
{
	return Rva007FDFF0Connect( host, timeout );
}

int Rva00807940( const char *host, int timeout )
{
	return Rva00807960( host, timeout );
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

// 0x00807A00 IS THE INVERSE of the two bodies above: it reads a "$xxxxxxxx"
// text form back into four bytes.  The parse starts at text + 1, which is what
// skips the '$' the formatter writes, and it is base 16; the result goes
// through the same transform at 0x007FFAD0 that the sibling at 0x007FF9F0
// applies in the other direction.
//
// THE RETURN IS A CHARACTER COUNT, NOT A STATUS.  Nine is exactly the width of
// "$" plus eight hex digits, so the caller is being told how much text was
// consumed; the failure arm returns zero for the same reason.  That failure is
// a BUFFER check and not an input check -- the only thing tested is that the
// caller offered four bytes, and it is the check that logs the module's name.
//
// The address is copied out with memcpy rather than stored, so the destination
// needs no alignment -- the opposite of the guard 0x00807AB0 puts on its own
// source pointer, and worth noticing because the two are a pair.
int Rva00807A00( void *dest, int destSize, const char *text )
{
	unsigned int uAddress;

	if( destSize < 4 )
	{
		Rva007FE780Printf( "dirtyaddr: output buffer too small\n" );
		return 0;
	}

	uAddress = strtoul( text + 1, 0, 16 );
	uAddress = Rva007FFAD0( uAddress );
	memcpy( dest, &uAddress, 4 );
	return 9;
}

// Two more wrappers over the 841-byte body at 0x00808220, and the difference
// between them is the whole point: both append a fifth argument of zero, but
// 0x008085A0 first runs the text form through the parser above and passes what
// came out, while 0x008081F0 passes its caller's second argument straight
// through.  So the pair is one entry point in a binary flavour and a text
// flavour, which is also why the parser's nine-character return is discarded
// here -- the caller of the text flavour never sees it.
int Rva008081F0( void *a, unsigned int b, void *c, void *d )
{
	return Rva00808220( a, b, c, d, 0 );
}

int Rva008085A0( void *a, const char *text, void *c, void *d )
{
	unsigned int uAddress;

	Rva00807A00( &uAddress, 4, text );
	return Rva00808220( a, uAddress, c, d, 0 );
}

// The record 0x00808140 tears down.  Only the three offsets that body touches
// are evidence: a socket at +0x00, something 0x007FEAA0 resets at +0x0C, and a
// singly linked list at +0x30 whose nodes link through their own first word.
// The span between is padding here and names nothing.
struct Rva00808140Node
{
	Rva00808140Node *m_next;         // +0x00
};

struct Rva00808140Ref
{
	void            *m_socket;       // +0x00
	int              m_pad04;
	int              m_pad08;
	char             m_sub0C[ 0x24 ];// +0x0C
	Rva00808140Node *m_list;         // +0x30
};

// 0x00808140 IS A DESTRUCTOR, and the ORDER is what it says: close the socket
// first, then drain the list, then tear down the sub-object at +0x0C, then free
// the record itself.  Nothing is nulled on the way out, so this is the last
// thing that ever touches the record.
//
// THE WHOLE BODY IS WRAPPED IN A NULL CHECK RATHER THAN GUARDED BY AN EARLY
// RETURN.  Retail's is one `je` over everything; an early return compiles to a
// short `jne` over a `jmp`, two instructions where retail has one, and shifts
// every displacement after it.
//
// The drain re-reads the head each time round instead of walking a cursor --
// it unlinks the first node, frees it, and tests the head again -- so the list
// is left consistent at every step even though nothing else can see it.
void Rva00808140( Rva00808140Ref *ref )
{
	Rva00808140Node *node;

	if( ref != 0 )
	{
		Rva007FD3F0SocketClose( ref->m_socket );

		while( ref->m_list != 0 )
		{
			node = ref->m_list;
			ref->m_list = node->m_next;
			Rva007F0030Free( node );
		}

		Rva007FEAA0ListReset( ref->m_sub0C );
		Rva007F0030Free( ref );
	}
}

// The object 0x007FDFF0 hands back.  Two of its words are CALLED with the
// object itself as the only argument and the stack cleaned by the caller, so
// they are __cdecl function pointers and not a C++ vtable -- a thiscall slot
// would pass the object in ecx and pop nothing.  Only the three offsets
// 0x00807960 touches are evidence.
struct Rva00807960Conn;
typedef int ( __cdecl *Rva00807960Proc )( Rva00807960Conn *conn );

struct Rva00807960Conn
{
	int             m_pad00;
	int             m_result;       // +0x04
	Rva00807960Proc m_poll;         // +0x08
	Rva00807960Proc m_close;        // +0x0C
};

__declspec(dllimport) void __stdcall Rva01358F30Sleep( unsigned int ms );

// 0x00807960 IS THE BLOCKING FORM of the connect at 0x007FDFF0, which is
// itself non-blocking: it starts the connection, then spins on the object's
// own poll until that reports non-zero, sleeping ten milliseconds between
// tries, and only then reads the result out of +0x04 and closes.
//
// THE SLEEP IS UNCONDITIONAL AND THERE IS NO DEADLINE.  The timeout argument
// goes to the connect and is never looked at again here, so if the poll never
// succeeds this loop never ends -- whatever bounds it lives inside the object,
// not in this body.
//
// The result is read BEFORE the close and the close's own return is dropped,
// so the object is expected to still be readable at that point and the caller
// learns nothing about whether tearing it down worked.  On a failed connect
// the zero the function starts with is what comes back, which is the same
// value a poll that succeeded with a zero result would give.
int Rva00807960( const char *host, int timeout )
{
	Rva00807960Conn *conn;
	int result;

	result = 0;
	conn = (Rva00807960Conn *)Rva007FDFF0Connect( host, timeout );

	if( conn != 0 )
	{
		while( conn->m_poll( conn ) == 0 )
			Rva01358F30Sleep( 10 );

		result = conn->m_result;
		conn->m_close( conn );
	}

	return result;
}
