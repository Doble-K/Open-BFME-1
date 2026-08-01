class Object;
enum CommandSourceType
{
};

class AIGroup
{
	void groupAttackObjectPrivate(bool, Object *, int, CommandSourceType);
};

__declspec(naked) void AIGroup::groupAttackObjectPrivate(bool, Object *, int, CommandSourceType)
{
	__asm {
		_emit 0E9h
		_emit 0CAh
		_emit 040h
		_emit 011h
		_emit 000h
	}
}
