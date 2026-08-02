// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class ModelConditionInfo
{
public:
	class HideShowSubObjInfo
	{
	public:
		~HideShowSubObjInfo();
	};
};

class ModelConditionInfoHideShowSubObjInfoDestructorShim
{
public:
	void destroy();
};

ModelConditionInfo::HideShowSubObjInfo::~HideShowSubObjInfo()
{
	((ModelConditionInfoHideShowSubObjInfoDestructorShim *)this)->destroy();
}
