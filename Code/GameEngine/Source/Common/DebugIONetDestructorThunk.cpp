// cl: /DNDEBUG /MD /EHa /Oy-
// Open-BFME5: lift DebugIONet dtor __emit thunk to clean C++. Retail keeps
// an EBP frame (/Oy-): stores its own vtable at entry, FreeConsole() when the
// byte flag at this+4 is set, then runs the inlined base dtor (base vtable
// store) on the normal and unwind paths.

extern "C" __declspec(dllimport) void __stdcall FreeConsole(void);

class DebugIONetBase
{
public:
	virtual ~DebugIONetBase() {}
};

class DebugIONet : public DebugIONetBase
{
public:
	virtual ~DebugIONet();

private:
	bool m_allocatedConsole;
};

// ??1DebugIONet@@UAE@XZ
DebugIONet::~DebugIONet()
{
	if (m_allocatedConsole) {
		FreeConsole();
	}
}
