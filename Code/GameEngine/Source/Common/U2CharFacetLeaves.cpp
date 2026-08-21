// Eight leaf members from the character-facet neighbourhood of
// T2CtypeTableFacets.cpp.  None of them contains a relocation, so every byte
// here is concrete and the only thing to get right is the shape.
//
// TWO PASS-THROUGHS.  0x00840830 is `mov al,[esp+4] / ret 4` and 0x00840870 is
// `mov al,[esp+4] / ret 8`: a __thiscall member that never reads ecx, takes one
// char and returns it unchanged, and its two-argument twin that returns the
// FIRST argument and ignores the second.  That is the widen/narrow pair of a
// facet whose two character types are the same width, so the conversion is the
// identity and the default character of the narrowing form is dead.  They sit
// a few rows from the mask-table `is` at 0x00840910, which is what places them
// in this family rather than among the general one-argument forwarders.
//
// THREE CONSTANTS.  0x00844500, 0x00844510 and 0x00848090 are `mov ax,IMM /
// ret` with no arguments at all, returning 0x2E, 0x2C and 0x20 -- '.', ',' and
// ' ' -- as SIXTEEN-bit values.  A member returning `char` would leave the byte
// in al; the operand size says the return type is two bytes wide, i.e. the wide
// character type of the same facet family.  Three punctuation characters
// published by three no-argument members is the shape of a numeric-punctuation
// facet, but nothing in these bytes names one, so the classes are addresses.
//
// THREE ALL-ONES.  0x0083FF70, 0x0083FF80 and 0x0083FF90 return 0xFFFF in ax,
// the first with no arguments and the other two with one dword each.  MSVC 7.1
// spells an all-ones 16-bit constant `or ax,0FFFFh` rather than `mov ax,-1`
// (both are four bytes), so the source is a plain `return` of a 16-bit -1 --
// the not-a-character result these facets hand back on failure.  0x0083FF80 and
// 0x0083FF90 are byte-identical to each other; they are kept as two members
// because they are two addresses, not one folded body.

struct Rva00840830Facet
{
	char widen(char c) const;
	char narrow(char c, char dflt) const;
};

char Rva00840830Facet::widen(char c) const
{
	return c;
}

char Rva00840830Facet::narrow(char c, char) const
{
	return c;
}

struct Rva00844500Punct
{
	unsigned short decimalPoint() const;
	unsigned short thousandsSep() const;
};

unsigned short Rva00844500Punct::decimalPoint() const
{
	return (unsigned short)'.';
}

unsigned short Rva00844500Punct::thousandsSep() const
{
	return (unsigned short)',';
}

struct Rva00848090Punct
{
	unsigned short fill() const;
};

unsigned short Rva00848090Punct::fill() const
{
	return (unsigned short)' ';
}

struct Rva0083FF70Facet
{
	unsigned short none() const;
	unsigned short noneOf(int c) const;
	unsigned short noneFor(int c) const;
};

unsigned short Rva0083FF70Facet::none() const
{
	return (unsigned short)-1;
}

unsigned short Rva0083FF70Facet::noneOf(int) const
{
	return (unsigned short)-1;
}

unsigned short Rva0083FF70Facet::noneFor(int) const
{
	return (unsigned short)-1;
}
