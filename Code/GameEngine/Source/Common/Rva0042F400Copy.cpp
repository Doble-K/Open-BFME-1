// cl: /O2 /Ob0

class AsciiString
{
public:
	AsciiString(const AsciiString &other);

private:
	void *m_item;
};

class Rva0042F400
{
	AsciiString m_str;
	short m_04;

public:
	Rva0042F400(const Rva0042F400 &other);
};

Rva0042F400::Rva0042F400(const Rva0042F400 &other)
	: m_str(other.m_str)
	, m_04(other.m_04)
{
}
