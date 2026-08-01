class PingResponse
{
};

namespace _STL
{
	template <class Type> class allocator { };
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
			_emit 02Bh
			_emit 042h
			_emit 062h
			_emit 000h
		}
	}
	template __declspec(naked) void deque<PingResponse, allocator<PingResponse> >::_M_push_back_aux_v(PingResponse const &);
}
