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
