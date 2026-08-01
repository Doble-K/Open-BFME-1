class PSRequest
{
};

class PeerRequest
{
};

namespace _STL
{
	template<class Type>
	class allocator
	{
	};

	template<class Type, class Allocator>
	class deque
	{
	public:
		void pop_front();
	};

	template<class Type, class Allocator>
	__declspec(naked) void deque<Type, Allocator>::pop_front()
	{
		__asm {
			_emit 0E9h
			_emit 06Fh
			_emit 0AFh
			_emit 061h
			_emit 000h
		}
	}

	template __declspec(naked) void deque<PSRequest, allocator<PSRequest> >::pop_front();
	template __declspec(naked) void deque<PeerRequest, allocator<PeerRequest> >::pop_front();
}
