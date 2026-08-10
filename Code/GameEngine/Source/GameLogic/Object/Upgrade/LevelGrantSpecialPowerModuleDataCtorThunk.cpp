// cl: /DNDEBUG /MD /EHsc

#include <string.h>

class RS_Base
{
public:
    RS_Base();
    virtual ~RS_Base();

private:
    unsigned char m_pad[0x250];
};

class RS_Member
{
public:
    RS_Member();

    unsigned int m_dummy;
    volatile unsigned int m_second;
};

struct SixDwords
{
    SixDwords() { memset(this, 0, sizeof(*this)); }

    volatile unsigned int v[6];
};

class LevelGrantSpecialPowerModuleData : public RS_Base
{
public:
    LevelGrantSpecialPowerModuleData();

private:
    volatile unsigned int m_field254;
    unsigned int m_field258;
    volatile unsigned int m_field25c;
    RS_Member m_member;
    SixDwords m_fields268;
    unsigned char m_field280;
};

// ??0LevelGrantSpecialPowerModuleData@@QAE@XZ
LevelGrantSpecialPowerModuleData::LevelGrantSpecialPowerModuleData()
    : m_field258(0), m_fields268()
{
    m_field25c = 0;
    m_member.m_second = 0;
    m_field254 = 1;
    memset(&m_fields268, 0, sizeof(m_fields268));
    m_field280 = 0;
}
