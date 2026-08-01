// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

struct ICoord2D;
struct Coord3D;

namespace _STL
{
	template <class T, class U>
	struct pair
	{
		T first;
		U second;
	};

	template <class T, class U>
	__declspec(naked) void _Construct(T *, const U &)
	{
		__asm {
			_emit 0E9h
			_emit 048h
			_emit 091h
			_emit 011h
			_emit 000h
		}
	}

	template void _Construct<pair<ICoord2D, Coord3D>, pair<ICoord2D, Coord3D> >(pair<ICoord2D, Coord3D> *, const pair<ICoord2D, Coord3D> &);
}
