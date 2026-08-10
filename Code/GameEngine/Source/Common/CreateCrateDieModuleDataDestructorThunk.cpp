// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME5: lift MASM dump to standalone C++ thunk.

#include <list>

struct Gen_t_000800c0_p4cd
{
public:
	~Gen_t_000800c0_p4cd();

private:
	char *m_data;
};

typedef Gen_t_000800c0_p4cd AsciiString;

class CreateCrateDieModuleDataBase
{
public:
	virtual ~CreateCrateDieModuleDataBase() {}

private:
	unsigned char m_pad[0x30];
};

class CreateCrateDieModuleData : public CreateCrateDieModuleDataBase
{
public:
    virtual ~CreateCrateDieModuleData();

private:
	_STL::list<AsciiString> m_crateNameList;
};

// ??1CreateCrateDieModuleData@@UAE@XZ
CreateCrateDieModuleData::~CreateCrateDieModuleData()
{
	m_crateNameList.clear();
}
