class PSRequest
{
};

class PeerRequest
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

class DequePopFrontShim
{
public:
	void pop_front();
};

template <class Type, class Allocator>
void deque<Type, Allocator>::pop_front()
{
	((DequePopFrontShim *)this)->pop_front();
}

template void deque<PSRequest, allocator<PSRequest> >::pop_front();
template void deque<PeerRequest, allocator<PeerRequest> >::pop_front();
}
