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

class FlightDeckBehaviorFlightDeckInfoInsertOverflowShim
{
public:
	void insert_overflow(FlightDeckBehavior::FlightDeckInfo *pos, const FlightDeckBehavior::FlightDeckInfo &x, const __false_type &tag, unsigned int fill_len, bool at_end);
};

void vector<FlightDeckBehavior::FlightDeckInfo, allocator<FlightDeckBehavior::FlightDeckInfo> >::_M_insert_overflow(
	FlightDeckBehavior::FlightDeckInfo *pos, const FlightDeckBehavior::FlightDeckInfo &x, const __false_type &tag, unsigned int fill_len, bool at_end)
{
	((FlightDeckBehaviorFlightDeckInfoInsertOverflowShim *)this)->insert_overflow(pos, x, tag, fill_len, at_end);
}
}
