// cl: /O2 /Ob0

class Rva006F6330
{
	unsigned m_vt;

public:
	Rva006F6330 *apply();
};

Rva006F6330 *g_rva006F6330;

Rva006F6330 *Rva006F6330::apply()
{
	m_vt = 0x011202B0u;
	g_rva006F6330 = this;
	return this;
}
