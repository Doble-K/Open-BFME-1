// cl: /DNDEBUG /MD /GX /Od /GZ /GS
// Three small /Od /GZ bodies from the 0x007EBAE0..0x007EC780 span, sharing this
// file because they share a compiler line and a subject: bounded string work
// against a caller's buffer.  Nothing in them names a module -- no string and no
// selector is reachable -- so the file name and every function name here are
// derived from addresses.

// 0x007EBAE0 is a GET-AND-SET on a single byte of global state: it saves the old
// value, stores the new one, and returns what was there.  A caller can therefore
// restore it, which is what makes this a scoped override rather than a setter.
// The old value goes through a one-byte local rather than staying in a register,
// which is why the frame exists at all.
extern char g_Rva012C391CFlag;

// 0x007EBCA0, the tag lookup both bodies at the end of this file feed; pinned
// by address and still a dump.
// A 256-byte case-folding table at 0x0112A210; the lookup below indexes it
// with a byte read through movzx, so it is unsigned.
extern const unsigned char g_Rva0112A210Lower[];

// Defined at the end of this file; the three wrappers above it all call it.
char *Rva007EBCA0( const char *text, const char *tag );   // 0x007EBCA0

// Reached by a direct rel32 to the import stub, so this TU never saw <stdio.h>.
extern "C" int sprintf( char *buffer, const char *format, ... );
extern "C" char *strcpy( char *dest, const char *src );
extern "C" char *strcat( char *dest, const char *src );

char Rva007EBAE0( char value )
{
	char old;

	old = g_Rva012C391CFlag;
	g_Rva012C391CFlag = value;
	return old;
}

// 0x007EC280 IS A BOUNDED COPY THAT REPORTS WHAT IT WROTE.  The counter starts
// at the caller's size and is spent per byte, so the return -- size minus what
// is left -- is the number of bytes copied, terminator included.
//
// THE SOURCE TEST IS PART OF THE LOOP CONDITION, not a break: retail leaves the
// loop with a single `je` at that test, which is what a second `&&` operand
// compiles to; a break inside the body is `jne` over a `jmp` and moves every
// displacement after it.
//
// The bound is `> 1`, so one byte is always held back, and the terminator is
// then written only when the counter is still positive -- which it always is
// after that loop.  A size of zero skips the loop and the terminator both, and
// returns zero.
int Rva007EC280( char *dest, int size, const char *src )
{
	int left;

	for( left = size; left > 1 && *src != 0; left-- )
	{
		*dest = *src;
		dest++;
		src++;
	}

	if( left > 0 )
		*dest = 0;

	return size - left;
}

// 0x007EC730 WRITES A TAG AND ITS SEPARATOR.  It copies the source up to its
// terminator and appends '=', returning the position after it, so a caller
// chains this to build "name=value" without measuring anything.
//
// IT IS UNBOUNDED.  There is no count and no limit: the only thing that stops
// the copy is the source's own terminator, and the caller's buffer is not
// consulted.  That is what the separate first argument is for -- given a null
// source, this writes a terminator through THAT pointer and returns the
// destination untouched, which is the only way it reports anything at all.
char *Rva007EC730( char *empty, char *dest, const char *src )
{
	if( src == 0 )
	{
		*empty = 0;
	}
	else
	{
		while( *src != 0 )
		{
			*dest = *src;
			dest++;
			src++;
		}

		*dest = '=';
		dest++;
	}

	return dest;
}

// 0x007EBF20 LOOKS UP A NUMBERED TAG.  It builds the name with "%s%d" -- a
// base and an index -- into a 0x100-byte buffer /GZ names `strTag`, and hands
// that to the lookup.  So the record's tags are things like "addr0",
// "addr1"; the numbering is in the name and not in the lookup.
//
// The buffer is 0x100 and the format is unbounded: a base name long enough
// overruns it, and nothing here checks.
char *Rva007EBF20( const char *text, const char *name, int index )
{
	char strTag[ 0x100 ];

	sprintf( strTag, "%s%d", name, index );
	return Rva007EBCA0( text, strTag );
}

