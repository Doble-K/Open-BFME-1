// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva000C9710Obj
{
	char m_pad[0xB24];
	int m_value;
};

Rva000C9710Obj *g_rva000C9710;

int rva000C9710Get()
{
	return g_rva000C9710->m_value;
}
