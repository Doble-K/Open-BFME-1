// cl: /Od /GZ /MD /DNDEBUG
/* EA DirtySock -- text-to-value scanners, /Od with /GZ.  Both take a default
 * to return when the input is unusable, so neither can fail visibly; a caller
 * that needs to tell "absent" from "parsed" has to pick a default it can
 * recognise.  Placement is by address neighbourhood.
 */

/* DECLARED HERE RATHER THAN INCLUDED, and that is forced by the bytes.  Under
 * /MD the CRT headers mark these __declspec(dllimport), which turns each call
 * into an indirect ff 15 straight through the IAT.  Retail calls the import
 * STUB with a direct e8, so the translation unit it was built from did not see
 * <string.h> -- these prototypes reproduce that. */
void * __cdecl memcpy( void *dest, const void *src, unsigned int count );
void * __cdecl memmove( void *dest, const void *src, unsigned int count );
int __cdecl memcmp( const void *a, const void *b, unsigned int count );

/* 0x007EE8B0 PACKS UP TO FOUR PRINTABLE CHARACTERS INTO AN INT -- the same
 * four-character tags the socket layer dispatches on, 'xmap' and the rest,
 * built from text instead of written as a literal.
 *
 * THE LENGTH LIMIT IS ENFORCED BY THE ACCUMULATOR, not by a counter.  It
 * starts at 0x20202020 -- four spaces -- and the loop runs while it stays
 * below 0x20FFFFFF.  Each character shifts a space out of the top, so after
 * the fourth the leading byte is a printable character, the value exceeds the
 * bound, and the loop stops.  A shorter string leaves the unused leading bytes
 * as SPACES rather than zeros, which is what makes a two-character tag compare
 * equal to the same tag written as a padded literal.
 *
 * The bound is a SIGNED comparison, which is safe only because the accepted
 * range stops at 0x7E: a character with the high bit set would make the
 * accumulator negative and the loop would never stop on its own.  The range
 * check is what protects the bound, not the other way round.
 */
int Rva007EE8B0( const char *text, int defaultValue )
{
	int iValue;

	if ( text == 0 || *text <= ' ' || *text >= 0x7F )
		return defaultValue;

	iValue = 0x20202020;

	while ( iValue < 0x20FFFFFF && *text > ' ' && *text < 0x7F )
	{
		iValue = ( iValue << 8 ) | *text;
		text++;
	}

	return iValue;
}

/* 0x007EE820 PARSES A DOTTED QUAD into a packed address, and it is the same
 * algorithm as the socket unit's parser at 0x007FFDD0 written differently:
 * there the running value's low byte is isolated by subtracting it out and
 * adding it back scaled, here by masking with 0xFFFFFF00 and OR-ing the new
 * byte in.  Same effect, and the two spellings sitting in one image is a
 * useful reminder that a shape match across bodies is not an identity.
 *
 * IT STOPS AT THE FIRST CHARACTER THAT IS NEITHER A DIGIT NOR A DOT and
 * returns what it has, so trailing text is ignored rather than rejected and
 * an empty string yields zero -- not the default, which is reached only by a
 * null pointer.
 *
 * There is no range check on an octet: digits accumulate into a single byte,
 * so "999" wraps rather than failing, exactly as the other parser does.
 */
int Rva007EE820( const char *text, int defaultValue )
{
	int iValue;

	iValue = 0;

	if ( text == 0 )
		return defaultValue;

	for ( iValue = 0; ; text++ )
	{
		if ( *text >= '0' && *text <= '9' )
		{
			iValue = ( iValue & 0xFFFFFF00 )
				| ( ( iValue & 0xFF ) * 10 + ( *text & 0x0F ) );
		}
		else if ( *text == '.' )
		{
			iValue = iValue << 8;
		}
		else
		{
			break;
		}
	}

	return iValue;
}

