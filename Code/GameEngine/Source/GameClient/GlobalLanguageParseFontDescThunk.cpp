class INI;

class GlobalLanguage
{
public:
	__declspec(dllexport) static void parseFontDesc(INI *, void *, void *, const void *);
};

__declspec(naked) void GlobalLanguage::parseFontDesc(INI *, void *, void *, const void *)
{
	__asm {
		_emit 0E9h
		_emit 02Ch
		_emit 0DDh
		_emit 042h
		_emit 000h
	}
}
