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
unsigned int Rva007EB520NetConnMAC( void *adapter );   // 0x007EB520
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
		if( Rva007EB520NetConnMAC( Adapter ) >= 0 )
		{
			memcpy( buffer, Adapter, 6 );
			return 1;
		}
		return 0;
	}

	return -1;
}

// The NCB Win32's netbios API takes.  Its field offsets are not a guess: the
// body below writes the command at +0x00, reads the return code at +0x01, sets
// the buffer at +0x04 and the length at +0x08, copies a name to +0x0A and
// steps the LANA number at +0x30 -- which is the documented layout, and 0x40 is
// the size it memsets.
struct Rva007EB520Ncb
{
	unsigned char  ncb_command;      // +0x00
	unsigned char  ncb_retcode;      // +0x01
	unsigned char  ncb_lsn;
	unsigned char  ncb_num;
	void          *ncb_buffer;       // +0x04
	unsigned short ncb_length;       // +0x08
	char           ncb_callname[ 16 ];  // +0x0A
	char           ncb_name[ 16 ];   // +0x1A
	unsigned char  ncb_rto;
	unsigned char  ncb_sto;
	void         (*ncb_post)( void );
	unsigned char  ncb_lana_num;     // +0x30
	unsigned char  ncb_cmd_cplt;
	char           ncb_reserve[ 10 ];
	void          *ncb_event;
};

extern "C" unsigned char __stdcall Netbios( Rva007EB520Ncb *ncb );
extern "C" char *strcpy( char *dest, const char *src );
extern "C" void *memset( void *dest, int value, unsigned int count );

// 0x007EB520 IS NetConnMAC and it says so twice, in "NetConnMAC: The NCBRESET
// return code is: 0x%x" and "NetConnMAC: Could not find any valid network
// addapters!" -- retail's spelling of `adapters` included.  The first of those
// also names the command: 0x32 is NCBRESET and the 0x33 the second half uses is
// NCBASTAT, the adapter-status query that returns a MAC.
//
// IT RESETS LANAS UNTIL ONE WORKS.  The loop runs 0 through 9 and BREAKS on the
// first reset that succeeds, so the LANA the second half queries is whichever
// one that was -- which is why the post-loop test on the same counter is not
// redundant: reaching 10 means every LANA failed.  Return code 0x23 is expected
// and stays quiet; every other failure is logged and the walk continues.
//
// THE CALLNAME COPY OVERRUNS BY ONE.  "*" followed by fifteen spaces is sixteen
// characters, and strcpy writes a seventeenth for the terminator -- into the
// first byte of ncb_name, which the memset has already zeroed.  It is harmless
// and it is retail's.
//
// The buffer is handed over with a length of 0xF0, which is the size of the
// block NetConnStatus declares for it, and only six bytes of the answer are
// ever used.  A failed query returns -1 WITHOUT logging: the "no adapters"
// line belongs to the loop running out, not to the query failing.
unsigned int Rva007EB520NetConnMAC( void *adapter )
{
	Rva007EB520Ncb ncb;
	int result;
	int lana;

	memset( &ncb, 0, 0x40 );
	ncb.ncb_command = 0x32;

	for( ncb.ncb_lana_num = 0; ncb.ncb_lana_num < 10; ncb.ncb_lana_num++ )
	{
		result = Netbios( &ncb );
		if( result != 0 )
		{
			if( result != 0x23 )
				Rva007FE780Printf(
						"NetConnMAC: The NCBRESET return code is: 0x%x \n",
						ncb.ncb_retcode );
		}
		else
		{
			break;
		}
	}

	if( ncb.ncb_lana_num < 10 )
	{
		lana = ncb.ncb_lana_num;
		memset( &ncb, 0, 0x40 );
		ncb.ncb_command = 0x33;
		ncb.ncb_lana_num = (unsigned char)lana;
		strcpy( ncb.ncb_callname, "*               " );
		ncb.ncb_buffer = adapter;
		ncb.ncb_length = 0xF0;

		if( Netbios( &ncb ) == 0 )
			return 0;
	}
	else
	{
		Rva007FE780Printf(
				"NetConnMAC: Could not find any valid network addapters!\n" );
	}

	return (unsigned int)-1;
}
