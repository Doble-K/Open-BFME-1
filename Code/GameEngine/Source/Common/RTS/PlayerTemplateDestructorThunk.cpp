// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class PlayerTemplate
{
public:
	~PlayerTemplate();
};

__declspec(naked) PlayerTemplate::~PlayerTemplate()
{
	__asm {
		_emit 0E9h
		_emit 0CDh
		_emit 0A5h
		_emit 00Ch
		_emit 000h
	}
}
