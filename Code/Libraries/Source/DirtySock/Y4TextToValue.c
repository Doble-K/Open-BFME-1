// cl: /Od /GZ /MD /DNDEBUG
/* EA DirtySock -- text-to-value scanners, /Od with /GZ.  Both take a default
 * to return when the input is unusable, so neither can fail visibly; a caller
 * that needs to tell "absent" from "parsed" has to pick a default it can
 * recognise.  Placement is by address neighbourhood.
 */

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
