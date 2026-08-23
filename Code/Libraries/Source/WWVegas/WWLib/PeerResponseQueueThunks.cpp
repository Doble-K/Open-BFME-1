class PeerResponse
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
public:
	void pop_front();
};

class PeerResponseDequePopFrontShim
{
public:
	void pop_front();
};

template <class Type, class Allocator>
void deque<Type, Allocator>::pop_front()
{
	((PeerResponseDequePopFrontShim *)this)->pop_front();
}

template void deque<PeerResponse, allocator<PeerResponse> >::pop_front();
}