// 0x007EBFC0 LOOKS UP THE TAG NAMED "~~" and then trims what it finds: it
// steps over every byte at or below 0x20 -- space and everything below it,
// which is leading whitespace and control characters together -- and reports a
// value that turns out to be empty as ABSENT, by returning null rather than a
// pointer to the terminator.
//
// So a caller cannot tell "no such tag" from "tag present but blank", and the
// trim is what collapses the two.  The comparison is `<= 0x20` on a value read
// with movzx, so it is UNSIGNED: a high byte is not whitespace here.
char *Rva007EBFC0( const char *text )
{
	char *value;

	value = Rva007EBCA0( text, "~~" );

	if( value != 0 )
	{
		while( *(unsigned char *)value != 0
				&& *(unsigned char *)value <= 0x20 )
			value++;

		if( *(unsigned char *)value == 0 )
			value = 0;
	}

	return value;
}

// 0x007EBE20 LOOKS UP A TAG BUILT FROM TWO PIECES, and its three arms are the
// whole content: a null first piece looks up the second alone, a null second
// looks up the first alone, and two present pieces are CONCATENATED into a
// 0x100-byte buffer /GZ names `name` and looked up together.  Two nulls fall
// into the first arm and look up nothing.
//
// The join is strcpy then strcat with no separator, so "addr" and "0" make
// "addr0" -- the same names 0x007EBF20 builds with "%s%d", reached the other
// way round.  It is unbounded for the same reason that one is.
//
// The result is initialised to null before the arms and every arm assigns it,
// so that store is dead; it is retail's and removing it removes an instruction.
char *Rva007EBE20( const char *text, const char *prefix, const char *suffix )
{
	char name[ 0x100 ];
	char *result;

	result = 0;

	if( prefix == 0 )
	{
		result = Rva007EBCA0( text, suffix );
	}
	else if( suffix == 0 )
	{
		result = Rva007EBCA0( text, prefix );
	}
	else
	{
		strcpy( name, prefix );
		strcat( name, suffix );
		result = Rva007EBCA0( text, name );
	}

	return result;
}

// 0x007EBCA0 IS THE TAG LOOKUP the three wrappers above all feed, and it works
// BACKWARDS.  It scans forward for a separator -- '=' or ':' -- and then walks
// back from there comparing the tag's last character first, so a tag is found
// by where its separator is rather than by where its name starts.  That is why
// the tag's end is measured up front.
//
// THE SEPARATOR TEST IS A NEGATED GUARD WITH A `continue`, not a positive `if`
// around the body.  Retail enters the body with a forward `je` from BOTH
// comparisons and falls into a short jump back to the loop; a positive `||`
// inverts the second test into a far `jne` instead, one byte longer and enough
// to move every displacement in the body.
//
// THE BACKWARD WALK'S THREE TESTS ARE ALL LOOP CONDITIONS, and the terminator
// check is a `break` rather than a `return 0`: retail leaves each of the three
// with ONE conditional jump to the same place, and the terminator's exit jumps
// to the function's own trailing `return 0` rather than making a second one.
// Writing any of them as an `if ... break` inside the body costs a byte each
// and a duplicated `xor eax,eax`.
//
// THE MATCH IS CASE-INSENSITIVE THROUGH A TABLE, not through tolower: both
// bytes are indexed into the 256-entry map at 0x0112A210.
//
// A MATCH ALSO HAS TO START ON A WORD BOUNDARY.  Running out of tag is not
// enough: the character before the name must be absent or at or below 0x20, so
// "peerIP=" does not match a request for "IP".  The scan continues from the
// same separator when that fails.
//
// THE END OF THE RECORD IS A SEPARATOR WITH NOTHING EITHER SIDE OF IT: a byte
// below 0x20 after it and whitespace before it stops the whole search and
// returns null.  That is the "~~=" terminator the wrapper above looks up by
// name, recognised here structurally rather than by text.
//
// The value returned skips one space after the separator if there is exactly
// one -- p + 2 rather than p + 1 -- and no more, so leading whitespace beyond
// that is the caller's problem.  It is 0x007EBFC0 that trims the rest.
char *Rva007EBCA0( const char *text, const char *tag )
{
	const char *p;
	const char *q;
	const char *r;
	const char *tagEnd;
	const char *tagPtr;
	const char *textPtr;
	const char *result;

	tagPtr = tag;
	textPtr = text;

	if( textPtr == 0 || *(unsigned char *)textPtr == 0 )
		return 0;

	if( tagPtr == 0 || *(unsigned char *)tagPtr == 0 )
		return 0;

	for( tagEnd = tagPtr; *(unsigned char *)tagEnd != 0; tagEnd++ )
		;
	tagEnd--;

	for( p = textPtr; *(unsigned char *)p != 0; p++ )
	{
		if( *(unsigned char *)p != '=' && *(unsigned char *)p != ':' )
			continue;

		{
			if( *(unsigned char *)( p + 1 ) < 0x20
					&& *(unsigned char *)( p - 1 ) <= 0x20 )
				break;

			for( q = p - 1, r = tagEnd;
					q >= textPtr && r >= tagPtr
						&& g_Rva0112A210Lower[ *(unsigned char *)q ]
							== g_Rva0112A210Lower[ *(unsigned char *)r ];
					q--, r-- )
			{
				if( r == tagPtr )
				{
					if( q == textPtr
							|| *(unsigned char *)( q - 1 ) <= 0x20 )
					{
						if( *(unsigned char *)( p + 1 ) == 0x20 )
							result = p + 2;
						else
							result = p + 1;

						return (char *)result;
					}
				}
			}
		}
	}

	return 0;
}

