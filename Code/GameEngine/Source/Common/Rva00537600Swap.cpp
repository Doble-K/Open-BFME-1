// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva00537600Swap
{
public:
	int replace(int value);

private:
	int m_pad;
	int m_value;
};

int Rva00537600Swap::replace(int value)
{
	int old = m_value;
	m_value = value;
	return old;
}
