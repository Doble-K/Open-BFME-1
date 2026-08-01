class GameResultsRequest
{
};

class GameResultsResponse
{
};

class PingRequest
{
};

class PingResponse
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
	protected:
		void _M_push_back_aux_v(Type const &);
	};

	template<class Type, class Allocator>
	__declspec(naked) void deque<Type, Allocator>::_M_push_back_aux_v(Type const &)
	{
		__asm {
			_emit 0E9h
			_emit 05Dh
			_emit 0FFh
			_emit 061h
			_emit 000h
		}
	}

	template __declspec(naked) void deque<GameResultsRequest, allocator<GameResultsRequest> >::_M_push_back_aux_v(const GameResultsRequest &);

}
