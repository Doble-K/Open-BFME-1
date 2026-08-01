// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

namespace GenericObjectCreationNugget
{
	struct AnimSet;
}

namespace _STL
{
	template <class T, class U>
	__declspec(naked) void _Construct(T *, const U &)
	{
		__asm {
			_emit 0E9h
			_emit 06Ch
			_emit 06Dh
			_emit 074h
			_emit 000h
		}
	}

	template void _Construct<GenericObjectCreationNugget::AnimSet, GenericObjectCreationNugget::AnimSet>(GenericObjectCreationNugget::AnimSet *, const GenericObjectCreationNugget::AnimSet &);
}
