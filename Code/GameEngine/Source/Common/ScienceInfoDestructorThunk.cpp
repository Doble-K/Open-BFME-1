// cl: /DNDEBUG /MD /EHsc

class UnicodeString
{
public:
    ~UnicodeString();

private:
    void *m_data;
};

class ScienceVecStandIn
{
public:
    ~ScienceVecStandIn();

private:
    void *m_begin;
    void *m_end;
    void *m_capacity;
};

class Overridable
{
public:
    virtual ~Overridable()
    {
        if (m_nextOverride)
            delete m_nextOverride;
        m_nextOverride = 0;
    }

private:
    Overridable *m_nextOverride;
    bool m_isOverride;
};

class ScienceInfo : public Overridable
{
protected:
    virtual ~ScienceInfo();

private:
    int m_science;
    UnicodeString m_name;
    UnicodeString m_description;
    ScienceVecStandIn m_rootSciences;
    int m_sciencePurchasePointCost;
    bool m_grantable;
};

ScienceInfo::~ScienceInfo()
{
}
