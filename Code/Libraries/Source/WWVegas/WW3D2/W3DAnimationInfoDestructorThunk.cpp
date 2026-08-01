// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class W3DAnimationInfo
{
public:
	~W3DAnimationInfo();
};

__declspec(naked) W3DAnimationInfo::~W3DAnimationInfo()
{
	__asm {
		_emit 0E9h
		_emit 063h
		_emit 000h
		_emit 05Fh
		_emit 000h
	}
}
