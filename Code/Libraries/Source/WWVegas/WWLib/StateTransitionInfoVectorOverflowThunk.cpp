struct State
{
	struct TransitionInfo
	{
	};
};

namespace _STL
{
	struct __false_type
	{
	};

	template <class Type>
	class allocator
	{
	};

	template <class Type, class Allocator>
	class vector
	{
	protected:
		void _M_insert_overflow(Type *, const Type &, const __false_type &, unsigned int, bool);
	};

	__declspec(naked) void vector<State::TransitionInfo, allocator<State::TransitionInfo> >::_M_insert_overflow(
		State::TransitionInfo *, const State::TransitionInfo &, const __false_type &, unsigned int, bool)
	{
		__asm {
			_emit 0E9h
			_emit 043h
			_emit 021h
			_emit 020h
			_emit 000h
		}
	}
}
