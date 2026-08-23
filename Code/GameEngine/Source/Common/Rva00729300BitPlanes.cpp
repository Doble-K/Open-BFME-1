// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

typedef unsigned char Byte;

struct Rva00729300Bytes
{
	Byte *m_begin;
	Byte *m_end;

	unsigned size() const { return (unsigned)(m_end - m_begin); }
	Byte operator[]( int index ) const { return m_begin[index]; }
};

class Rva00729300BitPlane
{
public:
	bool test( int x, int y ) const;

private:
	Byte m_opaque00[0x08];
	int m_width;
	int m_height;
	Byte m_opaque10[0x24];
	int m_stride;
	Byte m_opaque38[0x0c];
	Rva00729300Bytes m_bits;
};

class Rva00729370BitPlane
{
public:
	bool test( int x, int y ) const;

private:
	Byte m_opaque00[0x08];
	int m_width;
	int m_height;
	Byte m_opaque10[0x24];
	int m_stride;
	Byte m_opaque38[0x18];
	Rva00729300Bytes m_bits;
};

bool Rva00729300BitPlane::test( int x, int y ) const
{
	register const Rva00729300BitPlane *self = this;
	if( x < 0 || y < 0 || y >= self->m_height || x >= self->m_width )
	{
		return false;
	}

	const int index = self->m_stride * y + (x >> 3);
	if( (unsigned)index >= self->m_bits.size() )
	{
		return false;
	}

	int mask = 1;
	mask <<= x & 7;
	Byte value = self->m_bits[index];
	bool result = (value & mask) != 0;
	return result;
}

bool Rva00729370BitPlane::test( int x, int y ) const
{
	register const Rva00729370BitPlane *self = this;
	if( x < 0 || y < 0 || y >= self->m_height || x >= self->m_width )
	{
		return false;
	}

	const int index = self->m_stride * y + (x >> 3);
	if( (unsigned)index >= self->m_bits.size() )
	{
		return false;
	}

	int mask = 1;
	mask <<= x & 7;
	Byte value = self->m_bits[index];
	bool result = (value & mask) != 0;
	return result;
}
