// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva00889690Obj
{
	char m_pad[0x9F4B];
	char m_value;
	char m_flag;
};

Rva00889690Obj *g_rva00889690;

void rva00889690Set()
{
	g_rva00889690->m_flag = 1;
}

char rva008896D0Get()
{
	return g_rva00889690->m_value;
}
