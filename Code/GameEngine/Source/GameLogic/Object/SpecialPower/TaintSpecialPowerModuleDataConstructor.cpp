// cl: /DNDEBUG /MD /EHsc

// TaintSpecialPowerModuleData's constructor, retail 0x0026B870.
//
// The base constructor is the shared SpecialPower module-data one that runs to
// +0x210, reached here through the incremental-link thunk at 0x00015C44, the
// same pin ScavengerSpecialPowerModuleData uses. Only the four fields from
// +0x210 to +0x21C belong to this class: three zeros and 10.0f at +0x214.
//
// Retail writes the vftable pointer FIRST, immediately after the base
// constructor returns and before the three zeroed fields; the compiler's own
// vptr initialization sinks past them instead, landing next to the 10.0f store,
// because this backend canonicalises a constructor's stores into a
// register-store group followed by an immediate-store group and files the vptr
// store at the head of the immediate group. Source statement order does not
// reach that decision -- every ordering of the four assignments, member-init
// list or body, chained or separate, compiles to the same sunk shape -- and
// neither does volatile on the members, nor __declspec(novtable) with the
// vftable written by hand as an ordinary store.
//
// What does reach it is writing every store through a volatile-qualified
// lvalue, which forces the emitted order to be the written order. So the
// vftable pointer is suppressed with __declspec(novtable) and stored explicitly
// as the first statement, exactly the shape ElvenWoodSpecialPowerModuleData's
// constructor needed at 0x0025CA40 for the same residue.
//
// Sibling constructors whose retail order already agrees with the backend --
// Devastate at 0x0025AC10, SiegeDeploy at 0x00266450 -- need none of this and
// are written as plain assignments; the volatile spelling is only for the ones
// where retail keeps the vftable store ahead of the register-store group.

class BfmeSpecialPowerModuleDataBase
{
public:
	BfmeSpecialPowerModuleDataBase();

	virtual void moduleDataAnchor();

private:
	unsigned char m_unmodelled_04[ 0x210 - 4 ];
};

extern "C" char TaintSpecialPowerModuleData_vtbl;

class __declspec(novtable) TaintSpecialPowerModuleData
	: public BfmeSpecialPowerModuleDataBase
{
public:
	TaintSpecialPowerModuleData();

private:
	unsigned int m_unmodelled_210;				// +0x210
	float m_unmodelled_214;						// +0x214
	unsigned int m_unmodelled_218;				// +0x218
	unsigned int m_unmodelled_21C;				// +0x21C
};

// ??0TaintSpecialPowerModuleData@@QAE@XZ
TaintSpecialPowerModuleData::TaintSpecialPowerModuleData()
{
	*reinterpret_cast<char *volatile *>(this) =
		&TaintSpecialPowerModuleData_vtbl;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_210) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_218) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_21C) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_214) = 0x41200000u; // 10.0f
}
