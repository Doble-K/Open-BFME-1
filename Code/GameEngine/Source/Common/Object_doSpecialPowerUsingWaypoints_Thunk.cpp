// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class SpecialPowerTemplate;
class Waypoint;
class Object
{
public:
	void doSpecialPowerUsingWaypoints(const SpecialPowerTemplate *, const Waypoint *, unsigned int, bool);
};

// ?doSpecialPowerUsingWaypoints@Object@@QAEXPBVSpecialPowerTemplate@@PBVWaypoint@@I_N@Z
__declspec(naked) void Object::doSpecialPowerUsingWaypoints(const SpecialPowerTemplate *, const Waypoint *, unsigned int, bool)
{
	__asm {
		__emit 0x56
		__emit 0x8b
		__emit 0xf1
		__emit 0x8b
		__emit 0x86
		__emit 0xa4
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0x75
		__emit 0x3c
		__emit 0x8a
		__emit 0x44
		__emit 0x24
		__emit 0x14
		__emit 0x84
		__emit 0xc0
		__emit 0x57
		__emit 0x8b
		__emit 0x7c
		__emit 0x24
		__emit 0x0c
		__emit 0x75
		__emit 0x11
		__emit 0x8b
		__emit 0x0d
		__emit 0x0c
		__emit 0xd8
		__emit 0x2e
		__emit 0x01
		__emit 0x57
		__emit 0x56
		__emit 0xe8
		__emit 0x2a
		__emit 0xac
		__emit 0xe6
		__emit 0xff
		__emit 0x84
		__emit 0xc0
		__emit 0x74
		__emit 0x1d
		__emit 0x57
		__emit 0x8b
		__emit 0xce
		__emit 0xe8
		__emit 0x3c
		__emit 0xc9
		__emit 0xe7
		__emit 0xff
		__emit 0x85
		__emit 0xc0
		__emit 0x74
		__emit 0x11
		__emit 0x8b
		__emit 0x4c
		__emit 0x24
		__emit 0x14
		__emit 0x8b
		__emit 0x10
		__emit 0x51
		__emit 0x8b
		__emit 0x4c
		__emit 0x24
		__emit 0x14
		__emit 0x51
		__emit 0x8b
		__emit 0xc8
		__emit 0xff
		__emit 0x52
		__emit 0x34
		__emit 0x5f
		__emit 0x5e
		__emit 0xc2
		__emit 0x10
		__emit 0x00
	}
}