// 0x007EBB10 NORMALISES A RECORD IN PLACE, rewriting it over itself: the read
// and write pointers start together and the writer never overtakes the reader,
// because every run of control bytes collapses to one byte.
//
// IT RUNS IN TWO PASSES OVER THE SAME BUFFER.  The first replaces each run of
// bytes below 0x20 with the caller's separator and stops at the record
// terminator -- a '=' or ':' followed by a control byte, the same structural
// end 0x007EBCA0 recognises.  The second pass then rewrites what is LEFT AFTER
// that terminator with newline separators, and remembers each run's first
// character so the run ends where that character repeats.
//
// BETWEEN THE PASSES IT FIXES THE JOIN.  A trailing separator is replaced by a
// newline when there is more to come, and by a terminator when there is not, so
// the caller never sees a record ending in its own separator.  That is the only
// thing the two passes say to each other.
//
// The separator parameter is reused as a variable in the second pass, which is
// why it is not const: it holds the character each run began with.
//
// IT RETURNS NOTHING.  eax happens to hold the write pointer at the end,
// because the terminator is stored through it, but nothing sets a return value
// -- so a caller reading one is reading a side effect.  Declaring this to
// return that pointer adds an instruction retail does not have.
void Rva007EBB10( char *record, char separator )
{
	char *p;
	char *out;
	char *start;
	int extra;

	start = record;
	out = start;
	p = out;

	while( *(unsigned char *)p != 0 )
	{
		if( *(unsigned char *)p < 0x20 )
		{
			*out = separator;
			out++;

			while( *(unsigned char *)p > 0
					&& *(unsigned char *)p < 0x20 )
				p++;

			if( ( *(unsigned char *)p == '=' || *(unsigned char *)p == ':' )
					&& *(unsigned char *)( p + 1 ) < 0x20 )
				break;
		}
		else
		{
			*out = *p;
			out++;
			p++;
		}
	}

	if( out != start && *(unsigned char *)( out - 1 )
			== *(unsigned char *)&separator )
	{
		if( *(unsigned char *)&separator != 0x0A
				&& *(unsigned char *)p == 0 )
			extra = 0;
		else
			extra = 0x0A;

		out[ -1 ] = (char)extra;
	}

	while( *(unsigned char *)p != 0 )
	{
		if( *(unsigned char *)p < 0x20 )
		{
			*out = 0x0A;
			out++;

			separator = *p;
			p++;

			while( *(unsigned char *)p > 0
					&& *(unsigned char *)p < 0x20
					&& *(unsigned char *)p != *(unsigned char *)&separator )
				p++;
		}
		else
		{
			*out = *p;
			out++;
			p++;
		}
	}

	*out = 0;
}

