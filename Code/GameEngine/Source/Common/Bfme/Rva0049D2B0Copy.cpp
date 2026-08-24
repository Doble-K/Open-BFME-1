// cl: /DNDEBUG /MD /EHsc

class Rva0049D2B0
{
public:
	void copy(unsigned *first, unsigned *second) const;

private:
	unsigned char m_unmodelled_000[0x2d0];
	unsigned m_word0;
	unsigned m_word1;
};

void Rva0049D2B0::copy(unsigned *first, unsigned *second) const
{
	*first = m_word0;
	*second = m_word1;
}
