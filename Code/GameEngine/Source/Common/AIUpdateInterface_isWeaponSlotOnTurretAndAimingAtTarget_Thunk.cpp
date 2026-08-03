// cl: /DNDEBUG /MD /EHsc
// Lift the AIUpdateInterface::isWeaponSlotOnTurretAndAimingAtTarget __emit thunk
// to clean C++.
//
// Zero Hour's AIUpdate.cpp carries this function verbatim and the retail body
// agrees exactly: scan the turrets and, on the first live one owning the weapon
// slot, tail-answer with that turret's aim test; otherwise false. Retail pins
// the same details as the getWhichTurretForWeaponSlot sibling -- MAX_TURRETS is
// 2 (`cmp esi, 2`) and the turret array sits at this+0x1E8.

typedef float Real;

class Object;

enum WeaponSlotType { PRIMARY_WEAPON = 0 };

enum { MAX_TURRETS = 2 };

class TurretAI
{
public:
	bool isWeaponSlotOnTurret(WeaponSlotType) const;		///< ILT thunk at 0x00039D24
	bool isTryingToAimAtTarget(const Object *) const;		///< ILT thunk at 0x000079D7
};

class AIUpdateInterface
{
public:
	bool isWeaponSlotOnTurretAndAimingAtTarget(WeaponSlotType, const Object *) const;

private:
	unsigned char m_unreconstructed_00[0x1E8];
	TurretAI *m_turretAI[MAX_TURRETS];						///< retail this+0x1E8
};

// ?isWeaponSlotOnTurretAndAimingAtTarget@AIUpdateInterface@@QBE_NW4WeaponSlotType@@PBVObject@@@Z
bool AIUpdateInterface::isWeaponSlotOnTurretAndAimingAtTarget(WeaponSlotType wslot,
															  const Object *victim) const
{
	for (int i = 0; i < MAX_TURRETS; i++)
	{
		if (m_turretAI[i] && m_turretAI[i]->isWeaponSlotOnTurret(wslot))
		{
			return m_turretAI[i]->isTryingToAimAtTarget(victim);
		}
	}
	return false;
}