// 0x007EC030 DELETES A TAG FROM A RECORD, in place, and the four walks are the
// whole body.  The lookup gives it the value; from there it walks BACK to the
// start of the name -- stopping at the record's start or at the first byte at
// or below 0x20 -- then FORWARD past the value and past the control run that
// ends it, then copies everything that is left down over the hole, then trims
// trailing whitespace off what it produced.
//
// SO THE SEPARATOR IS NEVER SEARCHED FOR AGAIN.  The name's extent is found by
// scanning outward from the value the lookup already returned, which is why
// this needs no second parse and why deleting a tag whose name contains a space
// would leave part of it behind.
//
// A tag that is not there is -1 and nothing is touched; anything else is 0.
// There is no way to tell how much was removed.
int Rva007EC030( char *text, const char *tag )
{
	char *value;
	char *out;
	char *p;
	char *start;

	start = text;

	value = Rva007EBCA0( start, tag );
	if( value == 0 )
		return -1;

	for( out = value; out != start
			&& *(unsigned char *)( out - 1 ) > 0x20; out-- )
		;

	for( p = value; *(unsigned char *)p >= 0x20; p++ )
		;

	while( *(unsigned char *)p > 0 && *(unsigned char *)p < 0x20 )
		p++;

	while( *(unsigned char *)p != 0 )
	{
		*out = *p;
		out++;
		p++;
	}

	while( out != start && *(unsigned char *)( out - 1 ) <= 0x20 )
		out--;

	*out = 0;
	return 0;
}

// 0x007EC2E0 RETURNS THE FIRST TAG'S NAME.  It scans for the first separator,
// walks BACK from it to where the name starts -- the record's start, or the
// first byte at or below 0x20 -- and then copies forward from there to the
// separator.  Same outward-from-the-separator trick 0x007EC030 uses to delete
// one, and it stops at the same structural record terminator.
//
// THE DESTINATION IS CLEARED BEFORE ANYTHING ELSE, but only when the caller
// gave a positive size -- so a size of zero leaves the buffer untouched rather
// than being treated as an error, and a null or empty record then returns 0
// with the buffer already emptied.
//
// TWO OF THE THREE EXITS DO NOT TERMINATE THE BUFFER.  Running off the end of
// the record and hitting the record terminator both return the count as it
// stands, leaving whatever the initial clear left; only the successful copy
// writes a terminator.  Since the count is 0 on both of those paths and the
// clear already wrote a zero, the result is still a valid empty string -- which
// is why the omission is invisible rather than a bug.
//
// The copy bound is `written + 1 < destSize`, so one byte is always held back.
//
// BOTH EXITS FROM THE LOOP ARE `break`, NOT `return`.  Retail jumps to a single
// shared `mov eax,written` at the end; writing either as its own return loads
// the count again before jumping, three bytes retail does not have.
int Rva007EC2E0( const char *text, char *dest, int destSize )
{
	int written;
	const char *p;
	const char *q;
	const char *start;

	written = 0;
	start = text;

	if( destSize > 0 )
		*dest = 0;

	if( start == 0 || *(unsigned char *)start == 0 )
		return 0;

	for( p = start; *(unsigned char *)p != 0; p++ )
	{
		if( *(unsigned char *)p != '=' && *(unsigned char *)p != ':' )
			continue;

		if( *(unsigned char *)( p + 1 ) < 0x20
				&& *(unsigned char *)( p - 1 ) <= 0x20 )
			break;

		for( q = p; q != start
				&& *(unsigned char *)( q - 1 ) > 0x20; q-- )
			;

		while( q != p && written + 1 < destSize )
		{
			dest[ written ] = *q;
			written++;
			q++;
		}

		dest[ written ] = 0;
		break;
	}

	return written;
}

// Twenty-four letters, one per bit, in bit order from the least significant.
// A terminator in the table is what bounds the loop below, so the table's own
// length is the number of flags this can name -- nothing else limits it.
extern char g_Rva0112A410FlagLetters[];

// Rva007EC780 lives in Y4TextToValue.c, which is C.  The two halves of this
// module ended up split across a .c and a .cpp by two different lanes; the
// declaration has to say so or the call will not link.
extern "C" int Rva007EC780( unsigned char *buffer, int size, const char *field );

// 0x007ECAF0 NAMES A BIT MASK IN LETTERS and stores it as a field.  Bit zero
// takes the first letter of the table, bit one the second, and set bits
// contribute their letter in order -- so the value reads back as the flags it
// stands for rather than as a number.
//
// THE LOOP ENDS ON EITHER EXHAUSTION, and that asymmetry matters.  It stops
// when the remaining mask is zero OR when the table runs out, so bits above
// the table's length are DISCARDED SILENTLY: the field is written, the call
// reports success, and the information is simply gone.
//
// THE SHIFT IS ARITHMETIC, so a mask with its top bit set never empties -- it
// shifts in ones forever.  The table terminator is the only thing that stops
// it, which makes the table's length load-bearing rather than incidental.
int Rva007ECAF0( char *record, int size, const char *name, int flags )
{
	char *p;
	const char *pLetter;
	char strField[ 0x120 ];

	p = Rva007EC730( record, strField, name );

	for( pLetter = g_Rva0112A410FlagLetters;
		flags != 0 && *pLetter != 0; flags >>= 1, pLetter++ )
	{
		if( ( flags & 1 ) != 0 )
		{
			*p = *pLetter;
			p++;
		}
	}

	*p = 0;

	return Rva007EC780( ( unsigned char * )record, size, strField );
}

