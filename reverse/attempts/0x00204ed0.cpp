// ??0Gen_00204ED0@@QAE@XZ
// partial score=0.94 date=2026-08-25
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

// Retail 0x00204ED0, 69 bytes: the body the naked BattlePlanUpdateModuleData
// constructor thunk jumps to.
//
// The vptr store lands before the only constructor call, and that call takes
// esi+8 rather than esi, so what sits at +0x08 is a member with its own
// constructor -- UpgradeModuleDataSub -- and not a base. It runs to +0x70,
// which fixes its size at 0x68.
//
// The stores are grouped by the register holding the value, so every zero goes
// out together ahead of the two immediates. Within the zero group the order is
// the source order, which is why +0x7C comes before +0x74.
//
// The three zeros at +0x7C go out through a lea'd base register while every
// other store uses a full displacement off esi. A base register there means an
// inlined member function holding that sub-object's this in ecx, not three
// separate field assignments.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub(void);			// ILT 0x0000F0A6

private:
	char m_bfmeFields[0x68];
};

class Gen_00204ED0
{
public:
	Gen_00204ED0(void);

	virtual void bfmeSlot0(void);

private:
	int m_bfmeHead;					// +0x04
	UpgradeModuleDataSub m_bfmeSub;			// +0x08
	float m_bfmeRange;				// +0x70
	int m_bfme74;					// +0x74
	int m_bfme78;					// +0x78
	Coord3D m_bfmeOffset;				// +0x7C
	int m_bfmeCount;				// +0x88
	bool m_bfme8C;					// +0x8C
	bool m_bfme8D;					// +0x8D
};

// ??0Gen_00204ED0@@QAE@XZ
Gen_00204ED0::Gen_00204ED0(void)
{
	m_bfmeOffset.x = 0.0f;
	m_bfmeOffset.y = 0.0f;
	m_bfmeOffset.z = 0.0f;
	m_bfme8C = false;
	m_bfme74 = 0;
	m_bfme78 = 0;
	m_bfme8D = false;
	m_bfmeCount = 5;
	m_bfmeRange = 100.0f;
}
