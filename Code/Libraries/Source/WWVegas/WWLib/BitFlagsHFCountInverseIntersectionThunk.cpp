template<int Bits>
class BitFlags
{
public:
	int countInverseIntersection(const BitFlags<Bits> &) const;
};

template<int Bits>
__declspec(naked) int BitFlags<Bits>::countInverseIntersection(const BitFlags<Bits> &) const
{
	__asm {
		_emit 0E9h
		_emit 0B8h
		_emit 0DFh
		_emit 041h
		_emit 000h
	}
}

template __declspec(naked) int BitFlags<117>::countInverseIntersection(const BitFlags<117> &) const;
