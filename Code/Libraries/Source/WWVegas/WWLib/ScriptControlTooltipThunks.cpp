class AsciiString
{
};

class GameWindow
{
};

class ScriptEngine
{
public:
	void doNamedMapReveal(AsciiString const &);
	void undoNamedMapReveal(AsciiString const &);
};

class ControlBar
{
public:
	void showBuildTooltipLayout(GameWindow *);
};

class ScriptEnginedoNamedMapRevealShim
{
public:
	void doNamedMapReveal(AsciiString const & a0);
};

void ScriptEngine::doNamedMapReveal(AsciiString const & a0)
{
	((ScriptEnginedoNamedMapRevealShim *)this)->doNamedMapReveal(a0);
}

class ScriptEngineundoNamedMapRevealShim
{
public:
	void undoNamedMapReveal(AsciiString const & a0);
};

void ScriptEngine::undoNamedMapReveal(AsciiString const & a0)
{
	((ScriptEngineundoNamedMapRevealShim *)this)->undoNamedMapReveal(a0);
}

class ControlBarshowBuildTooltipLayoutShim
{
public:
	void showBuildTooltipLayout(GameWindow * a0);
};

void ControlBar::showBuildTooltipLayout(GameWindow * a0)
{
	((ControlBarshowBuildTooltipLayoutShim *)this)->showBuildTooltipLayout(a0);
}

