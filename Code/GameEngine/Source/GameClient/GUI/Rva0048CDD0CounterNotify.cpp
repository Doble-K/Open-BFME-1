// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: address-derived counter/notification method at 0x0048CDD0.

extern void *Rva012ED238Global;
void __stdcall Rva009F8878Notify(void *, void *);

class Rva0048CDD0CounterNotify
{
public:
	void decrementAndNotify();

private:
	unsigned char m_unknown00[0x10];
	void *m_value;
	unsigned char m_unknown14[4];
	int m_count;
};

void Rva0048CDD0CounterNotify::decrementAndNotify()
{
	if (--m_count <= 0) {
		m_count = 0;
		Rva009F8878Notify(Rva012ED238Global, m_value);
	}
}
