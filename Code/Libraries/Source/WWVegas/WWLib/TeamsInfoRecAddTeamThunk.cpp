class Dict;

class TeamsInfoRec
{
public:
	void addTeam(const Dict *);
};

__declspec(naked) void TeamsInfoRec::addTeam(const Dict *)
{
	__asm {
		_emit 0E9h
		_emit 063h
		_emit 016h
		_emit 005h
		_emit 000h
	}
}
