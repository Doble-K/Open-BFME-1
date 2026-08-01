class __declspec(novtable) AudioEventRTS
{
public:
	virtual ~AudioEventRTS();
};

__declspec(naked) AudioEventRTS::~AudioEventRTS()
{
	__asm {
		_emit 0E9h
		_emit 01Ch
		_emit 093h
		_emit 00Ah
		_emit 000h
	}
}
