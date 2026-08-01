class TeamFactory
{
public:
	void clear();
};

__declspec(naked) void TeamFactory::clear()
{
	__asm {
		_emit 0E9h
		_emit 0F4h
		_emit 0E7h
		_emit 00Ch
		_emit 000h
	}
}
