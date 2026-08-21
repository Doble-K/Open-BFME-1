// cl: /DNDEBUG /MD /EHsc

class Snapshot
{
protected:
	virtual void crc();
	virtual void xfer();
	virtual void loadPostProcess();
};

class DamageInfoInput : public Snapshot
{
public:
	DamageInfoInput();

private:
	unsigned char m_unreconstructed[0x44];
};

class DamageInfoOutput : public Snapshot
{
public:
	DamageInfoOutput()
	{
		m_actualDamageDealt = 0;
		m_actualDamageClipped = 0;
		m_noEffect = false;
	}

private:
	float m_actualDamageDealt;
	float m_actualDamageClipped;
	bool m_noEffect;
};

class DamageInfo : public Snapshot
{
public:
	DamageInfo();

private:
	DamageInfoInput in;
	DamageInfoOutput out;
};

DamageInfo::DamageInfo()
{
}
