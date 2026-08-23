// cl: /Od /GZ /RTCu /MD /DNDEBUG
/* EA DirtySock -- civil time from a seconds-since-epoch count, written out by
 * hand rather than called out to the CRT.  Placement is by address
 * neighbourhood; the packer at 0x007EFC20 is its only caller so far found.
 */

/* Retail's own name for this on the caller's frame is `tm2`, recovered from
 * the /GZ frame descriptor, and the layout is struct tm exactly -- 36 bytes,
 * fields in the standard order.  It is spelled out here rather than included
 * so the one field this function NEVER WRITES is visible: m_weekday.  A caller
 * that reads it gets whatever was on the stack, and with /GZ that is
 * 0xCCCCCCCC.
 */
struct Rva007EDB10Time
{
	int m_second;			/* +0x00 */
	int m_minute;			/* +0x04 */
	int m_hour;			/* +0x08 */
	int m_day;			/* +0x0C, 1-based */
	int m_month;			/* +0x10, 0-based */
	int m_year;			/* +0x14, less 1900 */
	int m_weekday;			/* +0x18, NEVER WRITTEN */
	int m_yearDay;			/* +0x1C, 0-based */
	int m_isDst;			/* +0x20, always zero */
};

/* Twenty-four month lengths: the twelve leap-year ones first, then the twelve
 * common ones.  Which half is used is selected by the PARITY of the year's
 * length -- 366 is even and picks index 0, 365 is odd and picks index 12 --
 * rather than by testing the leap flag again. */
extern int g_Rva0112A530MonthDays[];

/* 0x007EDB10 CONVERTS SECONDS SINCE 1970 INTO BROKEN-DOWN TIME, filling the
 * caller's structure and returning it.
 *
 * THE YEAR LOOP IS AN ESTIMATE-AND-CORRECT, not a count.  Rather than stepping
 * one year at a time it guesses with a divide by 366 -- always an
 * UNDERESTIMATE, since no year is longer -- forces the guess forward by one
 * when it lands on the year it started from, then subtracts 365 days per year
 * crossed and fixes up the leap days with the standard /4 - /100 + /400
 * accumulation across the span.  It then re-tests, so a guess that overshoots
 * is not possible but a guess that falls short simply iterates again.
 *
 * THE DIVISION OF SECONDS IS UNSIGNED AND EVERYTHING AFTER IT IS SIGNED.  Only
 * the initial split into days and seconds treats the timestamp as unsigned, so
 * the function keeps working past 2038 for the DAY count while the arithmetic
 * downstream is ordinary signed int.
 *
 * TWO FIELDS ARE NOT COMPUTED.  m_isDst is set to zero unconditionally -- this
 * is UTC and there is no zone rule anywhere in it -- but m_weekday is not
 * written at all, which is a different thing entirely: the caller sees
 * uninitialised stack.  Nothing in the packer at 0x007EFC20 reads it, which is
 * presumably why it was never noticed.
 */
struct Rva007EDB10Time *Rva007EDB10( struct Rva007EDB10Time *pTime,
	unsigned int uSeconds )
{
	int iYear;
	int iYearDays;
	int iNextYear;
	int iDays;
	int iSeconds;
	int *pMonthDays;
	unsigned int uTime;

	uTime = uSeconds;
	iDays = uTime / 86400;
	iSeconds = uTime % 86400;

	pTime->m_second = iSeconds % 60;
	iSeconds = iSeconds / 60;
	pTime->m_minute = iSeconds % 60;
	iSeconds = iSeconds / 60;
	pTime->m_hour = iSeconds;

	for ( iYear = 1970; ; iYear = iNextYear )
	{
		iYearDays = ( ( iYear & 3 ) == 0
			&& ( iYear % 100 != 0 || iYear % 400 == 0 ) ) ? 366 : 365;

		if ( iDays < iYearDays )
		{
			break;
		}

		iNextYear = iDays / 366 + iYear;

		if ( iNextYear == iYear )
		{
			iNextYear++;
		}

		iDays -= ( iNextYear - iYear ) * 365;

		iDays += ( iYear - 1 ) / 4 - ( iYear - 1 ) / 100 + ( iYear - 1 ) / 400;
		iDays -= ( iNextYear - 1 ) / 4 - ( iNextYear - 1 ) / 100
			+ ( iNextYear - 1 ) / 400;
	}

	pTime->m_year = iYear - 1900;
	pTime->m_yearDay = iDays;

	pMonthDays = &g_Rva0112A530MonthDays[ ( iYearDays & 1 ) * 12 ];

	for ( pTime->m_month = 0; iDays >= *pMonthDays; pTime->m_month++ )
	{
		iDays -= *pMonthDays;
		pMonthDays++;
	}

	pTime->m_day = iDays + 1;
	pTime->m_isDst = 0;

	return pTime;
}

