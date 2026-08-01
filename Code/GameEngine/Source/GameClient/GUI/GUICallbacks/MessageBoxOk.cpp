// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class GameWindow;
class UnicodeString {};

__declspec(naked) GameWindow *MessageBoxOk(UnicodeString, UnicodeString, void (*)(void))
{
	__asm {
		_emit 0E9h
		_emit 0EBh
		_emit 0C3h
		_emit 047h
		_emit 000h
	}
}
