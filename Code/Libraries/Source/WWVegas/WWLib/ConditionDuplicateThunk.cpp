class Condition
{
public:
	Condition * duplicate() const;
};

__declspec(naked) Condition * Condition::duplicate() const
{
	__asm {
		_emit 0E9h
		_emit 0A2h
		_emit 0BBh
		_emit 033h
		_emit 000h
	}
}
