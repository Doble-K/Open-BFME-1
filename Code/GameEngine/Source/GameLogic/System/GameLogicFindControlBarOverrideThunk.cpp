class AsciiString
{
};

class CommandButton
{
};

class GameLogic
{
public:
	bool findControlBarOverride(AsciiString const &, int, CommandButton const *&) const;
};

__declspec(naked) bool GameLogic::findControlBarOverride(AsciiString const &, int, CommandButton const *&) const
{
	__asm {
		_emit 0E9h
		_emit 022h
		_emit 0F6h
		_emit 038h
		_emit 000h
	}
}
