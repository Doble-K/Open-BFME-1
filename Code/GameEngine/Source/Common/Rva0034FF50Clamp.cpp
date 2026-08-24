// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva0034FF50Clamp
{
public:
	void maybeReplace();

private:
	int m_value;
};

void Rva0034FF50Clamp::maybeReplace()
{
	if (m_value == 15)
		m_value = 61;
}
