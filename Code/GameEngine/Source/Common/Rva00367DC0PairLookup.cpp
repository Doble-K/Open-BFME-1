// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// This body walks a half-open range of two-dword records, compares the first
// dword with the requested key, and copies the second dword to the caller's
// output on success.  Names remain descriptive because the bytes do not prove
// the owning subsystem.

struct Rva00367DC0Pair
{
	unsigned int m_key;
	unsigned int m_value;
};

class Rva00367DC0PairRange
{
public:
	unsigned char find( unsigned int key, unsigned int *value ) const;

private:
	Rva00367DC0Pair *m_first;
	Rva00367DC0Pair *m_last;
};

unsigned char Rva00367DC0PairRange::find(
	unsigned int key,
	unsigned int *value ) const
{
	for( Rva00367DC0Pair *entry = m_first; entry != m_last; ++entry )
	{
		if( entry->m_key == key )
		{
			*value = entry->m_value;
			return 1;
		}
	}

	return 0;
}
