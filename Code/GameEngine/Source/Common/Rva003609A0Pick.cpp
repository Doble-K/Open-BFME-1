// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class GlobalData
{
public:
	unsigned char m_pad[0x218];
	unsigned m_218;
};

extern GlobalData *TheWritableGlobalData;

class Rva003609A0
{
	unsigned char m_pad[0x18];
	unsigned m_18;
	unsigned m_1C;

public:
	unsigned pick() const;
};

unsigned Rva003609A0::pick() const
{
	if (TheWritableGlobalData->m_218 == 4)
		return m_1C;
	return m_18;
}
