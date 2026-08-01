class PingRequest
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
			_emit 0A8h
			_emit 010h
			_emit 063h
			_emit 000h
		}
	}
	template __declspec(naked) void deque<PingRequest, allocator<PingRequest> >::_M_push_back_aux_v(PingRequest const &);
}
