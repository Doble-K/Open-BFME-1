// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AudioEventRTS' destructor, retail 0x000CFA40, 77 bytes. The body
// carried only a machine byte-dump row; reverse/reloc_names.csv holds the name
// with identity=real.
//
// Two strings and nothing else: the AsciiString at +0x18 and then the
// UnicodeString at +0x14, which is reverse declaration order. There is no base
// call at the end, so the class has no polymorphic base of its own, and there
// is no vptr store at the top either even though the destructor is virtual --
// that is __declspec(novtable), the same shape the ModuleData destructors in
// the ledger carry.

class AsciiString
{
public:
	~AsciiString();						// retail 0x00887940

private:
	char *m_bfmeData;
};

class UnicodeString
{
public:
	~UnicodeString();					// retail 0x008881D0

private:
	void *m_bfmeData;
};

class __declspec(novtable) AudioEventRTS
{
public:
	virtual ~AudioEventRTS();

private:
	char m_bfmeHead[0x14 - 0x04];
	UnicodeString m_bfmeText;				// +0x14
	AsciiString m_bfmeName;					// +0x18
};

// ??1AudioEventRTS@@UAE@XZ
AudioEventRTS::~AudioEventRTS()
{
}
