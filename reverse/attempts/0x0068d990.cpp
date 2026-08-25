// ?bfmeReadByte_0068D990@@YAPAEPAE0PBE@Z
// partial score=0.95 date=2026-08-25
// Six more bodies in two shapes.
//
// 0x0068D990, 0x0068D9C0 and 0x0068D9F0 lift one byte out of a cursor and hand
// the advanced cursor back. The two bounds tests are ja, unsigned, so the
// operands are pointers rather than signed offsets, and both are skipped
// wholesale when the limit is null -- one je jumps past both of them.
//
// 0x0074AC00, 0x0074CD80 and 0x0074D6A0 widen a run of shorts into ints. The
// count comes from sub then sar 1, so the range is expressed as a pair of
// short pointers and not as a length, and the element load is movsx, so the
// source is signed. The guard is test/jle ahead of a bottom-tested loop, which
// is what a while over a count that the compiler cannot prove positive gives.


// ?bfmeReadByte_0068D990@@YAPAEPAE0PBE@Z
unsigned char *bfmeReadByte_0068D990(unsigned char *cursor, unsigned char *out, const unsigned char *end)
{
	if (end)
	{
		if (cursor > end)
			return cursor;

		if (cursor + 1 > end)
			return cursor;
	}

	*out = *cursor;

	return cursor + 1;
}

// ?bfmeReadByte_0068D9C0@@YAPAEPAE0PBE@Z
unsigned char *bfmeReadByte_0068D9C0(unsigned char *cursor, unsigned char *out, const unsigned char *end)
{
	if (end)
	{
		if (cursor > end)
			return cursor;

		if (cursor + 1 > end)
			return cursor;
	}

	*out = *cursor;

	return cursor + 1;
}

// ?bfmeReadByte_0068D9F0@@YAPAEPAE0PBE@Z
unsigned char *bfmeReadByte_0068D9F0(unsigned char *cursor, unsigned char *out, const unsigned char *end)
{
	if (end)
	{
		if (cursor > end)
			return cursor;

		if (cursor + 1 > end)
			return cursor;
	}

	*out = *cursor;

	return cursor + 1;
}

// ?bfmeWidenShorts_0074AC00@@YAXPBF0PAH@Z
void bfmeWidenShorts_0074AC00(const short *first, const short *last, int *out)
{
	int *dst = out;
	const short *stop = last;
	const short *src = first;
	int count = stop - src;

	while (count > 0)
	{
		*dst = *src;
		++src;
		++dst;
		--count;
	}
}

// ?bfmeWidenShorts_0074CD80@@YAXPBF0PAH@Z
void bfmeWidenShorts_0074CD80(const short *first, const short *last, int *out)
{
	int *dst = out;
	const short *stop = last;
	const short *src = first;
	int count = stop - src;

	while (count > 0)
	{
		*dst = *src;
		++src;
		++dst;
		--count;
	}
}

// ?bfmeWidenShorts_0074D6A0@@YAXPBF0PAH@Z
void bfmeWidenShorts_0074D6A0(const short *first, const short *last, int *out)
{
	int *dst = out;
	const short *stop = last;
	const short *src = first;
	int count = stop - src;

	while (count > 0)
	{
		*dst = *src;
		++src;
		++dst;
		--count;
	}
}
