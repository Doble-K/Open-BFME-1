class AsciiString
{
};

class ScriptEngine
{
public:
	void createNamedMapReveal(AsciiString const &, AsciiString const &, float, AsciiString const &);
};

__declspec(naked) void ScriptEngine::createNamedMapReveal(AsciiString const &, AsciiString const &, float, AsciiString const &)
{
	__asm {
		_emit 0E9h
		_emit 091h
		_emit 026h
		_emit 032h
		_emit 000h
	}
}
