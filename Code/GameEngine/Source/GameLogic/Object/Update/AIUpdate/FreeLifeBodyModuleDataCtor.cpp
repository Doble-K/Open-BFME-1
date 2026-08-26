// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: FreeLifeBodyModuleData ctor.
// Base 0x64; fields at +64..+7c with -1 at +70.

class FreeLifeBodyModuleDataBase
{
public:
	FreeLifeBodyModuleDataBase();
	virtual ~FreeLifeBodyModuleDataBase();

private:
	unsigned char m_pad[0x60];
};

class FreeLifeBodyModuleData : public FreeLifeBodyModuleDataBase
{
public:
	FreeLifeBodyModuleData();
	virtual ~FreeLifeBodyModuleData();

private:
	unsigned int m_64;
	unsigned int m_68;
	unsigned char m_6c;
	unsigned char m_pad6d[3];
	unsigned int m_70;
	unsigned int m_74;
	unsigned int m_78;
	unsigned int m_7c;
};

// ??0FreeLifeBodyModuleData@@QAE@XZ
FreeLifeBodyModuleData::FreeLifeBodyModuleData()
{
	m_64 = 0;
	m_68 = 0;
	m_6c = 0;
	m_7c = 0;
	m_74 = 0;
	m_78 = 0;
	m_70 = 0xffffffff;
}
