class __declspec(novtable) UserPreferences
{
public:
	virtual ~UserPreferences();
};

__declspec(naked) UserPreferences::~UserPreferences()
{
	__asm {
		_emit 0E9h
		_emit 0D0h
		_emit 0BCh
		_emit 006h
		_emit 000h
	}
}
