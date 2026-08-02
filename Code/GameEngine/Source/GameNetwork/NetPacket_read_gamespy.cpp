// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// The two GameSpy stats-authkey readers.
//
// Each string arrives NUL-terminated rather than length-prefixed, so both copy
// byte by byte into a 256-byte buffer and hand the result to an out-of-line
// setter by value.
//
// They are in a translation unit of their own, and StringBase here declares no
// default constructor, because that is what decides the instruction order
// around the temporary: with an inline default constructor in scope MSVC loads
// the constructor's `this` before recording the temporary for unwinding, and
// retail does it the other way round. The chat readers need the default
// constructor -- retail inlines it into them -- so they cannot share this file.

#include <string.h>
#include <wchar.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

static int stringLength(const char *s)
{
	return (int)strlen(s);
}

static int stringLength(const unsigned short *s)
{
	return (int)wcslen((const wchar_t *)s);
}

template <typename T>
class StringBase
{
	friend class BFMENetRequestGameSpyStatsAuthKeyCommandMsg;
	friend class BFMENetGameSpyStatsAuthKeyCommandMsg;
	friend class NetPacket;

public:
	void set(const T *str) { set(str, stringLength(str)); }
	void set(const T *str, int len);
	void set(const StringBase<T> &src);
	StringBase<T> &operator=(const StringBase<T> &src) { set(src); return *this; }

private:
	StringBase(const T *str);
	StringBase(const StringBase<T> &src);
	~StringBase();

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

typedef StringBase<char> AsciiString;
typedef StringBase<unsigned short> UnicodeString;

class NetCommandMsg
{
public:
	NetCommandMsg();
	virtual ~NetCommandMsg();

protected:
	UnsignedInt m_timestamp;						// this+0x04
	UnsignedInt m_executionFrame;					// this+0x08
	UnsignedInt m_playerID;							// this+0x0C
	UnsignedShort m_id;								// this+0x10
	Int m_commandType;								// this+0x14
	Int m_referenceCount;							// this+0x18
};

class BFMENetRequestGameSpyStatsAuthKeyCommandMsg : public NetCommandMsg
{
public:
	BFMENetRequestGameSpyStatsAuthKeyCommandMsg();
	void setText1C(AsciiString text);

	AsciiString m_text1C;							// this+0x1C
};

class BFMENetGameSpyStatsAuthKeyCommandMsg : public NetCommandMsg
{
public:
	BFMENetGameSpyStatsAuthKeyCommandMsg();
	void setText1C(AsciiString text);
	void setText20(AsciiString text);

	AsciiString m_text1C;							// this+0x1C
	AsciiString m_text20;							// this+0x20
};

class NetPacket
{
protected:
	static NetCommandMsg *readRequestGameSpyStatsAuthKeyMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readGameSpyStatsAuthKeyMessage(UnsignedByte *data, Int &i);
};


// ?readRequestGameSpyStatsAuthKeyMessage@NetPacket@@KAPAVNetCommandMsg@@PAEAAH@Z present-unmatched
NetCommandMsg *NetPacket::readRequestGameSpyStatsAuthKeyMessage(UnsignedByte *data, Int &i)
{
	BFMENetRequestGameSpyStatsAuthKeyCommandMsg *msg = new BFMENetRequestGameSpyStatsAuthKeyCommandMsg;

	char text[256];
	char *c = text;

	while (data[i] != 0) {
		*c = data[i];
		++c;
		++i;
	}
	*c = 0;
	++i;
	msg->setText1C(text);

	return msg;
}

// ?readGameSpyStatsAuthKeyMessage@NetPacket@@KAPAVNetCommandMsg@@PAEAAH@Z present-unmatched
NetCommandMsg *NetPacket::readGameSpyStatsAuthKeyMessage(UnsignedByte *data, Int &i)
{
	BFMENetGameSpyStatsAuthKeyCommandMsg *msg = new BFMENetGameSpyStatsAuthKeyCommandMsg;

	char text[256];
	char *c = text;

	while (data[i] != 0) {
		*c = data[i];
		++c;
		++i;
	}
	*c = 0;
	++i;
	msg->setText1C(text);

	// One buffer, refilled: retail's frame is 0x104 bytes, which is the single
	// 256-byte run plus the temporary AsciiString.
	c = text;

	while (data[i] != 0) {
		*c = data[i];
		++c;
		++i;
	}
	*c = 0;
	++i;
	msg->setText20(text);

	return msg;
}
