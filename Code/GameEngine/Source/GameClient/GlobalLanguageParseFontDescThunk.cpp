class INI;

class GlobalLanguage
{
public:
	__declspec(dllexport) static void parseFontDesc(INI *, void *, void *, const void *);
};

class GlobalLanguageParseFontDescShim
{
public:
	static void parseFontDesc(INI *, void *, void *, const void *);
};

void GlobalLanguage::parseFontDesc(INI *ini, void *field, void *data, const void *extra)
{
	GlobalLanguageParseFontDescShim::parseFontDesc(ini, field, data, extra);
}
