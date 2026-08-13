// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <list>

class INI
{
public:
	void initFromINI(void *, const void *);
};

class ShellMenuSchemeLine
{
public:
	ShellMenuSchemeLine()
	{
		m_startPos[0] = m_startPos[1] = 0;
		m_endPos[0] = m_endPos[1] = 0;
		m_color = 0x00ffffff;
		m_width = 1;
	}

private:
	int m_startPos[2];
	int m_endPos[2];
	int m_width;
	unsigned int m_color;
};

class ShellMenuScheme
{
private:
	unsigned char m_pad00[4];
	_STL::list<void *> m_imageList;
	_STL::list<ShellMenuSchemeLine *> m_lineList;

	friend class ShellMenuSchemeManager;
};

extern const unsigned char g_shellMenuSchemeLineFieldParse[];

class ShellMenuSchemeManager
{
public:
	static void __cdecl parseLinePart(INI *, void *, void *, const void *);
};

// ?parseLinePart@ShellMenuSchemeManager@@SAXPAVINI@@PAX1PBX@Z
void __cdecl ShellMenuSchemeManager::parseLinePart(INI *ini, void *instance,
	void *, const void *)
{
	ShellMenuSchemeLine *schemeLine = new ShellMenuSchemeLine;
	ini->initFromINI(schemeLine, g_shellMenuSchemeLineFieldParse);

	if (schemeLine != 0)
	{
		ShellMenuScheme *scheme = static_cast<ShellMenuScheme *>(instance);
		scheme->m_lineList.push_back(schemeLine);
	}
}
