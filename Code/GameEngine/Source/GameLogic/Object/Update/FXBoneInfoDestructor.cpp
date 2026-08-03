// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: FXBoneInfo destructor - destroy AsciiString at +4

class AsciiString
{
public:
	~AsciiString();
};

class FXBoneInfo
{
public:
	~FXBoneInfo();

private:
	int m_pad;
	AsciiString m_name;
};

// ??1FXBoneInfo@@QAE@XZ
FXBoneInfo::~FXBoneInfo()
{
}