// 0x007ECD90 IS THE INVERSE OF THE FOUR-CHARACTER TAG PACKER at 0x007EE8B0,
// and it shares that function's convention exactly: a tag is four printable
// bytes in an int, left-padded with SPACES rather than zeros.
//
// THE PADDING IS SKIPPED BY THE SAME SIGNED BOUND THE PACKER USED.  A value
// whose top byte is a space or lower compares at or below 0x20FFFFFF, so the
// byte is dropped and the value shifts on; the first byte above that bound
// begins the text.  ONE CONSEQUENCE IS THAT THE SKIPPING IS NOT ONLY LEADING:
// a space in the MIDDLE of a tag is dropped too, so a tag written with an
// interior space does not survive a round trip through the pair.
//
// THE LOOP CANNOT RUN AWAY because the shift is left and unsigned in effect --
// four shifts of eight empty any int -- so the four-byte limit is a property
// of the width rather than a counter, exactly as it is in the packer.
int Rva007ECD90( char *record, int size, const char *name, int value )
{
	char *p;
	char strField[ 0x120 ];

	p = Rva007EC730( record, strField, name );

	for( ; value != 0; value <<= 8 )
	{
		if( value > 0x20FFFFFF )
		{
			*p = ( char )( value >> 24 );
			p++;
		}
	}

	*p = 0;

	return Rva007EC780( ( unsigned char * )record, size, strField );
}

// Mirrors the definition in Y4CivilTime.c, which is C.  Duplicated rather than
// shared because the module is split across two translation units and two
// languages; the layout is struct tm and both halves agree on it.
struct Rva007EDB10Time
{
	int m_second; int m_minute; int m_hour;
	int m_day; int m_month; int m_year;
	int m_weekday; int m_yearDay; int m_isDst;
};

extern "C" struct Rva007EDB10Time *Rva007EDB10(
	struct Rva007EDB10Time *pTime, unsigned int uSeconds );
extern "C" unsigned int Rva007FEF60( void );

// "%d.%d.%d %d:%02d:%02d" -- in writable data rather than among the literals,
// so the stored format is configurable at run time.  Note the asymmetry it
// carries: the DATE fields are unpadded and the CLOCK fields after the first
// are zero-padded, so the text is not fixed width and cannot be sorted as a
// string even though it starts with the year.
extern char g_Rva012C3938Format[];

// Declared without the CRT header on purpose: under /MD that header marks
// sprintf dllimport and the call becomes an indirect through the IAT, where
// retail calls the import stub directly.
extern "C" int __cdecl sprintf( char *dest, const char *format, ... );

// 0x007ED9F0 STORES A TIMESTAMP AS A HUMAN-READABLE DATE FIELD.
//
// A ZERO TIMESTAMP MEANS NOW.  There is no separate entry point for "stamp
// this with the current time" -- passing zero is the way to ask, which also
// means the epoch second cannot be stored through this function.  That is the
// same convention the parser at 0x007EF780 arrived at from the other side, and
// neither of them says so in its signature.
//
// THE OUTPUT IS UNBOUNDED IN PRINCIPLE AND SAFE IN PRACTICE ONLY BY ARITHMETIC.
// sprintf writes into the tail of a 288-byte local after the name and its
// separator, with no size passed; nothing here checks that the name left room.
// A name approaching the buffer's length would overflow it, and the /GS cookie
// this function carries is the only thing that would notice.
//
// The two human-facing adjustments -- year plus 1900, month plus one -- appear
// here for the third time in this module rather than being shared, which keeps
// every outward-facing function independent of the others.
int Rva007ED9F0( char *record, int size, const char *name, unsigned int uWhen )
{
	struct Rva007EDB10Time *ptm;
	struct Rva007EDB10Time tm2;
	char *pDest;
	unsigned int uTime;
	char item[ 0x120 ];

	uTime = uWhen;

	if( uTime == 0 )
	{
		uTime = Rva007FEF60();
	}

	ptm = Rva007EDB10( &tm2, uTime );

	if( ptm == 0 )
	{
		return -1;
	}

	pDest = Rva007EC730( record, item, name );

	sprintf( pDest, g_Rva012C3938Format,
		ptm->m_year + 1900, ptm->m_month + 1, ptm->m_day,
		ptm->m_hour, ptm->m_minute, ptm->m_second );

	return Rva007EC780( ( unsigned char * )record, size, item );
}

