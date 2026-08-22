// cl: /DNDEBUG /MD /GX /Od /GZ /GS
// EA's DirtySock netconn.  THE MODULE NAMES ITSELF AND SO DOES THE FUNCTION:
// the body here logs "netconn: warning - calling NetConnStatus() while module
// is not initialized", which gives both the source file this belongs to and
// what this body is called.  The /Od /GZ signature is the same one the rest of
// this directory carries.
//
// The three module words it reports are address-derived; nothing names them but
// the selectors they answer.
extern int g_Rva0130A590State;   // 'open'
extern int g_Rva0130A594Conn;    // 'conn'
extern int g_Rva0130A598Online;  // 'onln'

int  Rva007FE780Printf( const char *format, ... );    // 0x007FE780
int  Rva007FDEE0( void );                             // 0x007FDEE0
unsigned int Rva007EB520( void *adapter );            // 0x007EB520
extern "C" void *memcpy( void *dest, const void *src, unsigned int count );

// FIVE SELECTORS, and the first one is answered BEFORE the initialisation
// guard: 'open' reports the module's own state word, so a caller can ask
// whether netconn is up without tripping the warning that every other selector
// trips when it is not.  That ordering is the point of the body's shape.
//
// 'conn' and 'onln' are two more module words, 'addr' defers to the address
// self test at 0x007FDEE0, and 'macx' fills the caller's buffer with six bytes
// -- a MAC address -- taken from the 0xF0-byte block /GZ names `Adapter`.
// Anything else is -1.
//
// THE 'macx' SUCCESS TEST CAN NEVER FAIL, and that is retail's.  `test eax,eax`
// clears the carry flag, so the `jb` that follows it is never taken and the
// `return 0` it guards is unreachable.  That is what an unsigned result
// compared `>= 0` compiles to at /Od -- the comparison is vacuous, MSVC emits
// it anyway, and writing the test as a signed one produces a different
// instruction.  So the helper's result is unsigned and the failure arm is dead.
//
// The third parameter is never read.  Callers pass it; this body does not use
// it, and it cannot be dropped without changing every call site's stack.
int Rva007EB410NetConnStatus( int selector, void *buffer, int bufferSize )
{
	char Adapter[ 0xF0 ];

	if( selector == 'open' )
		return g_Rva0130A590State;

	if( g_Rva0130A590State != 1 )
	{
		Rva007FE780Printf( "netconn: warning - calling NetConnStatus() "
				"while module is not initialized\n" );
		return -1;
	}

	if( selector == 'onln' )
		return g_Rva0130A598Online;

	if( selector == 'conn' )
		return g_Rva0130A594Conn;

	if( selector == 'addr' )
		return Rva007FDEE0();

	if( selector == 'macx' )
	{
		if( Rva007EB520( Adapter ) >= 0 )
		{
			memcpy( buffer, Adapter, 6 );
			return 1;
		}
		return 0;
	}

	return -1;
}
