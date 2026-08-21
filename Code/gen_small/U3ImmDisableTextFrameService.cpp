// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: 0x0005D6D0, and this one names itself.
//
// The two pushed literals are "IMM32.dll" and "ImmDisableTextFrameService", and
// the body is the standard late-bound call around them: LoadLibraryA, then
// GetProcAddress, call the entry point with -1 if it resolved, FreeLibrary
// either way. ImmDisableTextFrameService(-1) is the documented "switch every
// thread in this process off the IME text-frame service" call, and -1 rather
// than a real thread id is what the `push -1` fixes.
//
// The three KERNEL32 calls all go through `ff 15 [__imp_]`, so they are the
// ordinary dllimport declarations; the entry point itself is called through the
// register GetProcAddress returned, which is why the prototype has to be spelled
// out as a __stdcall function-pointer typedef.

typedef unsigned long DWORD;
typedef int BOOL;
typedef void *HMODULE;
typedef int (__stdcall *FARPROC)(void);

extern "C"
{
	__declspec(dllimport) HMODULE __stdcall LoadLibraryA(const char *fileName);
	__declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE module, const char *procName);
	__declspec(dllimport) BOOL __stdcall FreeLibrary(HMODULE module);
}

typedef BOOL(__stdcall *ImmDisableTextFrameServiceProc)(DWORD threadId);

// ?Rva0005D6D0DisableImmTextFrameService@@YAXXZ
void Rva0005D6D0DisableImmTextFrameService(void)
{
	HMODULE module = LoadLibraryA("IMM32.dll");

	if (module != 0)
	{
		ImmDisableTextFrameServiceProc disable =
			(ImmDisableTextFrameServiceProc)GetProcAddress(module, "ImmDisableTextFrameService");

		if (disable != 0)
		{
			disable((DWORD)-1);
		}

		FreeLibrary(module);
	}
}
