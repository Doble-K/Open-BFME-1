// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Xfer;
class GameClientRandomVariable;

__declspec(naked) void xferRandomVariable(Xfer &, GameClientRandomVariable &)
{
	__asm {
		_emit 0E9h
		_emit 099h
		_emit 0D6h
		_emit 00Ch
		_emit 000h
	}
}
