// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// The packet CRC, 0x00065250, 42 bytes.
//
// Same accumulation the engine's CRC class uses -- rotate the running value left
// by one and add the byte -- but as a free function taking and returning the
// running value rather than as a method on a CRC object, which is why it has no
// counterpart in the reference. The name is this tree's; retail carries no
// symbol for it.
//
// It is one of the two things 0x00683830 does to a packet, the other being the
// rolling-XOR pass at 0x006832C0.

typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

// Everything outside the loop body is retail's exactly -- the null guard, the
// zero-length guard, the register assignment, the epilogue. Inside it, retail
// computes (crc*2 + byte) and then adds the carried-out high bit, while MSVC
// folds byte + hibit first and adds crc*2 last. That reassociation is legal for
// unsigned arithmetic and survives writing the two adds as separate statements,
// as one left-associative expression, and with the shift split out.
// ?BFMEComputeCRC@@YAIPBEII@Z present-unmatched
UnsignedInt BFMEComputeCRC(const UnsignedByte *data, UnsignedInt length, UnsignedInt crc)
{
	if (data != 0) {
		while (length > 0) {
			UnsignedInt val = *data;
			UnsignedInt hibit = crc >> 31;
			crc = (crc << 1) + val;
			++data;
			crc = crc + hibit;
			--length;
		}
	}

	return crc;
}
