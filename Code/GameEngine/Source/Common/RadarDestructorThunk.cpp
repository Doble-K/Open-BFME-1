// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the retail Radar destructor to clean C++.

class Snapshot
{
public:
    virtual ~Snapshot() {}
};

class __declspec(novtable) SubsystemInterface
{
public:
    SubsystemInterface();
    virtual ~SubsystemInterface();

private:
    unsigned m_name;
};

class RadarEventReference
{
public:
    virtual void release(int);
    int m_referenceCount;
};

struct RadarEvent
{
    int m_type;
    bool m_active;
    unsigned char m_padding[0x47];
    RadarEventReference *m_reference;

    RadarEvent() : m_reference(0) {}

    ~RadarEvent()
    {
        RadarEventReference *reference = m_reference;
        if (reference != 0)
        {
            int referenceCount = --reference->m_referenceCount;
            if (referenceCount <= 0)
            {
                reference->release(1);
            }
        }
    }
};

class Radar : public Snapshot, public SubsystemInterface
{
protected:
    void deleteListResources();

private:
    bool m_radarHidden;
    bool m_radarForceOn;
    void *m_objectList;
    void *m_localObjectList;
    float m_terrainAverageZ;
    float m_waterAverageZ;
    float m_xSample;
    float m_ySample;
    RadarEvent m_event[64];

public:
    virtual ~Radar();
};

Radar::~Radar()
{
    deleteListResources();
}
