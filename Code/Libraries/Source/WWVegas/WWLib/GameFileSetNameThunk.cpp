class GameFileClass
{
public:
	virtual char const *Set_Name(char const *);
};

__declspec(naked) char const *GameFileClass::Set_Name(char const *)
{
	__asm {
		_emit 0E9h
		_emit 0A6h
		_emit 0F4h
		_emit 06Eh
		_emit 000h
	}
}
