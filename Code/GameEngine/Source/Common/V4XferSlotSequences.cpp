// Four __thiscall members that take ONE pointer argument and do nothing but call
// a run of VIRTUAL slots on it, each time handing it the address of a member of
// this object:
//
//     mov esi,[esp+8] / mov eax,[esi] / mov edi,ecx
//     lea ecx,[edi+4] / push ecx / mov ecx,esi / call [eax+0x74]
//     mov edx,[esi] / lea eax,[edi+8] / push eax / mov ecx,esi
//     call [edx+0x8C] / ...
//
// WHAT THE BYTES SHOW.  The argument is reloaded into ecx before every call and
// its vftable is re-read from [esi] before every call, so each call is a virtual
// __thiscall on the SAME receiver -- the argument -- and the compiler could not
// prove the vptr survives, which is what a call through an opaque interface
// looks like.  What is pushed is always `lea` of an interior address, never a
// value: these are OUT/IN-OUT parameters, one member of this object per call.
//
// THE SLOT NUMBERS ARE OPERANDS, not inference: 0x74, 0x8C, 0x68, 0x60 and 0x6C
// appear literally in the `call [reg+K]` displacements, so the receiver's class
// is declared with 36 virtual functions purely to place those five at those
// displacements.  All four rows open with the same two calls -- slot 0x74 on the
// member at +4 and slot 0x8C on the member at +8 -- and then diverge; none of
// them calls another of them, so they are four separate classes that happen to
// share a two-field prefix, not a base and three overrides.
//
// TWO ROWS LEAVE THE INTERFACE for one step.  0x003BB8F0 pushes the member
// address AND the interface pointer and cleans up eight bytes itself, so that
// one is a __cdecl free function taking both; 0x003BBA40 sets ecx to a member
// address and pushes the interface, so that one is a __thiscall member of the
// member at +0xC.  Both then continue on the interface.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the two
// non-virtual callee pins are address-derived and additive.

class GenXferInterface
{
public:
	virtual void slot00( void * field );
	virtual void slot04( void * field );
	virtual void slot08( void * field );
	virtual void slot0C( void * field );
	virtual void slot10( void * field );
	virtual void slot14( void * field );
	virtual void slot18( void * field );
	virtual void slot1C( void * field );
	virtual void slot20( void * field );
	virtual void slot24( void * field );
	virtual void slot28( void * field );
	virtual void slot2C( void * field );
	virtual void slot30( void * field );
	virtual void slot34( void * field );
	virtual void slot38( void * field );
	virtual void slot3C( void * field );
	virtual void slot40( void * field );
	virtual void slot44( void * field );
	virtual void slot48( void * field );
	virtual void slot4C( void * field );
	virtual void slot50( void * field );
	virtual void slot54( void * field );
	virtual void slot58( void * field );
	virtual void slot5C( void * field );
	virtual void slot60( void * field );
	virtual void slot64( void * field );
	virtual void slot68( void * field );
	virtual void slot6C( void * field );
	virtual void slot70( void * field );
	virtual void slot74( void * field );
	virtual void slot78( void * field );
	virtual void slot7C( void * field );
	virtual void slot80( void * field );
	virtual void slot84( void * field );
	virtual void slot88( void * field );
	virtual void slot8C( void * field );
};

class Gen003BB8F0Member;
class Gen003BBA40Member
{
public:
	void step( GenXferInterface * xfer );
};

void Gen003BB8F0Free( GenXferInterface * xfer, void * field );

class Rva003BB8F0
{
public:
	void xfer( GenXferInterface * x );
	char m_pad00[ 0x4 ];
	int  m_at04;
	int  m_at08;
	int  m_at0C;
};
void Rva003BB8F0::xfer( GenXferInterface * x )
{
	x->slot74( &m_at04 );
	x->slot8C( &m_at08 );
	Gen003BB8F0Free( x, &m_at0C );
}

class Rva003BB930
{
public:
	void xfer( GenXferInterface * x );
	char m_pad00[ 0x4 ];
	int  m_at04;
	int  m_at08;
	int  m_at0C;
};
void Rva003BB930::xfer( GenXferInterface * x )
{
	x->slot74( &m_at04 );
	x->slot8C( &m_at08 );
	x->slot68( &m_at0C );
}

class Rva003BBA40
{
public:
	void xfer( GenXferInterface * x );
	char m_pad00[ 0x4 ];
	int  m_at04;
	int  m_at08;
	char m_pad0C[ 0xC ];
	int  m_at18;
};
void Rva003BBA40::xfer( GenXferInterface * x )
{
	x->slot74( &m_at04 );
	x->slot8C( &m_at08 );
	( (Gen003BBA40Member *)( (char *)this + 0xC ) )->step( x );
	x->slot74( &m_at18 );
}

class Rva003BB9A0
{
public:
	void xfer( GenXferInterface * x );
	char m_pad00[ 0x4 ];
	int  m_at04;
	int  m_at08;
	int  m_at0C;
	char m_pad10[ 0x8 ];
	int  m_at18;
	int  m_at1C;
};
void Rva003BB9A0::xfer( GenXferInterface * x )
{
	x->slot74( &m_at04 );
	x->slot8C( &m_at08 );
	x->slot60( &m_at0C );
	x->slot6C( &m_at18 );
	x->slot74( &m_at1C );
}

