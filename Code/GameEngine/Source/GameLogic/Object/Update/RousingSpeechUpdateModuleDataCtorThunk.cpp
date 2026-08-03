// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift RousingSpeechUpdateModuleData ctor __emit thunk to clean
// C++. Out-of-line base ctor, own vtable, scalar zeroings, a tracked member
// at +0x274 (inline zero ctor, out-of-line dtor) taking SEH state 0, then the
// member object at +0x280 constructed at state 1 (trivial dtor, untracked).

class RS_Base
{
public:
    RS_Base();
    virtual ~RS_Base();

private:
    unsigned char m_pad[0x250];
};

class RS_SubObj
{
public:
    RS_SubObj() : m_value(0) {}
    ~RS_SubObj();

private:
    unsigned int m_value;
};

class RS_Member
{
public:
    RS_Member();

private:
    unsigned int m_dummy;
};

class RousingSpeechUpdateModuleData : public RS_Base
{
public:
    RousingSpeechUpdateModuleData();

private:
    unsigned int m_a;
    unsigned int m_b;
    unsigned int m_c;
    unsigned int m_d;
    unsigned int m_e;
    unsigned char m_f;
    unsigned int m_g;
    unsigned int m_h;
    unsigned int m_i;
    RS_SubObj m_tracked;
    unsigned char m_k;
    RS_Member m_obj;
};

// ??0RousingSpeechUpdateModuleData@@QAE@XZ
RousingSpeechUpdateModuleData::RousingSpeechUpdateModuleData()
    : m_a(0), m_b(0), m_c(0), m_d(0), m_e(0), m_f(0), m_g(0), m_h(0), m_i(0), m_k(0)
{
}
