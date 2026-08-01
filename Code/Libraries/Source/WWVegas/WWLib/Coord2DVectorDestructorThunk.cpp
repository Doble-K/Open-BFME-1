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

	__declspec(naked) vector<ICoord2D, allocator<ICoord2D> >::~vector()
	{
		__asm {
			_emit 0E9h
			_emit 0EEh
			_emit 0ECh
			_emit 008h
			_emit 000h
		}
	}
}
