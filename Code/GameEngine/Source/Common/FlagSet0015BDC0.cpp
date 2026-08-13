// cl: /DNDEBUG /MD

class AddressState0015BDC0
{
public:
	void setFlag();

private:
	unsigned char m_padding[0x44];
	bool m_flag;
};

void AddressState0015BDC0::setFlag()
{
	m_flag = true;
}
