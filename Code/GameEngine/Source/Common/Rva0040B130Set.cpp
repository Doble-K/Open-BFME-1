// cl: /O2 /Ob0

class UnicodeString
{
public:
	void set(const UnicodeString &);
};

UnicodeString g_rva0040b130;

class Rva0040B130
{
	char m_lead[8];
	UnicodeString m_str;

public:
	void run();
};

void Rva0040B130::run()
{
	m_str.set(g_rva0040b130);
}
