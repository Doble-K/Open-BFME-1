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

class ObjectIDPairVectorAssignShim
{
public:
	vector<pair<ObjectID, unsigned int>, allocator<pair<ObjectID, unsigned int> > > &assign(
		const vector<pair<ObjectID, unsigned int>, allocator<pair<ObjectID, unsigned int> > > &rhs);
};

class ObjectIDPairOverflowShim
{
public:
	void insert_overflow(pair<ObjectID, unsigned int> *pos, pair<ObjectID, unsigned int> const &x, const __false_type &tag, unsigned int n, bool at_end);
};

class ObjectIDObjectIDOverflowShim
{
public:
	void insert_overflow(pair<ObjectID, ObjectID> *pos, pair<ObjectID, ObjectID> const &x, const __false_type &tag, unsigned int n, bool at_end);
};

class ObjectIDOverflowShim
{
public:
	void insert_overflow(ObjectID *pos, ObjectID const &x, const __false_type &tag, unsigned int n, bool at_end);
};

vector<pair<ObjectID, unsigned int>, allocator<pair<ObjectID, unsigned int> > > &vector<pair<ObjectID, unsigned int>, allocator<pair<ObjectID, unsigned int> > >::operator=(const vector<pair<ObjectID, unsigned int>, allocator<pair<ObjectID, unsigned int> > > &rhs)
{
	return ((ObjectIDPairVectorAssignShim *)this)->assign(rhs);
}

void vector<pair<ObjectID, unsigned int>, allocator<pair<ObjectID, unsigned int> > >::_M_insert_overflow(pair<ObjectID, unsigned int> *pos, pair<ObjectID, unsigned int> const &x, const __false_type &tag, unsigned int n, bool at_end)
{
	((ObjectIDPairOverflowShim *)this)->insert_overflow(pos, x, tag, n, at_end);
}

void vector<pair<ObjectID, ObjectID>, allocator<pair<ObjectID, ObjectID> > >::_M_insert_overflow(pair<ObjectID, ObjectID> *pos, pair<ObjectID, ObjectID> const &x, const __false_type &tag, unsigned int n, bool at_end)
{
	((ObjectIDObjectIDOverflowShim *)this)->insert_overflow(pos, x, tag, n, at_end);
}

void vector<ObjectID, allocator<ObjectID> >::_M_insert_overflow(ObjectID *pos, ObjectID const &x, const __false_type &tag, unsigned int n, bool at_end)
{
	((ObjectIDOverflowShim *)this)->insert_overflow(pos, x, tag, n, at_end);
}
}
