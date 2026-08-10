// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/languagefilter /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib

#include "Common/UnicodeString.h"

enum SlotState
{
	SLOT_OPEN,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_PLAYER
};

class GameSlot
{
public:
	virtual void reset(void) = 0;	// vptr; m_state therefore lands at offset 4
	UnicodeString getName(void) const;
protected:
	SlotState m_state;
};

class LANGameSlot : public GameSlot
{
public:
	Bool isUser(UnicodeString userName);
};

// UnicodeString::compareNoCase is inline in the shim and folds to _wcsicmp.
// Retail calls StringBase<G>::compareNoCase out of line, so go through the
// base the same way the shim routes the copy ctor.
static int compareNoCase(const UnicodeString& self, const UnicodeString& other)
{
	return ((const StringBase<wchar_t> *)&self)->compareNoCase(
		*(const StringBase<wchar_t> *)&other);
}

// ?isUser@LANGameSlot@@QAE_NVUnicodeString@@@Z
Bool LANGameSlot::isUser(UnicodeString userName)
{
	return (m_state == SLOT_PLAYER && !compareNoCase(userName, getName()));
}
