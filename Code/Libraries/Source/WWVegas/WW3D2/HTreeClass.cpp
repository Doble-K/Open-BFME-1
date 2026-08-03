// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: HTreeClass default ctor + dtor
// Ctor retail 20B: zero +0x10/+0x14, float +0x18 = 1.0f, byte +0 = 0.

class HTreeClass
{
public:
	HTreeClass();
	~HTreeClass();

private:
	unsigned char m_name0;
	unsigned char m_pad[0xf];
	void *m_pivots;
	void *m_pivotCountOrPtr;
	float m_scale;
};

// ??0HTreeClass@@QAE@XZ
HTreeClass::HTreeClass()
{
	m_pivots = 0;
	m_pivotCountOrPtr = 0;
	m_scale = 1.0f;
	m_name0 = 0;
}

// Keep dtor as naked until separately converted (still matched via emit).
// ??1HTreeClass@@QAE@XZ
__declspec(naked) HTreeClass::~HTreeClass()
{
	__asm {
		_emit 056h
		_emit 08Bh
		_emit 0F1h
		_emit 08Bh
		_emit 046h
		_emit 014h
		_emit 085h
		_emit 0C0h
		_emit 074h
		_emit 010h
		_emit 050h
		_emit 0E8h
		_emit 010h
		_emit 0F7h
		_emit 0F2h
		_emit 0FFh
		_emit 083h
		_emit 0C4h
		_emit 004h
		_emit 0C7h
		_emit 046h
		_emit 014h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 0C7h
		_emit 046h
		_emit 010h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 0C7h
		_emit 046h
		_emit 018h
		_emit 000h
		_emit 000h
		_emit 080h
		_emit 03Fh
		_emit 05Eh
		_emit 0C3h
	}
}
