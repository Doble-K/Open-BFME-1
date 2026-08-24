class Rva006DACDFObject
{
public:
	void setHalf();

private:
	unsigned char m_prefix[0x0c];
	float m_value;
};

void Rva006DACDFObject::setHalf()
{
	m_value = 1.0f;
}
