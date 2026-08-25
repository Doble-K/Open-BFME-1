// cl: /Od

// Open-BFME5: nine /Od destructors at 0x0082AE60..0x0082AF60, one every 0x20
// bytes -- and they are not nine siblings, they are a THREE-LEVEL CHAIN.
//
// Each body stores its own vtable and then calls one destructor with `this`.
// Reading the call targets back against the addresses of the bodies shows
// four of the nine calling bodies that are themselves in this set:
//
//     0x0082AE40 (outside this file, the root)
//       +- 0x0082AE60  <- called by AEA0, AEC0, AEE0, AF00
//       +- 0x0082AE80  <- called by AF20, AF40, AF60
//
// So the file has to be written as a hierarchy, not as nine independent
// classes: the four mid-level calls resolve to rows landed in this same TU,
// and only the root's destructor is pinned from outside.
//
// The vptr store at the head of each is what says the destructor is VIRTUAL --
// a non-virtual one has no vptr to restore -- and the bare `ret` says it is
// the plain destructor and not the scalar deleting form, which would carry a
// flag argument and `ret 4`.
//
// `/Od` is the whole flag list: `this` is spilled to [ebp-4] and re-read for
// every use, which is what puts three separate loads of the same value in
// twenty-eight bytes.  There are no /GZ guard bytes, so the frame is plain.
//
// IDENTITY IS NOT RECOVERED.  Each class is named for its own destructor's
// address and its vtable is pinned at the address the store names.

struct GenRoot0082AE40
{
	virtual ~GenRoot0082AE40();		// retail 0x0082AE40
};

struct Gen0082AE60 : GenRoot0082AE40
{
	virtual ~Gen0082AE60();		// vtable 0x00D2E8C4
};

struct Gen0082AE80 : GenRoot0082AE40
{
	virtual ~Gen0082AE80();		// vtable 0x00D2E8D0
};

struct Gen0082AEA0 : Gen0082AE60
{
	virtual ~Gen0082AEA0();		// vtable 0x00D2E8DC
};

struct Gen0082AEC0 : Gen0082AE60
{
	virtual ~Gen0082AEC0();		// vtable 0x00D2E8E8
};

struct Gen0082AEE0 : Gen0082AE60
{
	virtual ~Gen0082AEE0();		// vtable 0x00D2E8F4
};

struct Gen0082AF00 : Gen0082AE60
{
	virtual ~Gen0082AF00();		// vtable 0x00D2E900
};

struct Gen0082AF20 : Gen0082AE80
{
	virtual ~Gen0082AF20();		// vtable 0x00D2E90C
};

struct Gen0082AF40 : Gen0082AE80
{
	virtual ~Gen0082AF40();		// vtable 0x00D2E918
};

struct Gen0082AF60 : Gen0082AE80
{
	virtual ~Gen0082AF60();		// vtable 0x00D2E924
};

// ??1Gen0082AE60@@UAE@XZ		28B at 0x0082AE60
Gen0082AE60::~Gen0082AE60()
{
}

// ??1Gen0082AE80@@UAE@XZ		28B at 0x0082AE80
Gen0082AE80::~Gen0082AE80()
{
}

// ??1Gen0082AEA0@@UAE@XZ		28B at 0x0082AEA0
Gen0082AEA0::~Gen0082AEA0()
{
}

// ??1Gen0082AEC0@@UAE@XZ		28B at 0x0082AEC0
Gen0082AEC0::~Gen0082AEC0()
{
}

// ??1Gen0082AEE0@@UAE@XZ		28B at 0x0082AEE0
Gen0082AEE0::~Gen0082AEE0()
{
}

// ??1Gen0082AF00@@UAE@XZ		28B at 0x0082AF00
Gen0082AF00::~Gen0082AF00()
{
}

// ??1Gen0082AF20@@UAE@XZ		28B at 0x0082AF20
Gen0082AF20::~Gen0082AF20()
{
}

// ??1Gen0082AF40@@UAE@XZ		28B at 0x0082AF40
Gen0082AF40::~Gen0082AF40()
{
}

// ??1Gen0082AF60@@UAE@XZ		28B at 0x0082AF60
Gen0082AF60::~Gen0082AF60()
{
}
