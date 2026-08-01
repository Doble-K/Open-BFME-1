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

	template <class Type, class Allocator>
	__declspec(naked) void deque<Type, Allocator>::_M_push_back_aux_v(Type const &)
	{
		__asm {
			_emit 0E9h
			_emit 01Ah
			_emit 081h
			_emit 05Fh
			_emit 000h
		}
	}

	template __declspec(naked) void deque<GameResultsResponse, allocator<GameResultsResponse> >::_M_push_back_aux_v(GameResultsResponse const &);
}
