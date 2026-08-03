// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DieModuleData ctor. Snapshot base + DieMuxData @+8.

class Snapshot
{
public:
	Snapshot();
	virtual ~Snapshot() {}
private:
	unsigned char m_pad[4];
};

class DieMuxData
{
public:
	DieMuxData();
private:
	unsigned char m_opaque[0x20];
};

class DieModuleData : public Snapshot
{
public:
	DieModuleData();
	virtual void dieModuleDataAnchor();
private:
	DieMuxData m_mux;
};

// ??0DieModuleData@@QAE@XZ
DieModuleData::DieModuleData()
{
}
