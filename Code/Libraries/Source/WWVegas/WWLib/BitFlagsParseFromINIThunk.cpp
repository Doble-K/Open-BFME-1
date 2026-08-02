class INI;

template <int Bits>
class BitFlags
{
public:
	static void parseFromINI(INI *, void *, void *, const void *);
};

class BitFlags45ParseFromINIShim
{
public:
	static void parseFromINI(INI *, void *, void *, const void *);
};

class BitFlags116ParseFromINIShim
{
public:
	static void parseFromINI(INI *, void *, void *, const void *);
};

template <int Bits>
void BitFlags<Bits>::parseFromINI(INI *ini, void *a, void *b, const void *c)
{
	BitFlags45ParseFromINIShim::parseFromINI(ini, a, b, c);
}

template void BitFlags<45>::parseFromINI(INI *, void *, void *, const void *);

template <>
class BitFlags<116>
{
public:
	static void parseFromINI(INI *, void *, void *, const void *);
};

void BitFlags<116>::parseFromINI(INI *ini, void *a, void *b, const void *c)
{
	BitFlags116ParseFromINIShim::parseFromINI(ini, a, b, c);
}
