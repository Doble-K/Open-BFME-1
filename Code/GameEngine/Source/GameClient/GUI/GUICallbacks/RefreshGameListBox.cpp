// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class GameWindow;

__declspec(naked) void RefreshGameListBox(GameWindow *, bool)
{
	__asm {
		_emit 0E9h
		_emit 0BFh
		_emit 0E5h
		_emit 061h
		_emit 000h
	}
}
