class INI;

template<int Bits>
class BitFlags
{
public:
	static void parseFromINI(INI *, void *, void *, const void *);
};

template<int Bits>
__declspec(naked) void BitFlags<Bits>::parseFromINI(INI *, void *, void *, const void *)
{
	__asm {
		_emit 0E9h
		_emit 0D1h
		_emit 0B2h
		_emit 01Dh
		_emit 000h
	}
}

template __declspec(naked) void BitFlags<45>::parseFromINI(INI *, void *, void *, const void *);

template<>
class BitFlags<116>
{
public:
	static void parseFromINI(INI *, void *, void *, const void *);
};

__declspec(naked) void BitFlags<116>::parseFromINI(INI *, void *, void *, const void *)
{
	__asm {
		_emit 0E9h
		_emit 0DDh
		_emit 094h
		_emit 010h
		_emit 000h
	}
}
