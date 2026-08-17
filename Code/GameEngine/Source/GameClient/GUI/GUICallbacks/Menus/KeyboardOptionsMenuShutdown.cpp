// cl: /DNDEBUG /MD /EHs-c-

// FILE: KeyboardOptionsMenuShutdown.cpp //////////////////////////////////////
//
// KeyboardOptionsMenuShutdown, retail 0x004C9060.
//
// No port of KeyboardOptionsMenu.cpp exists under Code/.  The body is Zero
// Hour's two lines and compiles to thirty bytes.
//
// Six byte-identical copies of these thirty bytes sit in the image -- one per
// menu compiland, since the linker did not fold them -- so the bytes cannot
// say which file this one is.  What does: 0x004C9060 sits 0x230 below
// 0x004C9290 and 0x330 below 0x004C9390, both of which push
// "KeyboardOptionsMenu.wnd:ButtonBack" and "KEYBOARD:Shift+" and so belong to
// that compiland.  The other five are left unclaimed rather than guessed at;
// DownloadMenuShutdown, the nearest already-landed one, is at 0x004C76F0 and is
// 64 bytes, which is what ruled the obvious neighbour out.
//
// WindowLayout::hide is virtual in BFME at vtable slot 0x10 -- the fifth file
// today to say so -- and Shell::shutdownComplete takes a second argument the
// reference does not have; retail passes FALSE.
//
///////////////////////////////////////////////////////////////////////////////

typedef bool Bool;

class WindowLayout;

// Five-slot shim: only the last of these is claimed, and only its offset.
class BfmeVirtualHideLayout
{
public:
	virtual void slot0() = 0;
	virtual void slot4() = 0;
	virtual void slot8() = 0;
	virtual void slotC() = 0;
	virtual void hide( Bool immediate ) = 0;
};

class Shell
{
public:
	void shutdownComplete( WindowLayout *layout, Bool impending );
};

extern Shell *TheShell;

void KeyboardOptionsMenuShutdown( WindowLayout *layout, void *userData )
{
		// hide menu
	((BfmeVirtualHideLayout *)layout)->hide( true );

	// our shutdown is complete
	TheShell->shutdownComplete( layout, false );
}
