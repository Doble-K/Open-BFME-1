// cl: /DNDEBUG /MD /EHsc

// The 28-byte body at retail 0x00844520. IDENTITY IS NOT RECOVERED -- both the
// name and the returned class carry address-derived placeholders, because the
// symbol this used to be pinned as cannot be right:
//
//   ??$__default_constructed_aux@VMultiplayerColorDefinition@@@_STL@@YA?AV...
//
// is __cdecl (YA), and retail ends in `ret 4`. Every matched __cdecl body in
// this image that returns a class by value -- forty-odd of them, AsciiString
// and UnicodeString and the STL iterator structs included -- ends in a plain
// `ret`, so MSVC 7.1 never makes __cdecl pop the hidden return pointer. A
// callee-cleaned four is therefore a *convention* fact: no declared parameters,
// and the only stack item popped is the hidden pointer. That is what __stdcall
// gives, and it reproduces every byte.
//
// The class actually constructed is not MultiplayerColorDefinition either: the
// call goes through ILT 0x0004048A to 0x004D4F40, which is already matched as
// _STL::basic_string<char>'s default constructor.
//
// One construct is reproduced rather than understood: the four-byte stack local
// that retail allocates with `push ecx` and clears with `mov [esp+4],0` and
// never reads. It survives /O2 only when spelled volatile -- a plain local, a
// zero-initialised array, an address-taken pointer and an empty-class temporary
// bound to a const reference are all eliminated. Whatever the original was, it
// left a kept dead store; that is what the volatile stands in for.

class Rva4048AString
{
public:
	Rva4048AString( void );

private:
	void *m_start;
	void *m_finish;
	void *m_endOfStorage;
	void *m_alloc;
};

// ?rva844520@@YG?AVRva4048AString@@XZ
Rva4048AString __stdcall rva844520( void )
{
	volatile int unused = 0;

	return Rva4048AString();
}
