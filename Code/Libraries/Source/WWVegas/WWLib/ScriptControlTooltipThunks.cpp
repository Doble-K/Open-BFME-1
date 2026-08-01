class AsciiString
{
};

class ScriptEngine
{
public:
	void doNamedMapReveal(AsciiString const &);
	void undoNamedMapReveal(AsciiString const &);
};

class GameWindow
{
};

class ControlBar
{
public:
	void showBuildTooltipLayout(GameWindow *);
};

__declspec(naked) void ScriptEngine::doNamedMapReveal(AsciiString const &)
{
	__asm {
		_emit 0E9h
		_emit 0BCh
		_emit 0D5h
		_emit 032h
		_emit 000h
	}
}

__declspec(naked) void ScriptEngine::undoNamedMapReveal(AsciiString const &)
{
	__asm {
		_emit 0E9h
		_emit 081h
		_emit 0D1h
		_emit 033h
		_emit 000h
	}
}

__declspec(naked) void ControlBar::showBuildTooltipLayout(GameWindow *)
{
	__asm {
		_emit 0E9h
		_emit 038h
		_emit 0FDh
		_emit 00Ch
		_emit 000h
	}
}
