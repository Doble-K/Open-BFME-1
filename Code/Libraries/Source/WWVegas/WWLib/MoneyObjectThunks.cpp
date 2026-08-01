enum DisabledType
{
	DisabledTypePlaceholder
};

class Money
{
public:
	void deposit(unsigned int, bool);
};

class Object
{
public:
	void setDisabledUntil(DisabledType, unsigned int);
};

__declspec(naked) void Money::deposit(unsigned int, bool)
{
	__asm {
		_emit 0E9h
		_emit 0BEh
		_emit 009h
		_emit 00Ah
		_emit 000h
	}
}

__declspec(naked) void Object::setDisabledUntil(DisabledType, unsigned int)
{
	__asm {
		_emit 0E9h
		_emit 071h
		_emit 04Bh
		_emit 019h
		_emit 000h
	}
}
