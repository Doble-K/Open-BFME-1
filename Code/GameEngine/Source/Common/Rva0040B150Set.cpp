// cl: /O2 /Ob0

class UnicodeString
{
public:
	void set(const UnicodeString &);
};

UnicodeString g_rva0040b150_src;
UnicodeString g_rva0040b150_dst;

void rva0040b150()
{
	g_rva0040b150_dst.set(g_rva0040b150_src);
}
