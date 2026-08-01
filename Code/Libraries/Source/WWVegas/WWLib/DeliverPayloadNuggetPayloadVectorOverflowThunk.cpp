struct DeliverPayloadNugget
{
	struct Payload
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

	__declspec(naked) void vector<DeliverPayloadNugget::Payload, allocator<DeliverPayloadNugget::Payload> >::_M_insert_overflow(
		DeliverPayloadNugget::Payload *, const DeliverPayloadNugget::Payload &, const __false_type &, unsigned int, bool)
	{
		__asm {
			_emit 0E9h
			_emit 028h
			_emit 0CAh
			_emit 076h
			_emit 000h
		}
	}
}
