// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ conversion of GameWindowManager::winTextLabelToText.

struct StringData
{
	int RefCount;
	unsigned short Length;
};

class AsciiString
{
public:
	~AsciiString();
	bool isEmpty() const { return Data == 0 || Data->Length == 0; }

private:
	StringData *Data;
};

class UnicodeString
{
public:
	UnicodeString() : Data(0) {}
	UnicodeString(const UnicodeString &);
	~UnicodeString();
	void translate(const AsciiString &);

	static const UnicodeString TheEmptyString;

private:
	StringData *Data;
};

class GameWindowManager
{
public:
	UnicodeString winTextLabelToText(AsciiString label);
};

UnicodeString GameWindowManager::winTextLabelToText(AsciiString label)
{
	if (label.isEmpty()) {
		return UnicodeString::TheEmptyString;
	}

	UnicodeString text;
	text.translate(label);
	return text;
}
