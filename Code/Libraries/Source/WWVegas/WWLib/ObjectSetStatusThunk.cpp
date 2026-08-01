template <int Bits>
class BitFlags
{
};

class Object
{
public:
	void setStatus(BitFlags<45>, bool);
};

__declspec(naked) void Object::setStatus(BitFlags<45>, bool)
{
	__asm {
		_emit 0E9h
		_emit 0FCh
		_emit 06Dh
		_emit 018h
		_emit 000h
	}
}
