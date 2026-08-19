// cl: /DNDEBUG /MD /EHsc

// FILE: AssistedTargetingObjectShim_find.cpp /////////////////////////////////
//
// AssistedTargetingObjectShim::find, retail 0x001BE270 - the same forty-seven
// bytes as Object::getCurrentWeapon at 0x001BE230, forty bytes earlier, which
// the linker did not fold. Same layout: the table of four pointers at +0x26C,
// the index at +0x27C, and the guard at +0x284.
//
// The decorated name says the argument is an int. It is not - the body stores
// through it - but that name comes from a stand-in declaration in
// promoted__isFreeToAssist_AssistedTargetingUpdate, and the ledger has to agree
// with it, so the store is spelled through a cast rather than a typed pointer.
//
///////////////////////////////////////////////////////////////////////////////

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0,
	SECONDARY_WEAPON,
	TERTIARY_WEAPON,

	WEAPONSLOT_COUNT
};

class AssistedTargetingObjectShim
{
public:
	void *find( int slotOut );

private:
	unsigned char m_unmodelled_00[ 0x26C ];
	void *m_weapons[ 4 ];					// +0x26C
	WeaponSlotType m_curWeapon;				// +0x27C
	unsigned char m_unmodelled_280[ 4 ];
	void *m_weaponSet;						// +0x284
};

// ?find@AssistedTargetingObjectShim@@QAEPAXH@Z
void *AssistedTargetingObjectShim::find( int slotOut )
{
	if( m_weaponSet == 0 )
		return 0;

	if( slotOut )
		*(WeaponSlotType *)slotOut = m_curWeapon;

	return m_weapons[ m_curWeapon ];
}
