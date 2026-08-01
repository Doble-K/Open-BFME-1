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

	template <class Type, class Allocator>
	__declspec(naked) void deque<Type, Allocator>::pop_front()
	{
		__asm {
			_emit 0E9h
			_emit 097h
			_emit 0E3h
			_emit 061h
			_emit 000h
		}
	}

	template <class Type, class Container>
	class queue
	{
	public:
		void push(Type const &);
	};

	template <class Type, class Container>
	__declspec(naked) void queue<Type, Container>::push(Type const &)
	{
		__asm {
			_emit 0E9h
			_emit 024h
			_emit 0FDh
			_emit 060h
			_emit 000h
		}
	}

	template __declspec(naked) void deque<PeerResponse, allocator<PeerResponse> >::pop_front();
	template __declspec(naked) void queue<PeerResponse, deque<PeerResponse, allocator<PeerResponse> > >::push(PeerResponse const &);
}
