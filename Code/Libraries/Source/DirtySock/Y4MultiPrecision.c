// cl: /Od /GZ /MD /DNDEBUG
/* MULTI-PRECISION INTEGER PRIMITIVES, built /Od with /GZ.
 *
 * The representation is read out of the bodies here rather than assumed: LIMBS
 * ARE 16 BITS and are stored MOST-SIGNIFICANT FIRST.  The bit test computes
 * its word index as (16 * count - index - 1) / 16, counting from the END,
 * which is only correct for a most-significant-first array; the addition at
 * 0x0080FD30 -- not yet converted, see reverse/re_attempts.log -- walks all
 * three of its arrays backwards and shifts its carry down by 16 per limb,
 * which agrees and fixes the limb width.
 *
 * Placement is by address neighbourhood -- neither body reaches a string and
 * nothing here names the module.
 */

/* 0x0080FE70 TESTS ONE BIT, numbered from the LEAST significant end.
 *
 * Bit 0 lives in the LAST limb, which is why the word index is computed by
 * subtracting from the total rather than dividing directly -- the array is
 * most-significant-first but the bit numbering is not.
 *
 * IT RETURNS THE MASKED BIT, NOT A BOOLEAN: the value is the bit still in
 * place, so it is 0x0001 for bit 0 but 0x8000 for bit 15.  A caller comparing
 * against 1 works only for bit 0.  The result is also truncated to 16 bits and
 * returned through movzx, so the caller gets 0x0000..0x8000 and never a
 * sign-extended value.
 *
 * The limb width is a LOCAL initialised to 16 rather than a constant in the
 * expressions, and it is used four times; folding it into the arithmetic
 * compiles differently.
 */
int Rva0080FE70( const unsigned short *bits, int count, int index )
{
	int iWidth;
	int iBit;
	int iWord;
	unsigned short uResult;

	iWidth = 16;

	iBit = index % iWidth;
	iWord = ( iWidth * count - index - 1 ) / iWidth;

	uResult = (unsigned short)( bits[ iWord ] & ( 1 << iBit ) );
	return uResult;
}