extern "C" unsigned int Rva007EDE00( const struct Rva007EDB10Time *pTime );
extern "C" void * __cdecl memset( void *dest, int c, unsigned int count );

// 0x007EE050 STORES A PACKED DATE AND TIME AS A DATE FIELD.  It is the mirror
// of the reader at 0x007EFC20: that one parses text and hands back two packed
// integers, this one takes two packed integers and writes the text.
//
// THE ROUND TRIP IS NOT SYMMETRIC, though, and the packing is where it shows.
// The date field is unpacked with a SIXTEEN-BIT year but an EIGHT-BIT month
// and day, and the clock with three eight-bit fields -- so this accepts values
// the reader can never have produced, and truncates rather than rejecting
// them.  A day of 300 becomes 44 with no complaint anywhere.
//
// THE ADJUSTMENTS RUN THE OTHER WAY HERE, year less 1900 and month less one,
// converting the human numbering back to the C one.  That is the fourth
// appearance of the pair in this module and the second in this direction.
//
// THE OFFSET IS SUBTRACTED, NOT ADDED, matching the reader that adds it -- and
// only when the conversion succeeded, so a zero result stays zero and is then
// read one level down as "use the current time".  A DATE THAT CONVERTS TO THE
// EPOCH THEREFORE STORES AS NOW rather than as 1970, which is the same blind
// spot the rest of this chain has, arrived at from a third direction.
int Rva007EE050( char *record, int size, const char *name,
	int iDate, int iTime, int iOffset )
{
	struct Rva007EDB10Time tm;
	unsigned int uTime;

	memset( &tm, 0, sizeof( tm ) );
	tm.m_isDst = -1;

	tm.m_year = ( ( iDate >> 16 ) & 0xFFFF ) - 1900;
	tm.m_month = ( ( iDate >> 8 ) & 0xFF ) - 1;
	tm.m_day = iDate & 0xFF;
	tm.m_hour = ( iTime >> 16 ) & 0xFF;
	tm.m_minute = ( iTime >> 8 ) & 0xFF;
	tm.m_second = iTime & 0xFF;

	uTime = Rva007EDE00( &tm );

	if( uTime != 0 )
	{
		uTime -= iOffset;
	}

	return Rva007ED9F0( record, size, name, uTime );
}

// 0x007EDD30 IS THE FIELD-WISE WRITER, taking six separate components where
// 0x007EE050 takes two packed integers.  With it the module's date interface
// closes into a FOUR-WAY SYMMETRY: read packed (0x007EFC20), read field-wise
// (0x007EFB20), write packed (0x007EE050), write field-wise (this).  All four
// are independent -- none is written in terms of another -- which is why the
// year and month adjustments appear in every one of them.
//
// THIS IS THE ONLY ONE OF THE FOUR THAT CANNOT TRUNCATE.  Its components
// arrive as full ints rather than through eight-bit fields, so it is the only
// path by which a caller can supply a value that the packed forms could not
// represent, and equally the only one that will not silently mangle one.  What
// it does instead is hand the value to a search that has no not-found exit, so
// an out-of-range component does not truncate here -- it fails further down.
int Rva007EDD30( char *record, int size, const char *name,
	int iYear, int iMonth, int iDay, int iHour, int iMinute, int iSecond,
	int iOffset )
{
	struct Rva007EDB10Time tm;
	unsigned int uTime;

	memset( &tm, 0, sizeof( tm ) );
	tm.m_isDst = -1;

	tm.m_year = iYear - 1900;
	tm.m_month = iMonth - 1;
	tm.m_day = iDay;
	tm.m_hour = iHour;
	tm.m_minute = iMinute;
	tm.m_second = iSecond;

	uTime = Rva007EDE00( &tm );

	if( uTime != 0 )
	{
		uTime -= iOffset;
	}

	return Rva007ED9F0( record, size, name, uTime );
}
