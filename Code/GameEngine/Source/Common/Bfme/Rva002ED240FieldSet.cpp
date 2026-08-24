// cl: /DNDEBUG /MD /EHsc
// Retail stores an activation marker and the one-byte state beside it.

class Rva002ED240
{
public:
	void set( unsigned char state );

private:
	unsigned char m_padding[0xE4];
	unsigned char m_active;
	unsigned char m_state;
};

void Rva002ED240::set( unsigned char state )
{
	m_active = 1;
	m_state = state;
}
