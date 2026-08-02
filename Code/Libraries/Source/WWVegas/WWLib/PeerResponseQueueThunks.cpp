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

template <class Type, class Container>
class queue
{
public:
	void push(Type const &);
};

class PeerResponseDequePopFrontShim
{
public:
	void pop_front();
};

class PeerResponseQueuePushShim
{
public:
	void push(void const *x);
};

template <class Type, class Allocator>
void deque<Type, Allocator>::pop_front()
{
	((PeerResponseDequePopFrontShim *)this)->pop_front();
}

template <class Type, class Container>
void queue<Type, Container>::push(Type const &x)
{
	((PeerResponseQueuePushShim *)this)->push((void const *)&x);
}

template void deque<PeerResponse, allocator<PeerResponse> >::pop_front();
template void queue<PeerResponse, deque<PeerResponse, allocator<PeerResponse> > >::push(PeerResponse const &);
}
