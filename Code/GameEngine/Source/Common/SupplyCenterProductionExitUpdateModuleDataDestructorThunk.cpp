// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: clean C++ lift of the retail module-data destructor.

#include <vector>

class SupplyCenterProductionExitEntry
{
public:
	~SupplyCenterProductionExitEntry();
};

class UpdateModuleData
{
public:
	virtual ~UpdateModuleData();

private:
	unsigned int m_moduleTagNameKey;
};

class SupplyCenterProductionExitUpdateModuleData : public UpdateModuleData
{
public:
	virtual ~SupplyCenterProductionExitUpdateModuleData();

private:
	std::vector<SupplyCenterProductionExitEntry *> m_entries;
	std::vector<unsigned int> m_values;
};

// ??1SupplyCenterProductionExitUpdateModuleData@@UAE@XZ
SupplyCenterProductionExitUpdateModuleData::~SupplyCenterProductionExitUpdateModuleData()
{
	for (std::vector<SupplyCenterProductionExitEntry *>::iterator it = m_entries.begin(); it != m_entries.end(); ++it)
		delete *it;
}
