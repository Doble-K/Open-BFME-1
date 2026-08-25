// cl: /DNDEBUG /MD /EHs-c-

// Open-BFME5: eighteen scalar deleting destructors from the DirtySock slice,
// in two shapes.
//
// `??_G` is not written, it is GENERATED: MSVC emits one per class with a
// virtual destructor, and it is the function the vtable's destructor slot
// actually points at.  Its body is always the same three steps -- run the
// destructor, test bit 0 of the hidden flag argument, free only if it is set
// -- and the `push <SIZE> / push this / call / add esp,8` says the class
// declares the C++98 MEMBER `operator delete(void *, size_t)`, because the
// global one-argument form takes no size.  The size in the instruction stream
// IS the class's size, which is where each `m_bfmePad` below comes from.
//
// SHAPE ONE (nine bodies) calls a destructor out of line and nothing else, so
// the class's own destructor is out of line; each has its own.
//
// SHAPE TWO (nine bodies) stores a vptr and then calls a SHARED destructor at
// 0x007EB6C0.  That is a derived class whose own destructor is INLINE and
// empty: what survives inlining is the vptr restore the compiler emits at the
// head of every destructor, followed by the base's.  Eight of the nine are
// 0xC bytes and one is 0x70, but all nine share the base, so the base is one
// class and only the vtables tell them apart.
//
// GETTING MSVC TO EMIT `??_G` AT ALL takes a defined constructor: the vtable
// is emitted only where something instantiates the class, and `??_G` rides
// along with it.  Declaring the destructor is not enough, and neither is an
// extra inline virtual -- both were tried and emit nothing.  Those eighteen
// constructors are the price of the recipe; retail has them somewhere and
// this file does not know where, so each is marked present-unmatched rather
// than claimed.
//
// IDENTITY IS NOT RECOVERED.  Classes are named for their `??_G` address, the
// padding carries the size the delete call names, and the shared base is
// named for its destructor.

struct BfmeDirtyBase
{
	BfmeDirtyBase();
	virtual ~BfmeDirtyBase();		// retail 0x007EB6C0
};

// This constructor forces MSVC to emit the base's vtable and its generated
// scalar deleting destructor; the retail scalar body at 0x007E9060 calls the
// shared base destructor at 0x007EB6C0 and the global operator delete.
// ??0BfmeDirtyBase@@QAE@XZ present-unmatched
BfmeDirtyBase::BfmeDirtyBase() {}

void force_BfmeDirtyBase_scalar()
{
	BfmeDirtyBase value;
}

struct Gen007E9B10 : BfmeDirtyBase
{
	Gen007E9B10();
	virtual ~Gen007E9B10() {}
	void operator delete( void *p, unsigned int n );

	char m_bfmePad[ 0xC - 4 ];
};

// ??0Gen007E9B10@@QAE@XZ present-unmatched   emitted only to force the vtable, and with it ??_G
Gen007E9B10::Gen007E9B10() {}

struct Gen007EB140
{
	Gen007EB140();
	virtual ~Gen007EB140();		// retail 0x007EA6F0
	void operator delete( void *p, unsigned int n );

	char m_bfmePad[ 0x2B0 - 4 ];
};

// ??0Gen007EB140@@QAE@XZ present-unmatched   emitted only to force the vtable, and with it ??_G
Gen007EB140::Gen007EB140() {}

struct Gen007F1BF0 : BfmeDirtyBase
{
	Gen007F1BF0();
	virtual ~Gen007F1BF0() {}
	void operator delete( void *p, unsigned int n );

	char m_bfmePad[ 0xC - 4 ];
};

// ??0Gen007F1BF0@@QAE@XZ present-unmatched   emitted only to force the vtable, and with it ??_G
Gen007F1BF0::Gen007F1BF0() {}

struct Gen007F2120 : BfmeDirtyBase
{
	Gen007F2120();
	virtual ~Gen007F2120() {}
	void operator delete( void *p, unsigned int n );

	char m_bfmePad[ 0xC - 4 ];
};

// ??0Gen007F2120@@QAE@XZ present-unmatched   emitted only to force the vtable, and with it ??_G
Gen007F2120::Gen007F2120() {}

struct Gen007F2E30 : BfmeDirtyBase
{
	Gen007F2E30();
	virtual ~Gen007F2E30() {}
	void operator delete( void *p, unsigned int n );

	char m_bfmePad[ 0xC - 4 ];
};

// ??0Gen007F2E30@@QAE@XZ present-unmatched   emitted only to force the vtable, and with it ??_G
Gen007F2E30::Gen007F2E30() {}

struct Gen007F33E0 : BfmeDirtyBase
{
	Gen007F33E0();
	virtual ~Gen007F33E0() {}
	void operator delete( void *p, unsigned int n );

	char m_bfmePad[ 0xC - 4 ];
};

// ??0Gen007F33E0@@QAE@XZ present-unmatched   emitted only to force the vtable, and with it ??_G
Gen007F33E0::Gen007F33E0() {}

