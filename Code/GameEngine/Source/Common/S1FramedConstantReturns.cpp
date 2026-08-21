// cl: /Od /Gy
// Five adjacent functions at 0x0082B050..0x0082B0D0, sixteen bytes apart, whose
// entire body is a constant return WITH a frame pointer:
//
//     push ebp / mov ebp,esp / mov eax,<K> / pop ebp / ret
//
// WHAT THE BYTES SHOW.  The frame is the evidence.  Nothing in these functions
// touches the stack, so /O2 -- which is what the rest of this project's sources
// compile under, and which implies /Oy -- emits `mov eax,<K> / ret` and nothing
// else.  Adding /Oy- to /O2 does NOT bring the frame back for a body with no
// stack usage; only turning optimisation OFF does.  So the flag directive above
// is not a convenience, it is the finding: THIS TRANSLATION UNIT WAS BUILT
// UNOPTIMISED, and that is why five one-line functions occupy ten bytes each
// and sit on a 16-byte grid instead of being folded.
//
// The constants alternate 8, 16, 8, 16, 8 and are read straight off the
// immediates.
//
// IDENTITY IS NOT RECOVERED, and here the bytes are unusually quiet: with no
// argument, no ecx use and a bare `ret`, a free function, a __stdcall function
// and a __thiscall member all encode identically.  These are spelled as free
// functions because that is the spelling that asserts the least -- it claims no
// owning class.  The alternating values and the even spacing look like a size
// or stride query answered per subtype, but that is a reading of the pattern,
// not of the bytes.

int Rva0082B050();
int Rva0082B050()
{
	return 8;
}

int Rva0082B080();
int Rva0082B080()
{
	return 16;
}

int Rva0082B090();
int Rva0082B090()
{
	return 8;
}

int Rva0082B0C0();
int Rva0082B0C0()
{
	return 16;
}

int Rva0082B0D0();
int Rva0082B0D0()
{
	return 8;
}
