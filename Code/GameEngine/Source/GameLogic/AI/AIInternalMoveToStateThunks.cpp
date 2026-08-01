enum StateReturnType
{
};

enum StateExitType
{
};

class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType);
	virtual StateReturnType update();
};

__declspec(naked) StateReturnType AIInternalMoveToState::onEnter()
{
	__asm {
		_emit 0E9h
		_emit 0D4h
		_emit 007h
		_emit 015h
		_emit 000h
	}
}

__declspec(naked) void AIInternalMoveToState::onExit(StateExitType)
{
	__asm {
		_emit 0E9h
		_emit 06Ah
		_emit 09Ah
		_emit 014h
		_emit 000h
	}
}

__declspec(naked) StateReturnType AIInternalMoveToState::update()
{
	__asm {
		_emit 0E9h
		_emit 075h
		_emit 0A5h
		_emit 012h
		_emit 000h
	}
}
