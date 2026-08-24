// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva00322040Positive
{
public:
	bool isPositive();

private:
	char m_pad[0x40];
	int m_value;
};

bool Rva00322040Positive::isPositive()
{
	return m_value > 0;
}
