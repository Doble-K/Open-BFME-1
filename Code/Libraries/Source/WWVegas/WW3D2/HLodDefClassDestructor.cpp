// cl: /DNDEBUG /MD /EHsc

class HLodDefClass
{
public:
	class SubObjectArrayClass
	{
	public:
		~SubObjectArrayClass() throw();
	};

	~HLodDefClass();

private:
	void Free();
	unsigned char m_unreconstructed[0x10];
	SubObjectArrayClass m_aggregates;
};

HLodDefClass::~HLodDefClass()
{
	Free();
}
