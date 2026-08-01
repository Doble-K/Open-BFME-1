class __declspec(novtable) GameMessageList
{
public:
	virtual ~GameMessageList();
};

__declspec(naked) GameMessageList::~GameMessageList()
{
	__asm {
		_emit 0E9h
		_emit 02Ah
		_emit 0C0h
		_emit 007h
		_emit 000h
	}
}
