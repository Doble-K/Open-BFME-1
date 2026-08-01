class Mission
{
};

class Campaign
{
public:
	Mission * getNextMission(Mission *);
};

__declspec(naked) Mission * Campaign::getNextMission(Mission *)
{
	__asm {
		_emit 0E9h
		_emit 0FFh
		_emit 09Eh
		_emit 058h
		_emit 000h
	}
}
