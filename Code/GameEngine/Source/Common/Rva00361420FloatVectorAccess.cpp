// Address-derived reconstruction of the 67-byte retail body at RVA 0x00361420.
// The bytes prove a [first,last) array of 0x58-byte elements at +0x18/+0x1C,
// a signed bounds check, and a float-returning element call.  The rel32 call
// targets the existing retail thunk at RVA 0x0002CC5F.  Class and method names
// remain descriptive because no trustworthy higher-level identity is known.

class Rva003608F0FloatElement
{
public:
	float value();
	char m_storage[ 0x58 ];
};

class Rva00361420FloatRange
{
public:
	unsigned int size() const { return m_last - m_first; }
	Rva003608F0FloatElement &operator[]( int index ) { return m_first[ index ]; }

private:
	Rva003608F0FloatElement *m_first;
	Rva003608F0FloatElement *m_last;
};

class Rva00361420FloatVector
{
public:
	float valueAt( int index );

private:
	char m_lead[ 0x18 ];
	Rva00361420FloatRange m_values;
};

float Rva00361420FloatVector::valueAt( int index )
{
	if ( index >= 0 && static_cast<unsigned int>( index ) < m_values.size() ) {
		return m_values[ index ].value();
	}

	return 0.0f;
}
