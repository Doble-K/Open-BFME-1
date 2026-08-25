// ?Gen_003fe1e0@@YGHMM@Z
// partial score=0.8 date=2026-08-25
// Retail 0x003FE1E0, 79 bytes, which the ledger had in three pieces: the
// computation, an eight-byte return-one arm claimed as an alias, and a
// byte-dump row for the upper clamp.
//
// The two arguments and two memory constants multiply in the order the flds
// give -- second, constant, first, constant -- and the product is stored as a
// QWORD before the call, so the callee takes a double. What comes back is
// stored as a dword, so it is assigned to a float before the conversion.
//
// The conversion is fistp into a stack slot and a reload, which is what an
// int cast of a float costs; the clamps then compare against 1 and 0x80 and
// return those literals rather than the value.
//
// The callee is reached with call dword ptr [address] -- an import-table
// indirection, which only a __declspec(dllimport) declaration produces. Which
// import it is the bytes do not say: the address rides a DIR32 relocation
// copied from retail, so any dllimport with this signature reproduces them.

typedef float Real;

extern const Real TheBfmeCountScaleA;					// 0x010CDFF4
extern const Real TheBfmeCountScaleB;					// 0x010F02F4

extern "C" __declspec(dllimport) double __cdecl BfmeScaledCountImport(double value);

// ?Gen_003fe1e0@@YGHMM@Z
int __stdcall Gen_003fe1e0(Real first, Real second)
{
	Real scaled = (Real)BfmeScaledCountImport(second * TheBfmeCountScaleA * first * TheBfmeCountScaleB);

	int count = (int)scaled;

	if (count < 1)
		return 1;

	if (count > 0x80)
		return 0x80;

	return count;
}
