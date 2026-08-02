struct ICoord2D
{
};

struct Coord3D
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

struct __false_type
{
};

template <class Type, class Allocator>
class vector
{
protected:
	void _M_insert_overflow(Type *, const Type &, const __false_type &, unsigned int, bool);
};

class Coord2DCoord3DPairInsertOverflowShim
{
public:
	void insert_overflow(pair<ICoord2D, Coord3D> *pos, const pair<ICoord2D, Coord3D> &x, const __false_type &tag, unsigned int fill_len, bool at_end);
};

void vector<pair<ICoord2D, Coord3D>, allocator<pair<ICoord2D, Coord3D> > >::_M_insert_overflow(
	pair<ICoord2D, Coord3D> *pos, const pair<ICoord2D, Coord3D> &x, const __false_type &tag, unsigned int fill_len, bool at_end)
{
	((Coord2DCoord3DPairInsertOverflowShim *)this)->insert_overflow(pos, x, tag, fill_len, at_end);
}
}
