// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

struct Rva00368B80Entry
{
	unsigned int m_key;
	unsigned int m_unused;
	unsigned int m_limit;
};

struct Rva00368B80Flags
{
	int getSingleBit() const
	{
		for( int index = 0; index < 7; ++index )
		{
			if( m_bits & ( 1 << ( index & 31 ) ) )
				return index;
		}

		return -1;
	}

	unsigned int m_bits;
};

struct Rva00368B80LookupResult
{
	char m_unused[ 12 ];
	Rva00368B80Flags m_flags;
};

struct Rva00368B80Registry
{
	Rva00368B80LookupResult *lookup( unsigned int key );
};

extern Rva00368B80Registry *g_rva00368B80Registry;

struct Rva00368B80Predicate
{
	bool test( unsigned int value, const Rva00368B80Entry *entry ) const;

	char m_unused[ 0x30 ];
	unsigned int m_limits[ 7 ];
};

bool Rva00368B80Predicate::test( unsigned int value,
	const Rva00368B80Entry *entry ) const
{
	int index = g_rva00368B80Registry->lookup( entry->m_key )
		->m_flags.getSingleBit();

	bool belowLimit = value < entry->m_limit;
	bool atOrBelowThreshold =
		index >= 0 && value <= m_limits[ index ];
	if( belowLimit && !atOrBelowThreshold )
		return true;

	return false;
}
