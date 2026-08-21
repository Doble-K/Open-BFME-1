// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: three more constructors out of d_0005b6c0.asm.
//
// 0x00071B90 is the plain polymorphic one: `mov eax,ecx` opens it, the vftable
// at 0x01075E54 goes down first and the single pointer argument second, which
// is the fixed ctor order (own vptr before member stores) and not a source
// choice.
//
// 0x00061BB0 and 0x00065C50 are the same shape twice over different types: zero
// the word at this+0 and then call a one-argument member with ecx still holding
// this and no stack cleanup after the call -- callee-clean with a this pointer,
// so a __thiscall member and not a free helper. The callees at 0x00850670 and
// 0x009D6290 are unconverted elsewhere in the image; they are pinned by name
// here so the REL32 resolves, and their identity is not recovered.
//
// All three identities are address-derived.

typedef int Int;

// ---------------------------------------------------------------------------

class Rva00071B90Holder
{
public:
	Rva00071B90Holder(void *target);

	virtual void slot00(void);

private:
	void *m_target;										///< retail this+0x04
};

// ??0Rva00071B90Holder@@QAE@PAX@Z
Rva00071B90Holder::Rva00071B90Holder(void *target)
{
	m_target = target;
}

// ---------------------------------------------------------------------------

class Rva00061BB0Owner
{
public:
	Rva00061BB0Owner(void *source);

private:
	void attach(void *source);							///< retail 0x00850670

	Int m_value00;										///< retail this+0x00
};

// ??0Rva00061BB0Owner@@QAE@PAX@Z
Rva00061BB0Owner::Rva00061BB0Owner(void *source)
{
	m_value00 = 0;
	attach(source);
}

// ---------------------------------------------------------------------------

class Rva00065C50Owner
{
public:
	Rva00065C50Owner(void *source);

private:
	void attach(void *source);							///< retail 0x009D6290

	Int m_value00;										///< retail this+0x00
};

// ??0Rva00065C50Owner@@QAE@PAX@Z
Rva00065C50Owner::Rva00065C50Owner(void *source)
{
	m_value00 = 0;
	attach(source);
}
