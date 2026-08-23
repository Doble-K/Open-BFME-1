// cl: /DNDEBUG /MD /EHsc
// Open-BFME: BitFlags<116>::parseFromINI, retail 0x00129810, 73 bytes. The
// name was parked on a 5-byte thunk.
//
// The reference's parseFromINI is one line -- it forwards to parse -- and here
// the forwarding is gone: what is left is parse's token loop with its body
// hoisted into a single call. Each turn hands the token and the addresses of
// the two "found" flags to the 459-byte routine at 0x00128510, reached through
// the ILT at 0x0003D3B1, and stops when it returns false.
//
// That routine has no identity yet, so it is declared here the way this tree
// declares other address-anchored callees: as a member of a class named after
// its address, reached by casting the store.

typedef int Int;
typedef bool Bool;

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps = 0);	// retail 0x008509C0
};

// The per-instantiation routine whose `this` is the BitFlags being filled in:
// 0x00128510 for the 116-bit flags, 0x00204770 for the 45-bit ones.
class Rva00128510BitFlagsParser
{
public:
	Bool parseToken(const char *token, Bool *foundNormal, Bool *foundAddOrSub);
};

class Rva00204770BitFlagsParser
{
public:
	Bool parseToken(const char *token, Bool *foundNormal, Bool *foundAddOrSub);
};

template <int NUMBITS>
class BitFlags
{
public:
	static void parseFromINI(INI *ini, void *instance, void *store, const void *userData);

private:
	unsigned int m_bits[(NUMBITS + 31) / 32];
};

template <>
void BitFlags<116>::parseFromINI(INI *ini, void *instance, void *store, const void *userData)
{
	Bool foundNormal = false;
	Bool foundAddOrSub = false;

	for (const char *token = ini->getNextTokenOrNull(); token != 0; token = ini->getNextTokenOrNull())
	{
		if (!((Rva00128510BitFlagsParser *)store)->parseToken(token, &foundNormal, &foundAddOrSub))
			break;
	}
}

template <>
void BitFlags<45>::parseFromINI(INI *ini, void *instance, void *store, const void *userData)
{
	Bool foundNormal = false;
	Bool foundAddOrSub = false;

	for (const char *token = ini->getNextTokenOrNull(); token != 0; token = ini->getNextTokenOrNull())
	{
		if (!((Rva00204770BitFlagsParser *)store)->parseToken(token, &foundNormal, &foundAddOrSub))
			break;
	}
}