struct Gen007F40C0 : BfmeDirtyBase
{
	Gen007F40C0();
	virtual ~Gen007F40C0() {}
	void operator delete( void *p, unsigned int n );

	char m_bfmePad[ 0xC - 4 ];
};

// ??0Gen007F40C0@@QAE@XZ present-unmatched   emitted only to force the vtable, and with it ??_G
Gen007F40C0::Gen007F40C0() {}

struct Gen007F47E0 : BfmeDirtyBase
{
	Gen007F47E0();
	virtual ~Gen007F47E0() {}
	void operator delete( void *p, unsigned int n );

	char m_bfmePad[ 0x70 - 4 ];
};

// ??0Gen007F47E0@@QAE@XZ present-unmatched   emitted only to force the vtable, and with it ??_G
Gen007F47E0::Gen007F47E0() {}

struct Gen007F4D00
{
	Gen007F4D00();
	virtual ~Gen007F4D00();		// retail 0x007F4D20
	void operator delete( void *p, unsigned int n );

	char m_bfmePad[ 0x18 - 4 ];
};

// ??0Gen007F4D00@@QAE@XZ present-unmatched   emitted only to force the vtable, and with it ??_G
Gen007F4D00::Gen007F4D00() {}

struct Gen007F86D0
{
	Gen007F86D0();
	virtual ~Gen007F86D0();		// retail 0x007F8090
	void operator delete( void *p, unsigned int n );

	char m_bfmePad[ 0x6E0 - 4 ];
};

// ??0Gen007F86D0@@QAE@XZ present-unmatched   emitted only to force the vtable, and with it ??_G
Gen007F86D0::Gen007F86D0() {}

struct Gen007FA290
{
	Gen007FA290();
	virtual ~Gen007FA290();		// retail 0x007F9C50
	void operator delete( void *p, unsigned int n );

	char m_bfmePad[ 0x6B8 - 4 ];
};

// ??0Gen007FA290@@QAE@XZ present-unmatched   emitted only to force the vtable, and with it ??_G
Gen007FA290::Gen007FA290() {}

struct Gen007FBAF0 : BfmeDirtyBase
{
	Gen007FBAF0();
	virtual ~Gen007FBAF0() {}
	void operator delete( void *p, unsigned int n );

	char m_bfmePad[ 0xC - 4 ];
};

// ??0Gen007FBAF0@@QAE@XZ present-unmatched   emitted only to force the vtable, and with it ??_G
Gen007FBAF0::Gen007FBAF0() {}

struct Gen007FCF50 : BfmeDirtyBase
{
	Gen007FCF50();
	virtual ~Gen007FCF50() {}
	void operator delete( void *p, unsigned int n );

	char m_bfmePad[ 0xC - 4 ];
};

// ??0Gen007FCF50@@QAE@XZ present-unmatched   emitted only to force the vtable, and with it ??_G
Gen007FCF50::Gen007FCF50() {}

struct Gen008030A0
{
	Gen008030A0();
	virtual ~Gen008030A0();		// retail 0x00802F50
	void operator delete( void *p, unsigned int n );

	char m_bfmePad[ 0x14 - 4 ];
};

// ??0Gen008030A0@@QAE@XZ present-unmatched   emitted only to force the vtable, and with it ??_G
Gen008030A0::Gen008030A0() {}

struct Gen00803D10
{
	Gen00803D10();
	virtual ~Gen00803D10();		// retail 0x00803890
	void operator delete( void *p, unsigned int n );

	char m_bfmePad[ 0x1C - 4 ];
};

// ??0Gen00803D10@@QAE@XZ present-unmatched   emitted only to force the vtable, and with it ??_G
Gen00803D10::Gen00803D10() {}

struct Gen00808FB0
{
	Gen00808FB0();
	virtual ~Gen00808FB0();		// retail 0x007E86C0
	void operator delete( void *p, unsigned int n );

	char m_bfmePad[ 0x38 - 4 ];
};

// ??0Gen00808FB0@@QAE@XZ present-unmatched   emitted only to force the vtable, and with it ??_G
Gen00808FB0::Gen00808FB0() {}

struct Gen00809750
{
	Gen00809750();
	virtual ~Gen00809750();		// retail 0x008096F0
	void operator delete( void *p, unsigned int n );

	char m_bfmePad[ 0xB4 - 4 ];
};

// ??0Gen00809750@@QAE@XZ present-unmatched   emitted only to force the vtable, and with it ??_G
Gen00809750::Gen00809750() {}

struct Gen0080ACD0
{
	Gen0080ACD0();
	virtual ~Gen0080ACD0();		// retail 0x0080A830
	void operator delete( void *p, unsigned int n );

	char m_bfmePad[ 0x194 - 4 ];
};

// ??0Gen0080ACD0@@QAE@XZ present-unmatched   emitted only to force the vtable, and with it ??_G
Gen0080ACD0::Gen0080ACD0() {}
