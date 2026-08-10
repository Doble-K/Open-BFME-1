// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BFME checks the resolved save path through FileSystem directly.

class AsciiString
{
private:
	struct AsciiStringData
	{
		unsigned short m_refCount;
		unsigned short m_numCharsAllocated;
		unsigned int m_bfmeHeader;
	};

	AsciiStringData *m_data;

public:
	~AsciiString();

	const char *str() const
	{
		static const char empty = 0;
		return m_data != 0 ? reinterpret_cast<const char *>(m_data + 1) : &empty;
	}
};

class FileSystem
{
public:
	bool doesFileExist(const char *) const;
};

extern FileSystem *TheFileSystem;

class GameState
{
public:
	AsciiString getFilePathInSaveDirectory(const AsciiString &) const;
	bool doesSaveGameExist(AsciiString);
};

// ?doesSaveGameExist@GameState@@QAE_NVAsciiString@@@Z
bool GameState::doesSaveGameExist(AsciiString filename)
{
	AsciiString filepath = getFilePathInSaveDirectory(filename);
	return TheFileSystem->doesFileExist(filepath.str());
}
