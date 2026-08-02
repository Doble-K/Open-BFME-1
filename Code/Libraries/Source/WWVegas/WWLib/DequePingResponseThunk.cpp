class PingResponse
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

class DequePingResponseThunkShim
{
public:
	void push_back_aux(void const *x);
};

template <class Type, class Allocator>
void deque<Type, Allocator>::_M_push_back_aux_v(Type const &x)
{
	((DequePingResponseThunkShim *)this)->push_back_aux((void const *)&x);
}
template void deque<PingResponse, allocator<PingResponse> >::_M_push_back_aux_v(PingResponse const &);
}
