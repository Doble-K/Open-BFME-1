// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva005BD470Obj
{
	unsigned char m_pad[0x1C];
	unsigned char m_1C;
};

int rva005BD470(const Rva005BD470Obj *p)
{
	return p->m_1C == 0;
}
