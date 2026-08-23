// cl: /Od /GZ /MD /DNDEBUG
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
