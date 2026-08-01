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
	protected:
		void _M_insert_overflow(Type *, const Type &, const struct __false_type &, unsigned int, bool);
	};

	struct __false_type
	{
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

	__declspec(naked) void vector<pair<ObjectID, unsigned int>, allocator<pair<ObjectID, unsigned int> > >::_M_insert_overflow(pair<ObjectID, unsigned int> *, pair<ObjectID, unsigned int> const &, const __false_type &, unsigned int, bool)
	{
		__asm {
			_emit 0E9h
			_emit 057h
			_emit 0B5h
			_emit 006h
			_emit 000h
		}
	}

	__declspec(naked) void vector<pair<ObjectID, ObjectID>, allocator<pair<ObjectID, ObjectID> > >::_M_insert_overflow(pair<ObjectID, ObjectID> *, pair<ObjectID, ObjectID> const &, const __false_type &, unsigned int, bool)
	{
		__asm {
			_emit 0E9h
			_emit 074h
			_emit 0EDh
			_emit 074h
			_emit 000h
		}
	}
}
