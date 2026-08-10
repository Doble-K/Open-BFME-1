// cl: /DNDEBUG /MD /EHs-c-
// Lift the draw-callback window-file parser to clean C++.

typedef int Int;
typedef bool Bool;

extern "C" __declspec(dllimport) char *__cdecl strtok(char *string, const char *separators);
extern "C" unsigned int __cdecl strlen(const char *string);

class AsciiString
{
public:
	void set(const char *string, Int length);

	const char *str(void) const
	{
		return m_data ? (const char *)((unsigned char *)m_data + 8) : "";
	}

	void *m_data;
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class GameWindow;
class WinInstanceData;
typedef void (__cdecl *GameWinDrawFunc)(GameWindow *, WinInstanceData *);

class FunctionLexicon
{
public:
	enum TableIndex
	{
		TABLE_ANY = -1
	};

	GameWinDrawFunc gameWinDrawFunc(NameKeyType key, TableIndex index = TABLE_ANY);
};

extern AsciiString theDrawString;
extern NameKeyGenerator *TheNameKeyGenerator;
extern FunctionLexicon *TheFunctionLexicon;
extern GameWinDrawFunc drawFunc;

// ?parseDrawCallback@@YA_NPADPAVWinInstanceData@@0PAX@Z
Bool parseDrawCallback(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	char *c, *ptr;
	char *stringSeps = "\"";

	ptr = buffer;
	while (*ptr != '"')
		ptr++;
	ptr++;
	c = strtok(ptr, stringSeps);

	theDrawString.set(c, c ? (Int)strlen(c) : 0);
	NameKeyType key = TheNameKeyGenerator->nameToKey(theDrawString.str());
	drawFunc = TheFunctionLexicon->gameWinDrawFunc(key);

	return true;
}