/* 0x007EE720 PARSES A SIGNED DECIMAL INTEGER, and the two things it does NOT
 * do are the ones worth knowing.
 *
 * IT DOES NOT SKIP LEADING WHITESPACE.  A space before the sign or the digits
 * ends the parse immediately and yields zero -- not the default, which only a
 * null pointer reaches.  Anything handing it text straight out of a
 * configuration line has to trim first.
 *
 * AND IT DOES NOT DETECT OVERFLOW: digits accumulate into an int by multiply
 * and add with no bound, so a long enough run wraps silently.
 *
 * A leading '+' is accepted and skipped, which strtol does but atoi is not
 * required to.  The sign is kept as a multiplier applied at the end rather
 * than by negating the accumulator, so the most negative value is not
 * representable through this path -- it would have to overflow positive first.
 */
int Rva007EE720( const char *text, int defaultValue )
{
	int iSign;
	int iValue;

	if ( text == 0 )
		return defaultValue;

	iSign = 1;

	if ( *text == '+' )
	{
		text++;
	}
	else if ( *text == '-' )
	{
		text++;
		iSign = -1;
	}

	for ( iValue = 0; *text >= '0' && *text <= '9'; text++ )
		iValue = iValue * 10 + ( *text & 0x0F );

	return iSign * iValue;
}

/* A 256-entry translation table, indexed by a SIGNED char -- so a byte with
 * the high bit set reads BEFORE the table's start.  That is what the bytes do;
 * whether anything upstream keeps such bytes out is not visible here. */
extern char g_Rva0112A210Fold[];

/* 0x007EFD00 COMPARES TWO STRINGS THROUGH THAT TABLE, and it is doing three
 * jobs at once rather than one.
 *
 * QUOTES SET A PER-SIDE TERMINATOR.  A leading double quote is consumed and
 * remembered, and thereafter a matching quote ends that side; without one the
 * side instead ends at any character below space.  The two sides are decided
 * INDEPENDENTLY, so a quoted string compares cleanly against an unquoted one
 * -- which is the point, since it lets a configuration value be written either
 * way.
 *
 * The end-of-string test is therefore not a NUL test: a control character ends
 * an unquoted side, and a NUL ends a quoted one only because it is below
 * space... which it is not, in the quoted case.  A quoted string missing its
 * closing quote runs past the terminator.
 *
 * The loop is a DO-WHILE, so both sides always advance at least once; the
 * caller's null and empty-string checks at the top are what make that safe.
 *
 * The result is the difference of the two folded characters, so it orders by
 * the TABLE's ordering rather than by the raw bytes.
 */
int Rva007EFD00( const char *a, const char *b )
{
	unsigned char cTermA;
	unsigned char cTermB;
	unsigned char cA;
	unsigned char cB;

	if ( a == 0 || *a == 0 )
		return -1;

	cTermA = ( *a == '"' ) ? *a++ : 0;
	cTermB = ( *b == '"' ) ? *b++ : 0;

	do
	{
		cA = g_Rva0112A210Fold[ *a ];
		a++;
		if ( cA == cTermA || ( cA < ' ' && cTermA == 0 ) )
			cA = 0;

		cB = g_Rva0112A210Fold[ *b ];
		b++;
		if ( cB == cTermB || ( cB < ' ' && cTermB == 0 ) )
			cB = 0;
	}
	while ( cA == cB && cA != 0 && cB != 0 );

	return cA - cB;
}

/* A separator character and a suffix string, both in writable data rather than
 * among the literals, so both are configurable at run time.  The separator is
 * a plain char -- read with movsx where the buffer's own bytes are read with
 * movzx, which is what types the two differently. */
extern char g_Rva012C391CSeparator;
extern char g_Rva012C392CSuffix[];

/* 0x007EC4D0 APPENDS THE SUFFIX TO A BUFFER, inserting the separator first if
 * the buffer needs one, and returns 0 or -1 for "did not fit".
 *
 * THE SEPARATOR IS ONLY ADDED WHEN IT IS ACTUALLY MISSING.  Three conditions
 * all have to hold: the buffer is non-empty, its last character is not a
 * control character, and it is not already the separator.  So calling this
 * twice does not double the separator, and appending to text that already ends
 * in one leaves it alone -- which is what makes the operation repeatable.
 *
 * THE TWO LENGTH CHECKS ARE DIFFERENT AND BOTH MATTER.  The separator needs
 * one free byte and is checked against size - 1; the suffix is checked with a
 * FIXED MARGIN OF FOUR rather than against its own length, so a suffix longer
 * than three characters plus its terminator would overrun.  Nothing here reads
 * the suffix's length, so that margin is an assumption about the data rather
 * than a bound derived from it.
 *
 * A buffer too small for the suffix is left with the separator already
 * appended -- the failure is not atomic, and -1 does not mean "unchanged".
 */
