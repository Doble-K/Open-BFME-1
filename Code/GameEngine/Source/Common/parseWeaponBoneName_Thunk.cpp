// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift parseWeaponBoneName to clean C++.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class INI
{
public:
	const char *getNextToken(const char *separators = 0);
	AsciiString getNextAsciiString();
	static int scanIndexList(const char *token, const char *const *names);
};

class ModelConditionInfo
{
public:
	void addPublicBone(const AsciiString &boneName) const;
};

extern const char *const TheWeaponSlotTypeNames[];

// ?parseWeaponBoneName@@YAXPAVINI@@PAX1PBX@Z
void parseWeaponBoneName(INI *ini, void *instance, void *store, const void *)
{
	ModelConditionInfo *self = (ModelConditionInfo *)instance;
	AsciiString *bones = (AsciiString *)store;
	int slot = INI::scanIndexList(ini->getNextToken(), TheWeaponSlotTypeNames);
	bones[slot] = ini->getNextAsciiString();
	bones[slot].toLower();
	if (bones[slot].isNone())
		bones[slot].clear();

	if (self)
		self->addPublicBone(bones[slot]);
}
