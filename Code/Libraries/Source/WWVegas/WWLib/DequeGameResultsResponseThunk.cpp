class GameResultsResponse
{
};

namespace _STL
{
template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class deque
{
protected:
	void _M_push_back_aux_v(Type const &);
};

class DequeGameResultsResponseThunkShim
{
public:
	void push_back_aux(void const *x);
};

template <class Type, class Allocator>
void deque<Type, Allocator>::_M_push_back_aux_v(Type const &x)
{
	((DequeGameResultsResponseThunkShim *)this)->push_back_aux((void const *)&x);
}
template void deque<GameResultsResponse, allocator<GameResultsResponse> >::_M_push_back_aux_v(GameResultsResponse const &);
}
