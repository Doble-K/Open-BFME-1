// cl: /DNDEBUG /MD /EHsc
// Lift the isRepairMostImportant __emit thunk to clean C++.
//
// Retail walks State +0x1C -> +0x10 -> +0x204 to reach the repair manager, then
// makes three virtual calls. The filler virtuals below exist only to push the
// three real ones onto their retail vtable offsets (+0x13C and +0x180 on the
// manager, +0x14 on the target); none of them is ever defined or called.
// The trailing `dec/neg/sbb/inc` in the dump is MSVC 7.1's `== 1` idiom.

class State;

class RepairTarget
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual int getCount();					///< vtable +0x14
};

class RepairManager
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void unused44();
	virtual void unused45();
	virtual void unused46();
	virtual void unused47();
	virtual void unused48();
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual void unused53();
	virtual void unused54();
	virtual void unused55();
	virtual void unused56();
	virtual void unused57();
	virtual void unused58();
	virtual void unused59();
	virtual void unused60();
	virtual void unused61();
	virtual void unused62();
	virtual void unused63();
	virtual void unused64();
	virtual void unused65();
	virtual void unused66();
	virtual void unused67();
	virtual void unused68();
	virtual void unused69();
	virtual void unused70();
	virtual void unused71();
	virtual void unused72();
	virtual void unused73();
	virtual void unused74();
	virtual void unused75();
	virtual void unused76();
	virtual void unused77();
	virtual void unused78();
	virtual RepairTarget *getRepairTarget();	///< vtable +0x13C
	virtual void unused80();
	virtual void unused81();
	virtual void unused82();
	virtual void unused83();
	virtual void unused84();
	virtual void unused85();
	virtual void unused86();
	virtual void unused87();
	virtual void unused88();
	virtual void unused89();
	virtual void unused90();
	virtual void unused91();
	virtual void unused92();
	virtual void unused93();
	virtual void unused94();
	virtual void unused95();
	virtual bool isRepairActive();			///< vtable +0x180
};

struct DozerStateLevel3
{
	unsigned char m_pad[0x204];
	RepairManager *m_manager;					///< this+0x204
};

struct DozerStateLevel2
{
	unsigned char m_pad[0x10];
	DozerStateLevel3 *m_level3;					///< this+0x10
};

struct DozerStateOwner
{
	unsigned char m_pad[0x1C];
	DozerStateLevel2 *m_level2;					///< this+0x1C
};

class DozerPrimaryStateMachine
{
public:
	static bool __cdecl isRepairMostImportant(State *, void *);
};

// ?isRepairMostImportant@DozerPrimaryStateMachine@@SA_NPAVState@@PAX@Z
bool __cdecl DozerPrimaryStateMachine::isRepairMostImportant(State *state, void *)
{
	RepairManager *manager =
		((DozerStateOwner *)state)->m_level2->m_level3->m_manager;
	if (manager == 0)
		return false;

	RepairTarget *target = manager->getRepairTarget();
	if (target == 0)
		return false;

	if (!manager->isRepairActive())
		return false;

	return target->getCount() == 1;
}
