// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class INI;

__declspec(naked) void iniParseObjectFilter(INI *, void *, void *, const void *)
{
	__asm {
		_emit 0E9h
		_emit 006h
		_emit 05Ch
		_emit 036h
		_emit 000h
	}
}
