// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

enum WeaponSlotType { };
class Object;
class AIUpdateInterface
{
public:
	bool isWeaponSlotOnTurretAndAimingAtTarget(WeaponSlotType, const Object *) const;
};

// ?isWeaponSlotOnTurretAndAimingAtTarget@AIUpdateInterface@@QBE_NW4WeaponSlotType@@PBVObject@@@Z
__declspec(naked) bool AIUpdateInterface::isWeaponSlotOnTurretAndAimingAtTarget(WeaponSlotType, const Object *) const
{
	__asm {
		__emit 0x53
		__emit 0x55
		__emit 0x8b
		__emit 0x6c
		__emit 0x24
		__emit 0x0c
		__emit 0x56
		__emit 0x8b
		__emit 0xd9
		__emit 0x57
		__emit 0x33
		__emit 0xf6
		__emit 0x8d
		__emit 0xbb
		__emit 0xe8
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x8b
		__emit 0x0f
		__emit 0x85
		__emit 0xc9
		__emit 0x74
		__emit 0x0a
		__emit 0x55
		__emit 0xe8
		__emit 0x76
		__emit 0xb2
		__emit 0xdc
		__emit 0xff
		__emit 0x84
		__emit 0xc0
		__emit 0x75
		__emit 0x12
		__emit 0x46
		__emit 0x83
		__emit 0xc7
		__emit 0x04
		__emit 0x83
		__emit 0xfe
		__emit 0x02
		__emit 0x7c
		__emit 0xe7
		__emit 0x5f
		__emit 0x5e
		__emit 0x5d
		__emit 0x32
		__emit 0xc0
		__emit 0x5b
		__emit 0xc2
		__emit 0x08
		__emit 0x00
		__emit 0x8b
		__emit 0x44
		__emit 0x24
		__emit 0x18
		__emit 0x8b
		__emit 0x8c
		__emit 0xb3
		__emit 0xe8
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0xe8
		__emit 0x02
		__emit 0x8f
		__emit 0xd9
		__emit 0xff
		__emit 0x5f
		__emit 0x5e
		__emit 0x5d
		__emit 0x5b
		__emit 0xc2
		__emit 0x08
		__emit 0x00
	}
}
