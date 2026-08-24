// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva0060D3D0Obj
{
	char m_pad[0x2C];
	unsigned char m_value;
};

Rva0060D3D0Obj *g_rva0060D3D0;

unsigned char rva0060D3D0Get()
{
	return g_rva0060D3D0->m_value;
}
