class Rva00368C10Mask
{
public:
	unsigned int m_bits;
};

class Rva00368C10Values
{
public:
	char m_unreconstructed[ 0x48 ];
	int m_values[ 8 ];

	int valueFor(const Rva00368C10Mask *mask) const;
};

int Rva00368C10Values::valueFor(const Rva00368C10Mask *mask) const
{
	int index;
	for( index = 0; index < 7; ++index )
	{
		if( mask->m_bits & (1u << (index & 0x1F)) )
			goto found;
	}
	index = -1;

found:
	return m_values[index + 1];
}

// @?valueFor@Rva00368C10Values@@QBEHPBVRva00368C10Mask@@@Z 0x00368C10
