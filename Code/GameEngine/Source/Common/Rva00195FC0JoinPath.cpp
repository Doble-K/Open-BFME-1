// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
#include "string_base.h"

typedef int Int;

class AsciiString
{
public:
	AsciiString( const AsciiString &other );
	~AsciiString();

	void concat( const char *text, Int length );
	void concat( char ch ) { concat( &ch, 1 ); }

	Int getLength( void ) const
	{
		return m_string.m_data ? m_string.m_data->length : 0;
	}

	const char *str( void ) const
	{
		return m_string.m_data ? &m_string.m_data->data[ 0 ] : "";
	}

private:
	StringBase<char> m_string;
};

AsciiString Rva00195FC0JoinPath( const AsciiString &left, const AsciiString &right )
{
	AsciiString path( left );
	path.concat( '/' );
	path.concat( right.str(), right.getLength() );
	return path;
}
