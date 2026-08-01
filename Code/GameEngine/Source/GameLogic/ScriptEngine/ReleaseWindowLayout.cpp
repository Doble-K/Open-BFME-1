// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class WindowLayout;

__declspec(naked) void ReleaseWindowLayout(WindowLayout *)
{
	__asm {
		_emit 0E9h
		_emit 06Bh
		_emit 08Ch
		_emit 04Dh
		_emit 000h
	}
}
