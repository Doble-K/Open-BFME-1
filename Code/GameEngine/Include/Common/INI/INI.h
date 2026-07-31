#pragma once
#include "ascii_string.h"
class INI {
public:
	INI();
	~INI();
	// BFME's load takes four arguments where ZH's takes three; the subsystem
	// loader at 0x000BB310 calls it as load(file, 1, 0, xfer).
	void load(AsciiString filename, int loadType, int reload, void* xfer);
	static bool loadSubsystemFiles(const char* subsystem, void* xfer);
	const char* getNextToken(const char* seps = 0);
	void initFromINI(void* what, const struct FieldParse* parseTable);
	const char* getNextTokenOrNull(const char* seps = 0);
	static float scanReal(const char* token);
	static int scanInt(const char* token);
	static int scanBool(const char* token);
	static int scanIndexList(const char* token, const char* const* names);

private:
	// Not ported. The padding keeps sizeof(INI) at retail's 0x848 so callers that
	// stack-allocate one get retail's frame; INI::INI() at 0x00851230 writes as
	// far as [this+0x834].
	char m_unported[0x848];
};
typedef void (*INIFieldParseProc)(INI*, void*, void*, const void*);
struct FieldParse { const char* token; INIFieldParseProc parse; const void* userData; int offset; };
