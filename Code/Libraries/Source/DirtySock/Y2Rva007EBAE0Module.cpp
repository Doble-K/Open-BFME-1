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
