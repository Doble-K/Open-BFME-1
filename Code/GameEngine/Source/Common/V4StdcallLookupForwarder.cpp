// One 29-byte __stdcall free function: look one object up by its first argument
// and, when the lookup answers something, pass the second argument to it.
//
//     mov eax,[esp+4] / push eax / call <lookup>
//     test eax,eax / je .out
//     mov ecx,[esp+8] / push ecx / mov ecx,eax / call <set>
//   .out: ret 8
//
// WHAT THE BYTES SHOW.  The incoming ecx is never read and is overwritten before
// the second call, so nothing arrives in a register: this is a free function,
// and `ret 8` gives it exactly two dword stack arguments.  The lookup's argument
// is pushed and NOT cleaned up by this function, so the lookup is __stdcall too;
// the second call loads its receiver from eax -- the lookup's own result -- so it
// is a __thiscall member of whatever came back.  The second argument is moved as
// a DWORD, so it is a dword-sized type, not a narrower one widened for the push.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the callee
// pins are address-derived and additive.

class Gen003C0110Result
{
public:
	void set( int value );
	void apply( int a, int b, int c, int d, int e );
	char m_pad00[ 0x1F ];
	bool m_at1F;
};

Gen003C0110Result * __stdcall Gen003C0110Lookup( void * key );

void __stdcall Rva003C0220( void * key, int value )
{
	Gen003C0110Result *found = Gen003C0110Lookup( key );
	if( found )
		found->set( value );
}

// ------------------------------------------------------- same lookup, six args
// 0x003C0250 opens with the same `mov eax,[esp+4] / push eax / call` into the
// same lookup and, like the row above, does nothing when it answers null -- but
// it answers a BOOL rather than nothing, and `ret 0x18` gives it six dword
// arguments.  Five of them are forwarded to a __thiscall member of the result
// alongside a literal zero; the sixth is tested as a BYTE (`mov cl,[esp+0x10]`)
// and only decides whether a flag at +0x1F of the result is set.  `mov al,1` is
// hoisted ABOVE that branch, so the true result is shared by both paths: the
// function answers true whenever the lookup found anything.

bool __stdcall Rva003C0250( void * key, int a, bool flag, int b, int c, int d )
{
	Gen003C0110Result *found = Gen003C0110Lookup( key );
	if( !found )
		return false;
	found->apply( a, b, c, 0, d );
	if( flag )
		found->m_at1F = true;
	return true;
}
