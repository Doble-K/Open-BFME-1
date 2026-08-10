// cl: /DNDEBUG /MD /EHa /Oy-
// Open-BFME5: clean C++ reconstruction of the ICF-shared DebugIOFlat body.

void DebugFreeMemory(void *ptr);

class DebugIOFlat
{
public:
    class OutputStream
    {
    public:
        void Delete(const char *path);
    };
};

class DebugIOInterface
{
public:
    virtual ~DebugIOInterface() {}
};

class DebugIOOds : public DebugIOInterface
{
    struct SplitListEntry
    {
        SplitListEntry *next;
    };

    struct StreamListEntry
    {
        StreamListEntry *next;
        DebugIOFlat::OutputStream *stream;
    };

    SplitListEntry *m_firstSplit;
    SplitListEntry **m_lastSplitPtr;
    StreamListEntry *m_firstStream;
    StreamListEntry **m_lastStreamPtr;
    char m_baseFilename[256];
    char m_copyDir[256];

public:
    virtual ~DebugIOOds();
};

// ??1DebugIOOds@@UAE@XZ
DebugIOOds::~DebugIOOds()
{
    for (SplitListEntry *cur=m_firstSplit;cur;)
    {
        SplitListEntry *kill=cur;
        cur=cur->next;
        DebugFreeMemory(kill);
    }
    m_firstSplit=0;

    for (StreamListEntry *stream=m_firstStream;stream;)
    {
        StreamListEntry *kill=stream;
        stream=stream->next;
        kill->stream->Delete(m_copyDir);
        DebugFreeMemory(kill);
    }
}
