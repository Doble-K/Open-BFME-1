// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// The two chat readers.
//
// Chat text is length-prefixed rather than NUL-terminated: one byte of
// character count, then that many UnsignedShorts. The terminator is written
// afterwards, so the buffer holds 256 characters and never a 257th.
//
// Both are retail's instruction for instruction apart from one adjacent pair:
// retail records the temporary for unwinding and then loads the constructor's
// `this`, and this source emits the two the other way round. The same pair is
// the only difference in the GameSpy readers next door, and it is specific to
// handing a temporary to an out-of-line function by value -- the file readers
// build the same temporary and match exactly, because their setter is inline
// and no by-value argument crosses a call boundary.
//
// Ruled out so far: every /O, /G and /EH flag combination the compiler accepts;
// declaring the setter, the constructor or the destructor nothrow; removing the
// copy constructor declaration; reordering the declarations, the members and
// the functions in the file; naming the temporary; walking the buffer by index
// instead of by pointer; and making the string a plain class rather than the
// template instantiation.

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
	friend class NetDisconnectChatCommandMsg;
	friend class NetChatCommandMsg;
	friend class NetPacket;

public:
	void set(const T *str) { set(str, stringLength(str)); }
	void set(const T *str, int len);
	void set(const StringBase<T> &src);
	StringBase<T> &operator=(const StringBase<T> &src) { set(src); return *this; }

private:
	StringBase() { m_data = 0; }
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

class NetDisconnectChatCommandMsg : public NetCommandMsg
{
public:
	NetDisconnectChatCommandMsg();
	void setText(UnicodeString text);

	UnicodeString m_text;							// this+0x1C
};

class NetChatCommandMsg : public NetCommandMsg
{
public:
	NetChatCommandMsg();
	void setText(UnicodeString text);
	void setPlayerMask(Int playerMask);

	UnicodeString m_text;							// this+0x1C
	Int m_playerMask;								// this+0x20
};

class NetPacket
{
protected:
	static NetCommandMsg *readDisconnectChatMessage(UnsignedByte *data, Int &i);
	static NetCommandMsg *readChatMessage(UnsignedByte *data, Int &i);
};

// ?readDisconnectChatMessage@NetPacket@@KAPAVNetCommandMsg@@PAEAAH@Z present-unmatched
NetCommandMsg *NetPacket::readDisconnectChatMessage(UnsignedByte *data, Int &i)
{
	NetDisconnectChatCommandMsg *msg = new NetDisconnectChatCommandMsg;

	UnsignedShort text[256];
	UnsignedByte length;
	memcpy(&length, data + i, sizeof(UnsignedByte));
	++i;
	memcpy(text, data + i, length * sizeof(UnsignedShort));
	i += length * sizeof(UnsignedShort);
	text[length] = 0;

	UnicodeString unitext;
	unitext.set(text);

	msg->setText(unitext);
	return msg;
}

// ?readChatMessage@NetPacket@@KAPAVNetCommandMsg@@PAEAAH@Z present-unmatched
NetCommandMsg *NetPacket::readChatMessage(UnsignedByte *data, Int &i)
{
	NetChatCommandMsg *msg = new NetChatCommandMsg;

	UnsignedShort text[256];
	UnsignedByte length;
	Int playerMask;
	memcpy(&length, data + i, sizeof(UnsignedByte));
	++i;
	memcpy(text, data + i, length * sizeof(UnsignedShort));
	i += length * sizeof(UnsignedShort);
	text[length] = 0;
	memcpy(&playerMask, data + i, sizeof(Int));
	i += sizeof(Int);

	UnicodeString unitext;
	unitext.set(text);

	msg->setText(unitext);
	msg->setPlayerMask(playerMask);
	return msg;
}
