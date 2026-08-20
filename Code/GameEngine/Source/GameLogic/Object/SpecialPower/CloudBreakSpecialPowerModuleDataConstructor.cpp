// cl: /DNDEBUG /MD /EHsc

// CloudBreakSpecialPowerModuleData's constructor, retail 0x002592A0.
//
// Same shape as TaintSpecialPowerModuleData at 0x0026B870: the shared
// SpecialPower module-data base running to +0x210, reached through the
// incremental-link thunk at 0x00015C44, then four fields of this class's own --
// 10.0f at +0x210, two zeros, and 100.0f at +0x21C.
//
// Retail writes the vftable pointer first, ahead of the zero pair, and writes
// +0x218 before +0x214. The backend reaches neither on its own: it files the
// compiler's vptr store at the head of the immediate-store group, behind the
// register-store group, and it canonicalises the zero pair's order regardless of
// how the source spells it (a chained `a = b = 0` only flips the pair to
// descending). Writing every store through a volatile-qualified lvalue, with the
// vftable suppressed by __declspec(novtable) and stored by hand, pins the
// emitted order to the written order and gives retail exactly. This is the same
// spelling ElvenWood (0x0025CA40) and Taint (0x0026B870) need.

class BfmeSpecialPowerModuleDataBase
{
public:
	BfmeSpecialPowerModuleDataBase();

	virtual void moduleDataAnchor();

private:
	unsigned char m_unmodelled_04[ 0x210 - 4 ];
};

extern "C" char CloudBreakSpecialPowerModuleData_vtbl;

class __declspec(novtable) CloudBreakSpecialPowerModuleData
	: public BfmeSpecialPowerModuleDataBase
{
public:
	CloudBreakSpecialPowerModuleData();

private:
	float m_unmodelled_210;						// +0x210
	unsigned int m_unmodelled_214;				// +0x214
	unsigned int m_unmodelled_218;				// +0x218
	float m_unmodelled_21C;						// +0x21C
};

// ??0CloudBreakSpecialPowerModuleData@@QAE@XZ
CloudBreakSpecialPowerModuleData::CloudBreakSpecialPowerModuleData()
{
	*reinterpret_cast<char *volatile *>(this) =
		&CloudBreakSpecialPowerModuleData_vtbl;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_218) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_214) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_210) = 0x41200000u;	// 10.0f
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_21C) = 0x42C80000u;	// 100.0f
}
