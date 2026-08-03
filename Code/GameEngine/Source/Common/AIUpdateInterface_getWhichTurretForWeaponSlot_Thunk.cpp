// cl: /DNDEBUG /MD /EHsc
// Lift the AIUpdateInterface::getWhichTurretForWeaponSlot __emit thunk to clean C++.
//
// Zero Hour's AIUpdate.cpp carries this function verbatim, and the retail body
// agrees with it exactly: scan MAX_TURRETS entries, and on the first live turret
// that owns the weapon slot write back the angle and pitch through the optional
// out-parameters and return the index, else TURRET_INVALID. Retail confirms
// MAX_TURRETS == 2 (`cmp esi, 2`), the array at this+0x1E8, and the angle/pitch
// members at TurretAI+0x18/+0x1C. It also re-reads m_turretAI[i] for each
// write-back rather than caching the turret, which is what the ZH source does.

typedef float Real;

enum WeaponSlotType { PRIMARY_WEAPON = 0 };
enum WhichTurretType { TURRET_INVALID = -1, TURRET_MAIN = 0 };

enum { MAX_TURRETS = 2 };

class TurretAI
{
public:
	bool isWeaponSlotOnTurret(WeaponSlotType) const;	///< pinned to the ILT thunk at 0x00039D24

	Real getTurretAngle(void) const { return m_angle; }
	Real getTurretPitch(void) const { return m_pitch; }

private:
	unsigned char m_unreconstructed_00[0x18];
	Real m_angle;										///< retail this+0x18
	Real m_pitch;										///< retail this+0x1C
};

class AIUpdateInterface
{
public:
	WhichTurretType getWhichTurretForWeaponSlot(WeaponSlotType, Real *, Real *) const;

private:
	unsigned char m_unreconstructed_00[0x1E8];
	TurretAI *m_turretAI[MAX_TURRETS];					///< retail this+0x1E8
};

// ?getWhichTurretForWeaponSlot@AIUpdateInterface@@QBE?AW4WhichTurretType@@W4WeaponSlotType@@PAM1@Z
WhichTurretType AIUpdateInterface::getWhichTurretForWeaponSlot(WeaponSlotType wslot, Real *turretAngle,
															   Real *turretPitch) const
{
	for (int i = 0; i < MAX_TURRETS; ++i)
	{
		if (m_turretAI[i] && m_turretAI[i]->isWeaponSlotOnTurret(wslot))
		{
			if (turretAngle)
				*turretAngle = m_turretAI[i]->getTurretAngle();
			if (turretPitch)
				*turretPitch = m_turretAI[i]->getTurretPitch();

			return (WhichTurretType)i;
		}
	}
	return TURRET_INVALID;
}
