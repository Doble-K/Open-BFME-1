// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ModuleInfo::Nugget dtor. dual strings: first@+0 body, tag@+4 ILT.

class AsciiString
{
public:
	~AsciiString();

private:
	unsigned char m_pad[4];
};

class ModuleTagString
{
public:
	~ModuleTagString();

private:
	unsigned char m_pad[4];
};

class ModuleInfo
{
public:
	class Nugget
	{
	public:
		~Nugget();

	private:
		AsciiString first;
		ModuleTagString m_moduleTag;
	};
};

// ??1Nugget@ModuleInfo@@QAE@XZ
ModuleInfo::Nugget::~Nugget()
{
}
