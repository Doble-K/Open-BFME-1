// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /ICode/Libraries/Source/WWVegas/WWLib

#include "Common/AsciiString.h"

typedef bool Bool;

class WindowLayout
{
public:
    virtual void unused00();
    virtual void unused01();
    virtual void unused02();
    virtual void unused03();
    virtual void hide(Bool hide);
};

class GameWindowManager
{
public:
    virtual void unused00(); virtual void unused01(); virtual void unused02();
    virtual void unused03(); virtual void unused04(); virtual void unused05();
    virtual void unused06(); virtual void unused07(); virtual void unused08();
    virtual void unused09(); virtual void unused10(); virtual void unused11();
    virtual void unused12(); virtual void unused13(); virtual void unused14();
    virtual void unused15(); virtual void unused16(); virtual void unused17();
    virtual void unused18(); virtual void unused19(); virtual void unused20();
    virtual void unused21(); virtual void unused22(); virtual void unused23();
    virtual void unused24(); virtual void unused25(); virtual void unused26();
    virtual void unused27(); virtual void unused28(); virtual void unused29();
    virtual void unused30(); virtual void unused31(); virtual void unused32();
    virtual void unused33(); virtual void unused34(); virtual void unused35();
    virtual void unused36(); virtual void unused37(); virtual void unused38();
    virtual void unused39();
    virtual void clearTabList();
};

class Shell
{
public:
    void shutdownComplete(WindowLayout *layout, Bool impendingPush);
    void push(char *screen);
    void reverseAnimatewindow();
};

class GameSpyLoginPreferences
{
public:
    void write();
};

class GameWindowTransitionsHandler
{
public:
    void reverse(AsciiString groupName);
};

extern GameWindowManager *TheWindowManager;
extern Shell *TheShell;
extern GameWindowTransitionsHandler *TheTransitionHandler;

static Bool isShuttingDown;
static Bool loggedInOK;
static GameSpyLoginPreferences *loginPref;
static char *nextScreen;

// Retail spells this `static void shutdownComplete(WindowLayout *)`, but that
// name is file-scoped and ~30 menu TUs each define their own. symbols.csv is a
// flat name->address map with no room for two meanings of one key, so the
// resolver would pick whichever copy happened to reproduce a displacement
// first. Spelled per-TU here so the pin is unambiguous; retail symbol is
// ?shutdownComplete@@YAXPAVWindowLayout@@@Z in WOLLoginMenu.cpp @0x004FFA40.
static __declspec(noinline) void shutdownCompleteWOLLoginMenu(WindowLayout *layout)
{
    isShuttingDown = false;
    layout->hide(true);
    TheShell->shutdownComplete(layout, nextScreen != 0);

    if (nextScreen != 0)
    {
        if (loginPref != 0)
        {
            loginPref->write();
            delete loginPref;
            loginPref = 0;
        }
        TheShell->push(nextScreen);
    }
    else if (loginPref != 0)
    {
        loginPref->write();
        delete loginPref;
        loginPref = 0;
    }

    nextScreen = 0;
}

// ?WOLLoginMenuShutdown@@YAXPAVWindowLayout@@PAX@Z
void WOLLoginMenuShutdown(WindowLayout *layout, void *userData)
{
    isShuttingDown = true;
    loggedInOK = false;
    TheWindowManager->clearTabList();

    Bool popImmediate = *(Bool *)userData;
    if (popImmediate)
    {
        shutdownCompleteWOLLoginMenu(layout);
        return;
    }

    TheShell->reverseAnimatewindow();
    TheTransitionHandler->reverse("GameSpyLoginProfileFade");
}
