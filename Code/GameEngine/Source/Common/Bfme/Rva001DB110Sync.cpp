// cl: /DNDEBUG /MD /EHsc

class Rva001DB110
{
public:
	void sync();

private:
	unsigned m_value;
	unsigned m_source;
};

void Rva001DB110::sync()
{
	m_value = m_source;
}
