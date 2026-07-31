// cl: /ICode/Libraries/Source/WWVegas/WWLib
#include "string_base.h"

extern "C" unsigned int __cdecl strlen(const char *str);

static const char replayExtention[] = ".rep";
static const char lastReplayFileName[] = "00000000";
static const char replayDir[] = "Replays\\";

class AsciiString {
public:
    AsciiString() { base()->StringBase<char>::StringBase(); }
    AsciiString(const AsciiString &that) { base()->StringBase<char>::StringBase(*that.base()); }
    AsciiString(const char *str) { base()->StringBase<char>::StringBase(str); }
    ~AsciiString() { base()->releaseBuffer(); }

    void concat(const char *str)
    {
        base()->concat(str, strlen(str));
    }

private:
    StringBase<char> *base() { return (StringBase<char> *)this; }
    const StringBase<char> *base() const { return (const StringBase<char> *)this; }

private:
    StringBase<char>::Header *m_data;
};

class GlobalData {
public:
    AsciiString getPath_UserData() const;
};

extern GlobalData *TheWritableGlobalData;
#define TheGlobalData ((const GlobalData *)TheWritableGlobalData)

enum RecorderModeType {
    RECORDERMODETYPE_RECORD,
    RECORDERMODETYPE_PLAYBACK,
    RECORDERMODETYPE_NONE
};

class RecorderClass {
public:
    char m_pad[0x18];
    RecorderModeType m_mode;
    static AsciiString getReplayDir();
    static AsciiString getReplayExtention();
    AsciiString getLastReplayFileName();
    RecorderModeType getMode();
};

AsciiString RecorderClass::getReplayDir()
{
    const char *dir = replayDir;
    AsciiString tmp = TheGlobalData->getPath_UserData();
    tmp.concat(dir);
    return tmp;
}

AsciiString RecorderClass::getReplayExtention()
{
    return AsciiString(replayExtention);
}

AsciiString RecorderClass::getLastReplayFileName()
{
    return AsciiString(lastReplayFileName);
}

RecorderModeType RecorderClass::getMode()
{
    return m_mode;
}
