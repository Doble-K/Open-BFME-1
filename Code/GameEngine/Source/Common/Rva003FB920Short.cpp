// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva003FB920Short
{
public:
	void set(short value);

private:
	char m_pad[0x0A];
	short m_value;
};

void Rva003FB920Short::set(short value)
{
	m_value = value;
}
