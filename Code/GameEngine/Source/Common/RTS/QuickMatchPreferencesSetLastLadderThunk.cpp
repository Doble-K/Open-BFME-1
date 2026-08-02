// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class AsciiString;

class QuickMatchPreferences
{
public:
    void setLastLadder(const AsciiString &, unsigned short);
};

class QuickMatchPreferencesSetLastLadderShim
{
public:
    void set(const AsciiString &ladder, unsigned short port);
};

void QuickMatchPreferences::setLastLadder(const AsciiString &ladder, unsigned short port)
{
    ((QuickMatchPreferencesSetLastLadderShim *)this)->set(ladder, port);
}
