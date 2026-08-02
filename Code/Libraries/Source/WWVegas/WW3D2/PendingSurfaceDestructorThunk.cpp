// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Render2DSentenceClass
{
public:
	class PendingSurfaceStruct
	{
	public:
		~PendingSurfaceStruct();
	};
};

class Render2DSentenceClassPendingSurfaceStructDestructorShim
{
public:
	void destroy();
};

Render2DSentenceClass::PendingSurfaceStruct::~PendingSurfaceStruct()
{
	((Render2DSentenceClassPendingSurfaceStructDestructorShim *)this)->destroy();
}
