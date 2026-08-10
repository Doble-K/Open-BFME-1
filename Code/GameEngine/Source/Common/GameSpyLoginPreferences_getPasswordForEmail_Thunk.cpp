// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift GameSpyLoginPreferences::getPasswordForEmail to clean C++.

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();

	static AsciiString TheEmptyString;

private:
	void *m_data;
};

struct PassMapNode
{
	unsigned char m_unreconstructed_00[0x14];
	AsciiString m_value;
};

class PassMap
{
public:
	PassMapNode *find(const AsciiString &key);
	AsciiString &operator[](const AsciiString &key);
	PassMapNode *end() const { return m_header; }

private:
	PassMapNode *m_header;
};

class UserPreferences
{
public:
	virtual ~UserPreferences();

private:
	unsigned char m_unreconstructed_04[0x10];
};

class GameSpyLoginPreferences : public UserPreferences
{
public:
	AsciiString getPasswordForEmail(AsciiString email);

private:
	PassMap m_emailPasswordMap;
};

// ?getPasswordForEmail@GameSpyLoginPreferences@@QAE?AVAsciiString@@V2@@Z
AsciiString GameSpyLoginPreferences::getPasswordForEmail(AsciiString email)
{
	if (m_emailPasswordMap.find(email) == m_emailPasswordMap.end())
		return AsciiString::TheEmptyString;
	return m_emailPasswordMap[email];
}
