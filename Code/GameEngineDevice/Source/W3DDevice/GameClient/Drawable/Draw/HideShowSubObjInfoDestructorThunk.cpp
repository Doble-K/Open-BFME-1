// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class ModelConditionInfo
{
public:
	struct HideShowSubObjInfo
	{
		~HideShowSubObjInfo();
	};
};

__declspec(naked) ModelConditionInfo::HideShowSubObjInfo::~HideShowSubObjInfo()
{
	__asm {
		_emit 0E9h
		_emit 0BCh
		_emit 052h
		_emit 033h
		_emit 000h
	}
}
