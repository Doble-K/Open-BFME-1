// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ lift of the ModuleData destructor.

class GeometryUpgradeModuleDataMemberA
{
public:
	~GeometryUpgradeModuleDataMemberA();

private:
	unsigned char m_data[0x68];
};

class GeometryUpgradeModuleDataMemberB
{
public:
	~GeometryUpgradeModuleDataMemberB();

private:
	unsigned char m_data[0x0c];
};

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();

	char *m_data;
};

class GeometryUpgradeModuleDataPrimaryBase
{
public:
	virtual ~GeometryUpgradeModuleDataPrimaryBase() {}

private:
	unsigned int m_04;
};

class __declspec(novtable) GeometryUpgradeModuleDataIntermediateBase
	: public GeometryUpgradeModuleDataPrimaryBase
{
private:
	GeometryUpgradeModuleDataMemberA m_base;
};

class __declspec(novtable) GeometryUpgradeModuleData
	: public GeometryUpgradeModuleDataIntermediateBase
{
public:
	virtual ~GeometryUpgradeModuleData();

private:
	GeometryUpgradeModuleDataMemberB m_first;
	GeometryUpgradeModuleDataMemberB m_second;
	BFMERetailAsciiString m_name0;
	BFMERetailAsciiString m_name1;
	BFMERetailAsciiString m_name2;
};

// ??1GeometryUpgradeModuleData@@UAE@XZ
GeometryUpgradeModuleData::~GeometryUpgradeModuleData()
{
}
