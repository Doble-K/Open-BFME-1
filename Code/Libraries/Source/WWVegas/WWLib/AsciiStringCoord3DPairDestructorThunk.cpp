// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class AsciiString;
struct Coord3D;

namespace _STL
{
template <class First, class Second>
class pair
{
public:
	~pair();
};

class AsciiStringCoord3DPairDestructorShim
{
public:
	void destroy();
};

pair<AsciiString const, Coord3D>::~pair()
{
	((AsciiStringCoord3DPairDestructorShim *)this)->destroy();
}
}
