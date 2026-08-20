// cl: /DNDEBUG /MD /EHsc

// The client-update-module constructor at retail 0x00603790, 95 bytes.
//
// IDENTITY, and why the row does not assert it. The incremental-link thunk at
// 0x00006780 is `jmp 0x00603790` and reverse/symbols.csv pins that thunk as
// ??0LaserUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, so this is LaserUpdate's
// constructor. The ledger already spends that mangled name on a DIFFERENT
// 5-byte thunk, 0x00035D91, whose jump lands on 0x002B1060 -- an SEH-framed
// constructor that writes four vftables (0x0109C9D0, 0x0109CBA0, 0x010A1DE4,
// 0x010C5124) and cannot be the same body. One of the two claims is wrong and
// the ledger allows a name only one address, so this row takes an
// address-derived placeholder rather than contest the older one. Promoting it
// to the real name is a one-line repoint once 0x00035D91 is re-identified.
//
// SHAPE. The base is ClientUpdateModule(Thing *, const ModuleData *), already
// pinned at the 0x00002874 thunk. Its subobject ends at +0x0C; everything from
// +0x0C to +0x50 is this class's own, all zeroed except 1.0f at +0x3C.
//
// Retail writes the byte at +0x24 first, then the vftable pointer, and only
// then the rest -- and puts +0x31 between +0x38 and +0x40. The backend reaches
// none of that on its own: it canonicalises a constructor's stores into a
// register-store group followed by an immediate-store group and files the
// compiler's own vptr store at the head of the immediate group, so the vftable
// sinks to second-from-last beside the 1.0f store no matter how the source is
// spelled -- member-init list, body statements in retail order, first field
// first. Writing every store through a volatile-qualified lvalue, with the
// vftable suppressed by __declspec(novtable) and stored by hand, pins the
// emitted order to the written order. Same spelling as ElvenWood
// (0x0025CA40), Taint (0x0026B870) and CloudBreak (0x002592A0).

class Thing;
class ModuleData;

class ClientUpdateModule
{
public:
	ClientUpdateModule( Thing *thing, const ModuleData *moduleData );

	virtual void clientUpdateModuleAnchor();

private:
	unsigned char m_unmodelled_04[ 0x0C - 4 ];
};

extern "C" char Rva603790_vtbl;

class __declspec(novtable) Rva603790Ctor : public ClientUpdateModule
{
public:
	Rva603790Ctor( Thing *thing, const ModuleData *moduleData );

private:
	unsigned int m_unmodelled_0C;
	unsigned int m_unmodelled_10;
	unsigned int m_unmodelled_14;
	unsigned int m_unmodelled_18;
	unsigned int m_unmodelled_1C;
	unsigned int m_unmodelled_20;
	unsigned char m_unmodelled_24;
	unsigned char m_pad_25[ 3 ];
	unsigned int m_unmodelled_28;
	unsigned int m_unmodelled_2C;
	unsigned char m_unmodelled_30;
	unsigned char m_unmodelled_31;
	unsigned char m_pad_32[ 2 ];
	unsigned int m_unmodelled_34;
	unsigned int m_unmodelled_38;
	float m_unmodelled_3C;
	unsigned int m_unmodelled_40;
	unsigned int m_unmodelled_44;
	unsigned int m_unmodelled_48;
	unsigned int m_unmodelled_4C;
	unsigned int m_unmodelled_50;
};

// ??0Rva603790Ctor@@QAE@PAVThing@@PBVModuleData@@@Z
Rva603790Ctor::Rva603790Ctor( Thing *thing, const ModuleData *moduleData )
	: ClientUpdateModule( thing, moduleData )
{
	*reinterpret_cast<unsigned char volatile *>(&m_unmodelled_24) = 0;
	*reinterpret_cast<char *volatile *>(this) = &Rva603790_vtbl;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_18) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_1C) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_20) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_0C) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_10) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_14) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_28) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_2C) = 0;
	*reinterpret_cast<unsigned char volatile *>(&m_unmodelled_30) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_34) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_38) = 0;
	*reinterpret_cast<unsigned char volatile *>(&m_unmodelled_31) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_40) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_44) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_48) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_4C) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_50) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_3C) = 0x3F800000u;	// 1.0f
}