/* 0x007EDE00 IS THE INVERSE, AND IT IS A BINARY SEARCH RATHER THAN A FORMULA.
 * Instead of accumulating days per year the way an ordinary mktime would, it
 * searches the whole 32-bit timestamp space for the value whose decomposition
 * matches the caller's, calling 0x007EDB10 about thirty-two times.  That is a
 * deliberate trade: the forward direction is the only calendar code that has
 * to be right, and this direction cannot disagree with it.
 *
 * The local names below -- cmp, res, mid -- are RETAIL'S OWN, recovered from
 * the /GZ frame descriptor and from the strings the uninitialised-use checks
 * pass to __RTC_UninitUse.  Those checks are the compiler's, not the author's:
 * res and mid are assigned only inside the loop, so MSVC cannot prove they are
 * set by the time the return expression reads them.
 *
 * THE MIDPOINT IS COMPUTED OVERFLOW-SAFE -- half of each end plus the carry
 * they share -- which is necessary here and not merely careful, because hi
 * starts at 0xFFFFFFFF and the naive sum would wrap on the first iteration.
 *
 * THE SEARCH DOES NOT TERMINATE ON A MISS, and that is the sharp edge.  There
 * is no "not found" exit: the loop ends only on an exact match.  A target
 * before 1970 leaves res positive at mid == 0, so hi = mid - 1 wraps back to
 * 0xFFFFFFFF and the search returns to its starting interval forever.  THE
 * RANGE VALIDATION IN THE CALLER AT 0x007EF780 IS LOAD-BEARING FOR
 * TERMINATION, not just for correctness -- it is what guarantees the target
 * lies inside the searched space.
 *
 * THE RETURN IS A TERNARY THAT MSVC MADE BRANCHLESS.  `( res ? 0 : -1 ) & mid`
 * compiles at /Od to setne + dec + and, with no jump anywhere: this compiler
 * contracts the shape `x ? 0 : -1` into a mask even with optimisation off,
 * where the same value written as `( res != 0 ) - 1` gives a three-byte
 * `sub eax, 1` instead of the one-byte `dec`.  The bytes distinguish the two
 * spellings; nothing else does.  Since the loop only exits normally with res
 * zero, the mask is unreachable-false on every real path -- it matters only
 * for an empty interval, which the unsigned bounds make impossible.
 */
unsigned int Rva007EDE00( const struct Rva007EDB10Time *pTime )
{
	int res;
	struct Rva007EDB10Time cmp;
	unsigned int lo;
	unsigned int hi;
	unsigned int mid;

	lo = 0;
	hi = 0xFFFFFFFF;

	while ( lo <= hi )
	{
		mid = ( lo >> 1 ) + ( hi >> 1 ) + ( lo & hi & 1 );

		Rva007EDB10( &cmp, mid );

		res = cmp.m_year - pTime->m_year;

		if ( res == 0 )
		{
			res = cmp.m_month - pTime->m_month;

			if ( res == 0 )
			{
				res = cmp.m_day - pTime->m_day;

				if ( res == 0 )
				{
					res = cmp.m_hour - pTime->m_hour;

					if ( res == 0 )
					{
						res = cmp.m_minute - pTime->m_minute;

						if ( res == 0 )
						{
							res = cmp.m_second - pTime->m_second;

							if ( res == 0 )
							{
								break;
							}
						}
					}
				}
			}
		}

		if ( res > 0 )
		{
			hi = mid - 1;
		}
		else
		{
			lo = mid + 1;
		}
	}

	return ( res ? 0 : -1 ) & mid;
}
