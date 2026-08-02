struct State
{
	struct TransitionInfo
	{
	};
};

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
protected:
	void _M_insert_overflow(Type *, const Type &, const __false_type &, unsigned int, bool);
};

class StateTransitionInfoInsertOverflowShim
{
public:
	void insert_overflow(State::TransitionInfo *pos, const State::TransitionInfo &x, const __false_type &tag, unsigned int fill_len, bool at_end);
};

void vector<State::TransitionInfo, allocator<State::TransitionInfo> >::_M_insert_overflow(
	State::TransitionInfo *pos, const State::TransitionInfo &x, const __false_type &tag, unsigned int fill_len, bool at_end)
{
	((StateTransitionInfoInsertOverflowShim *)this)->insert_overflow(pos, x, tag, fill_len, at_end);
}
}
