// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class FXBoneInfo
{
public:
	~FXBoneInfo();
};

__declspec(naked) FXBoneInfo::~FXBoneInfo()
{
	__asm {
		_emit 083h
		_emit 0C1h
		_emit 004h
		_emit 0E9h
		_emit 098h
		_emit 097h
		_emit 050h
		_emit 000h
	}
}
