// cl: /DNDEBUG /MD /EHs-c-

extern "C" int __stdcall closesocket( int s );

class Rva00885980Class
{
public:
	char m_pad0[4];
	int m_socket; // at 0x4
	int m_socket8; // at 0x8

	int d_00885980( void );
	void d_00885960( void );
};

int Rva00885980Class::d_00885980( void )
{
	closesocket( m_socket );
	return 0;
}

void Rva00885980Class::d_00885960( void )
{
	closesocket( m_socket8 );
	m_socket8 = 0;
}
