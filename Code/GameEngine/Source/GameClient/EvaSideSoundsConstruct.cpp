// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

struct EvaSideSounds;

namespace _STL
{
	template <class T, class U>
	__declspec(naked) void _Construct(T *, const U &)
	{
		__asm {
			_emit 0E9h
			_emit 0FEh
			_emit 0A1h
			_emit 035h
			_emit 000h
		}
	}

	template void _Construct<EvaSideSounds, EvaSideSounds>(EvaSideSounds *, const EvaSideSounds &);
}
