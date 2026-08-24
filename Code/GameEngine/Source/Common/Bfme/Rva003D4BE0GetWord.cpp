// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x003D4BE0 (7 bytes).

class Rva003D4BE0
{
public:
	unsigned short getWord();

private:
	unsigned short *m_value;
};

unsigned short Rva003D4BE0::getWord()
{
	return m_value[2];
}
