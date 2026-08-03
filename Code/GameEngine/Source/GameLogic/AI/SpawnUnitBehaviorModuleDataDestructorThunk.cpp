// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SpawnUnitBehaviorModuleData dtor.
// Retail 80B SEH: destroy Buffer @+0xc then @+0x8, base vtbl store. Buffer pin 0x887940 (ICF with Oathbreakers).

class Buffer
{
public:
	~Buffer();

private:
	unsigned char m_pad[4];
};

class SpawnUnitBehaviorModuleDataBase
{
public:
	virtual ~SpawnUnitBehaviorModuleDataBase() {}

private:
	unsigned char m_pad[0x4];
};

class __declspec(novtable) SpawnUnitBehaviorModuleData
	: public SpawnUnitBehaviorModuleDataBase
{
public:
	virtual ~SpawnUnitBehaviorModuleData();

private:
	Buffer m_a;
	Buffer m_b;
};

// ??1SpawnUnitBehaviorModuleData@@UAE@XZ
SpawnUnitBehaviorModuleData::~SpawnUnitBehaviorModuleData()
{
}