int Rva007EC4D0( unsigned char *buffer, int size )
{
	int i;
	int iResult;
	char *pSuffix;
	unsigned char *pBuffer;

	iResult = -1;
	pSuffix = g_Rva012C392CSuffix;
	pBuffer = buffer;

	for ( i = 0; pBuffer[ i ] != 0; i++ )
	{
	}

	if ( i > 0 && pBuffer[ i - 1 ] >= ' '
		&& pBuffer[ i - 1 ] != g_Rva012C391CSeparator
		&& i < size - 1 )
	{
		pBuffer[ i ] = g_Rva012C391CSeparator;
		i++;
		pBuffer[ i ] = 0;
	}

	if ( i + 4 < size )
	{
		while ( *pSuffix != 0 )
		{
			pBuffer[ i ] = *pSuffix;
			i++;
			pSuffix++;
		}

		pBuffer[ i ] = 0;
		iResult = 0;
	}

	return iResult;
}

/* 0x007EC3F0 REPLACES THE VALUE OF A ONE-FIELD RECORD IN PLACE, rewriting the
 * buffer as "key=\nvalue" and returning 0, or -1 if there is not enough room.
 *
 * THE SCAN AT THE TOP DEFINES THE RECORD FORMAT more precisely than any of the
 * parsers in this file do.  A delimiter is '=' OR ':' FOLLOWED BY A CONTROL
 * CHARACTER -- neither punctuation mark alone ends the key, so a key may
 * contain either as long as ordinary text follows it.  What is written back is
 * always '=' and 0x0A, so ':' is accepted on input and never produced.
 * Finding no delimiter is not an error: the scan then stops at the terminator
 * and the whole existing string is taken as the key.
 *
 * A NULL VALUE MEANS "TRUNCATE", NOT "NO CHANGE", and it returns success.  The
 * key's terminator is written BEFORE the value is examined, so by the time the
 * null test runs the old value is already gone -- and the same is true of the
 * -1 path below, which leaves a truncated buffer behind.  NEITHER FAILURE NOR
 * THE NULL CASE IS A NO-OP.
 *
 * THE MARGIN OF FIVE IS NOT A FIT CHECK.  The copy stops at the last byte of
 * the buffer and the terminator always lands there, so two bytes past the key
 * would be enough to write an empty value.  Requiring five means the caller
 * gets -1 rather than a record whose value was cut to almost nothing: the
 * check is about the result being worth writing, not about it fitting.
 */
int Rva007EC3F0( unsigned char *buffer, int size, const char *value )
{
	unsigned char *p;
	unsigned char *pEnd;

	for ( p = buffer; *p != 0; p++ )
	{
		if ( ( *p == '=' || *p == ':' ) && p[ 1 ] < ' ' )
		{
			break;
		}
	}

	*p = 0;

	if ( value == 0 )
	{
		return 0;
	}

	pEnd = buffer + size - 1;

	if ( pEnd - p < 5 )
	{
		return -1;
	}

	*p = '=';
	p++;
	*p = '\n';
	p++;

	while ( *value != 0 && p != pEnd )
	{
		*p = *value;
		p++;
		value++;
	}

	*p = 0;
	return 0;
}

/* 0x007EFAB0 SCANS A RUN OF DIGITS INTO *value AND RETURNS WHERE IT STOPPED,
 * consuming at most maxLength characters.
 *
 * A NON-POSITIVE maxLength MEANS 256, not "unbounded" and not "nothing".  So
 * there is no way to ask this for an unlimited scan, and passing 0 -- the
 * value a caller would most naturally use for "no limit" -- silently gets the
 * default rather than an empty result.
 *
 * THE LIMIT IS TESTED LAST, after both digit tests, which is what makes the
 * returned pointer meaningful: stopping because the budget ran out leaves it
 * on a digit, while stopping at a non-digit leaves it on the separator.  The
 * caller can tell the two apart only by looking at what it points to.
 *
 * NO OVERFLOW CHECK, and no sign or whitespace handling -- consistent with the
 * decimal parser above, which shares this shape.  Digits are folded with & 0xF
 * rather than by subtracting '0'; the two agree for '0'..'9' and this one is a
 * byte shorter.
 */
