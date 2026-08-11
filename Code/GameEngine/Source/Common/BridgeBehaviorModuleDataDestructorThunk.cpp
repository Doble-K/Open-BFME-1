// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: clean C++ lift of the retail BridgeBehavior module-data destructor.

#include <list>

typedef unsigned int UnsignedInt;

class AsciiString
{
public:
	~AsciiString();

private:
	char *m_data;
};

struct TimeAndLocationInfo
{
	UnsignedInt delay;
	AsciiString boneName;
};

class FXList;
class ObjectCreationList;

struct BridgeFXInfo
{
	const FXList *fx;
	TimeAndLocationInfo timeAndLocationInfo;
};

struct BridgeOCLInfo
{
	const ObjectCreationList *ocl;
	TimeAndLocationInfo timeAndLocationInfo;
};

class BehaviorModuleData
{
public:
	virtual ~BehaviorModuleData() {}

private:
	int m_data;
};

class BridgeBehaviorModuleData : public BehaviorModuleData
{
public:
	virtual ~BridgeBehaviorModuleData();

private:
	float m_lateralScaffoldSpeed;
	float m_verticalScaffoldSpeed;
	std::list<BridgeFXInfo> m_fx;
	std::list<BridgeOCLInfo> m_ocl;
};

BridgeBehaviorModuleData::~BridgeBehaviorModuleData()
{
	m_fx.clear();
	m_ocl.clear();
}
