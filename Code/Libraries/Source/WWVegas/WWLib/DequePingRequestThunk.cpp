class PingRequest
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

class DequePingRequestThunkShim
{
public:
	void push_back_aux(void const *x);
};

template <class Type, class Allocator>
void deque<Type, Allocator>::_M_push_back_aux_v(Type const &x)
{
	((DequePingRequestThunkShim *)this)->push_back_aux((void const *)&x);
}
template void deque<PingRequest, allocator<PingRequest> >::_M_push_back_aux_v(PingRequest const &);
}
