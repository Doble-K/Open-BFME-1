// Address-derived seven-byte member at 0x0069DE60.

class Rva0069DE60
{
public:
	Rva0069DE60 *clear();

private:
	char m_pad00[ 8 ];
	bool m_flag;
};

Rva0069DE60 *Rva0069DE60::clear()
{
	m_flag = false;
	return this;
}
