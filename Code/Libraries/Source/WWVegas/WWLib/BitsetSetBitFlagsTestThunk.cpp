namespace _STL
{
	template<int Bits>
	class bitset
	{
	public:
		bitset<Bits> & set(unsigned int, int);
	};

	template<int Bits>
	__declspec(naked) bitset<Bits> & bitset<Bits>::set(unsigned int, int)
	{
		__asm {
			_emit 0E9h
			_emit 03Eh
			_emit 0FDh
			_emit 00Ch
			_emit 000h
		}
	}

	template __declspec(naked) bitset<67> & bitset<67>::set(unsigned int, int);
}

template<int Bits>
class BitFlags
{
public:
	bool testSetAndClear(const BitFlags<Bits> &, const BitFlags<Bits> &) const;
};

template<int Bits>
__declspec(naked) bool BitFlags<Bits>::testSetAndClear(const BitFlags<Bits> &, const BitFlags<Bits> &) const
{
	__asm {
		_emit 0E9h
		_emit 03Eh
		_emit 0FDh
		_emit 00Ch
		_emit 000h
	}
}

template __declspec(naked) bool BitFlags<116>::testSetAndClear(const BitFlags<116> &, const BitFlags<116> &) const;
