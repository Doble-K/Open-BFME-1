struct FlightDeckBehavior
{
	struct FlightDeckInfo
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

	__declspec(naked) void vector<FlightDeckBehavior::FlightDeckInfo, allocator<FlightDeckBehavior::FlightDeckInfo> >::_M_insert_overflow(
		FlightDeckBehavior::FlightDeckInfo *, const FlightDeckBehavior::FlightDeckInfo &, const __false_type &, unsigned int, bool)
	{
		__asm {
			_emit 0E9h
			_emit 081h
			_emit 075h
			_emit 022h
			_emit 000h
		}
	}
}
