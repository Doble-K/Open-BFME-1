// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class W3DAnimationInfo
{
public:
	~W3DAnimationInfo();
};

class W3DAnimationInfoDestructorShim
{
public:
	void destroy();
};

W3DAnimationInfo::~W3DAnimationInfo()
{
	((W3DAnimationInfoDestructorShim *)this)->destroy();
}
