// cl: /DNDEBUG /MD /GX
// Open-BFME5: BFMENetworkThreadBase constructor at retail 0x009DB4E0.

class BFMENetworkThreadBase
{
public:
	BFMENetworkThreadBase(const char *name);
	virtual ~BFMENetworkThreadBase();

private:
	char m_threadName[0x40];
	void *m_auxHandle;
	void *m_liveHandle;
	int m_threadPriority;
};

extern "C" char *strcpy(char *, const char *);

BFMENetworkThreadBase::BFMENetworkThreadBase(const char *name)
{
	m_liveHandle = 0;
	m_threadPriority = 0;
	m_auxHandle = 0;
	if (name != 0) {
		strcpy(m_threadName, name);
	} else {
		*reinterpret_cast<unsigned int *>(m_threadName) =
			*reinterpret_cast<const unsigned int *>(0x0114483c);
		*reinterpret_cast<unsigned int *>(m_threadName + 4) =
			*reinterpret_cast<const unsigned int *>(0x01144840);
	}
}
