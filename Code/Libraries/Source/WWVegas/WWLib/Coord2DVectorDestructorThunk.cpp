// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

struct ICoord2D;

namespace _STL
{
template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
public:
	~vector();
};

class ICoord2DVectorDestructorShim
{
public:
	void destroy();
};

vector<ICoord2D, allocator<ICoord2D> >::~vector()
{
	((ICoord2DVectorDestructorShim *)this)->destroy();
}
}
