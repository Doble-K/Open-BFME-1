// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// NetCommandRef::~NetCommandRef, 0x00676280, 12 bytes.
//
// Connection::doSend runs this on every command it drops -- destructor, then
// operator delete -- so it is one of the callees doSend needs named.
//
// The body is the reference's, and the whole of it: detach the message if there
// is one. Retail tail-jumps into NetCommandMsg::detach (already matched at
// 0x00673610) because that is the last statement and returns void. The
// reference's two DEBUG_ASSERTCRASH lines on m_next/m_prev compile out.
//
// m_msg is at +0, not +4: BFME's NetCommandRef is not a MemoryPoolObject, so it
// carries no vptr and every field sits four bytes lower than the reference
// header puts it. NetCommandList::removeMessage showed the same thing for
// m_next/m_prev at +4/+8.
//
// Declared locally: the real GameNetwork/NetCommandRef.h derives the class from
// MemoryPoolObject, and any file under reference/shims/ forces the full gate.

class NetCommandMsg
{
public:
	void detach();
};

class NetCommandRef
{
public:
	~NetCommandRef();

private:
	NetCommandMsg *m_msg;							// this+0x00
};

NetCommandRef::~NetCommandRef()
{
	if (m_msg != 0)
	{
		m_msg->detach();
	}
}