const char *Rva007EFAB0( const char *text, int *value, int maxLength )
{
	if ( maxLength <= 0 )
	{
		maxLength = 0x100;
	}

	*value = 0;

	for ( ; *text >= '0' && *text <= '9' && maxLength > 0; text++, maxLength-- )
	{
		*value = *value * 10 + ( *text & 0xF );
	}

	return text;
}

/* A 256-entry character-class table.  Class 1 ends a field, class 0 is
 * whitespace or a terminator, and anything >= 2 is a name character -- the
 * comparison below only ever asks whether two classes are equal AND at least
 * two, so the distinctions above 1 are the caller's business, not ours.  It is
 * indexed by the buffer's bytes UNSIGNED and by the field text's bytes SIGNED,
 * so a high-bit byte in the field reads BEFORE the table start. */
extern unsigned char g_Rva0112A310Class[];

/* 0x007EC780 REPLACES ONE NAMED FIELD IN A RECORD, or appends it, and returns
 * the length written less one -- so the value is a count of everything before
 * the separator it just placed.  This is the engine the small writers above
 * are thin wrappers over.
 *
 * A LEADING '~' MEANS "APPEND, DO NOT SEARCH".  It skips the scan entirely, so
 * a record can carry the SAME NAME TWICE, deliberately; nothing here rejects a
 * duplicate, and a later search will only ever find the first.
 *
 * THE SCAN COMPARES CHARACTER CLASSES, NOT CHARACTERS, and stops at the first
 * position where the two classes disagree or drop below 2.  A NAME MATCHES
 * WHEN THE CLASSES AT THAT POSITION SUM TO EXACTLY 2 -- that is, both sides
 * ended together on class-1 delimiters.  One side ending early gives 0 + 1 or
 * 1 + 2 and fails, which is what stops a name being a prefix of another.
 *
 * THE THREE-WAY memmove IS A RESIZE IN PLACE.  iDelta is new length minus old:
 * positive opens a gap and is the only case that can overflow the buffer,
 * negative closes one, and ZERO SHORT-CIRCUITS ON memcmp -- rewriting a field
 * with the text it already holds returns 0 without touching a byte.  That is
 * the only path that reports success without writing.
 *
 * THE OVERFLOW CHECK GUARDS ONLY GROWTH, which is correct but worth stating:
 * when iDelta <= 0 the result cannot be longer than what is already there, so
 * no check is needed and none is made.
 *
 * THE LAST BYTE IS DECIDED BY THE SEPARATOR'S IDENTITY.  Writing the field's
 * own terminator would end the record, so it is overwritten with the separator
 * -- EXCEPT where the field landed at the very end AND the separator is not a
 * newline, where a real terminator goes in instead.  The '\n' case is special
 * because a trailing newline is harmless at the end of a record and a trailing
 * anything-else would leave a separator with nothing after it.
 */
