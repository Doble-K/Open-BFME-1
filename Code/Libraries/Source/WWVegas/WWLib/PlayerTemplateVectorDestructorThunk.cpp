// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class PlayerTemplate;

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

	__declspec(naked) vector<PlayerTemplate, allocator<PlayerTemplate> >::~vector()
	{
		__asm {
			_emit 0E9h
			_emit 05Fh
			_emit 0F5h
			_emit 00Ch
			_emit 000h
		}
	}
}
