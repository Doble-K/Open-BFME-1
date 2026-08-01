// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

enum ObjectID
{
};

namespace _STL
{
	template <class First, class Second>
	struct pair
	{
	};

	template <class Type>
	class allocator
	{
	};

	template <class Type, class Allocator>
	class vector
	{
	public:
		vector &operator=(const vector &);
	};

	__declspec(naked) vector<pair<ObjectID, unsigned int>, allocator<pair<ObjectID, unsigned int> > > &vector<pair<ObjectID, unsigned int>, allocator<pair<ObjectID, unsigned int> > >::operator=(const vector<pair<ObjectID, unsigned int>, allocator<pair<ObjectID, unsigned int> > > &)
	{
		__asm {
			_emit 0E9h
			_emit 08Ch
			_emit 080h
			_emit 006h
			_emit 000h
		}
	}
}
