// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class MultiFixedPoolDecalSystemClass
{
public:
	class LogicalDecalClass
	{
	public:
		~LogicalDecalClass();
	};
};

__declspec(naked) MultiFixedPoolDecalSystemClass::LogicalDecalClass::~LogicalDecalClass()
{
	__asm {
		_emit 0E9h
		_emit 090h
		_emit 0D4h
		_emit 05Ah
		_emit 000h
	}
}
