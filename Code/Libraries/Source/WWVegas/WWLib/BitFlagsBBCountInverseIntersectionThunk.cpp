template <int Bits>
class BitFlags
{
public:
	int countInverseIntersection(const BitFlags &) const;
};

template <int Bits>
__declspec(naked) int BitFlags<Bits>::countInverseIntersection(const BitFlags<Bits> &) const
{
	__asm {
		_emit 0E9h
		_emit 0B0h
		_emit 042h
		_emit 075h
		_emit 000h
	}
}

template int BitFlags<17>::countInverseIntersection(const BitFlags<17> &) const;