int Rva007EC780( unsigned char *buffer, int size, const char *field )
{
	int i;
	int iDelta;
	unsigned char *p;
	unsigned char *pValue;
	unsigned char *pTail;
	unsigned char cClassBuffer;
	unsigned char cClassField;
	unsigned char *pBuffer;

	pBuffer = buffer;

	if ( pBuffer == 0 )
	{
		return -1;
	}

	if ( field == 0 || (unsigned int)*field <= ' ' )
	{
		return -1;
	}

	if ( *field == '~' )
	{
		for ( p = pBuffer; *p != 0; p++ )
		{
		}

		if ( p != pBuffer && p[ -1 ] >= ' '
			&& p[ -1 ] != g_Rva012C391CSeparator
			&& p < pBuffer + size - 1 )
		{
			*p = g_Rva012C391CSeparator;
			p++;
			*p = 0;
		}

		pTail = p;
		pValue = pTail;
	}
	else
	{
		p = pBuffer;

		for ( ;; )
		{
			if ( *p == 0 )
			{
				if ( p != pBuffer && p[ -1 ] >= ' '
					&& p[ -1 ] != g_Rva012C391CSeparator
					&& p < pBuffer + size - 1 )
				{
					*p = g_Rva012C391CSeparator;
					p++;
					*p = 0;
				}

				pTail = p;
				pValue = pTail;
				break;
			}

			if ( *p <= ' ' )
			{
				p++;
				continue;
			}

			if ( g_Rva0112A310Class[ *p ] == 1 )
			{
				pTail = p;
				pValue = pTail;
				break;
			}

			for ( i = 0; ; i++ )
			{
				cClassBuffer = g_Rva0112A310Class[ p[ i ] ];
				cClassField = g_Rva0112A310Class[ field[ i ] ];

				if ( cClassBuffer != cClassField || cClassBuffer < 2 )
				{
					break;
				}
			}

			if ( cClassBuffer + cClassField == 2 )
			{
				pTail = p;
				pValue = pTail;

				for ( ; *pTail >= ' '; pTail++ )
				{
				}

				if ( *pTail > 0 )
				{
					pTail++;
				}

				break;
			}

			do
			{
				p++;
			}
			while ( *p >= ' ' );
		}
	}

	for ( i = 0; (unsigned int)field[ i ] >= ' '; i++ )
	{
	}

	i++;

	iDelta = i - ( pTail - pValue );

	for ( p = pTail; *p != 0; p++ )
	{
	}

	p++;

	if ( iDelta > 0 && pBuffer + size - p < iDelta )
	{
		return -1;
	}

	if ( iDelta == 0 && memcmp( pValue, field, i ) == 0 )
	{
		return 0;
	}

	if ( iDelta > 0 )
	{
		memmove( pTail + iDelta, pTail, p - pTail );
	}

	if ( iDelta < 0 )
	{
		memmove( pValue, pValue - iDelta, p - ( pValue - iDelta ) );
	}

	memcpy( pValue, field, i );

	if ( pValue[ i ] == 0 && g_Rva012C391CSeparator != '\n' )
	{
		pValue[ i - 1 ] = 0;
	}
	else
	{
		pValue[ i - 1 ] = g_Rva012C391CSeparator;
	}

	return i - 1;
}

/* 0x007EE1D0 APPLIES A WHOLE LIST OF FIELDS TO A RECORD and returns how many
 * of them actually changed it.
 *
 * THE COUNT IS OF CHANGES, NOT OF FIELDS APPLIED.  The engine returns 0 when a
 * field already holds the text being written, and only a strictly positive
 * result is counted here -- so a caller can use the return value to decide
 * whether the record needs saving, which is the only reason to distinguish
 * those two cases at all.  Errors return -1 and are counted the same as
 * no-change: NOTHING HERE REPORTS A FAILED FIELD.  A list that overflows the
 * buffer halfway through returns a plausible non-zero count.
 *
 * A DELIMITER WHERE A NAME SHOULD BE ENDS THE LIST.  Leading whitespace is
 * skipped, but a field starting with '=' or ':' would name nothing, so the
 * whole remainder is abandoned rather than skipped -- silently, and with the
 * fields already applied left in place.
 *
 * Fields are separated by anything below a space, and a run of them counts as
 * one separator, so the list is equally happy as newline- or NUL-delimited
 * text.
 */
int Rva007EE1D0( unsigned char *buffer, int size, const unsigned char *fields )
{
	int iChanged;
	const unsigned char *p;

	iChanged = 0;
	p = fields;

	while ( *p != 0 )
	{
		if ( *p <= ' ' )
		{
			p++;
			continue;
		}

		if ( *p == '=' || *p == ':' )
		{
			break;
		}

		if ( Rva007EC780( buffer, size, (const char *)p ) > 0 )
		{
			iChanged++;
		}

		while ( *p >= ' ' )
		{
			p++;
		}
	}

	return iChanged;
}
