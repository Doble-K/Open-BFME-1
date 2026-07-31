// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/namekeygenerator /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// ArmorStore -- the subsystem SubsystemLegend.ini feeds Armor.ini to. Ported
// from the Zero Hour reference (GeneralsMD/.../GameLogic/Object/Armor.cpp)
// against the NameKeyGenerator shim, because this TU needs the same AsciiString
// ABI that file established: an inline str() and an out-of-line release.
//
// Entry point into it is INI::parseArmorTemplate (0x000BAE50), which reads
// TheArmorStore from 0x012EF4E8 and calls findArmorTemplate at 0x001B05E0.
#include "PreRTS.h"
#include "Common/NameKeyGenerator.h"
#include "Common/STLTypedefs.h"

// DAMAGE_NUM_TYPES is 24 in BFME, not ZH's count: ArmorStore::parseArmorDefinition
// inlines clear() as exactly 24 stores of 1.0f (0x3F800000) at +0x00..+0x5C.
enum { DAMAGE_NUM_TYPES = 24 };

class ArmorTemplate
{
public:
	void clear();
	static void parseArmorCoefficients( INI* ini, void *instance, void *store, const void* userData );
private:
	Real m_damageCoefficient[DAMAGE_NUM_TYPES];
	friend class ArmorStore;
};

// ?clear@ArmorTemplate@@QAEXXZ present-unmatched
// Retail always inlines this (parseArmorDefinition carries its 24 stores), so
// there is no standalone body to claim; it is here because that caller needs it.
void ArmorTemplate::clear()
{
	for (Int i = 0; i < DAMAGE_NUM_TYPES; ++i)
		m_damageCoefficient[i] = 1.0f;
}

class ArmorStore;
extern ArmorStore *TheArmorStore;		// 0x012EF4E8

class ArmorStore : public SubsystemInterface
{
public:
	void init() {}
	void reset() {}
	void update() {}
	const ArmorTemplate *findArmorTemplate(AsciiString name) const;
	static void parseArmorDefinition(INI *ini);
private:
	typedef std::hash_map< NameKeyType, ArmorTemplate, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> > ArmorTemplateMap;
	ArmorTemplateMap m_armorTemplates;		// +0x08
};

// ?findArmorTemplate@ArmorStore@@QBEPBVArmorTemplate@@VAsciiString@@@Z
// nameToKey is called through the const char* overload, not the AsciiString
// one: retail inlines AsciiString::str() here (m_text ? m_text+8 : "") and
// passes the result, which is why this reads name.str() explicitly.
const ArmorTemplate *ArmorStore::findArmorTemplate(AsciiString name) const
{
	NameKeyType namekey = TheNameKeyGenerator->nameToKey(name.str());
	ArmorTemplateMap::const_iterator it = m_armorTemplates.find(namekey);
	if (it == m_armorTemplates.end())
		return NULL;
	return &(*it).second;
}

// ?parseArmorDefinition@ArmorStore@@SAXPAVINI@@@Z present-unmatched
// 143 of retail's 144 bytes at 0x001B09B0. The one byte that differs is the base
// register of the LAST of the 24 stores: retail peels it out and issues it
// through eax (the untouched operator[] result) interleaved with the FieldParse
// push, where we keep using the edx copy the other 23 went through -- 0x48 vs
// 0x4A at +131. Unmoved by loop form (for/while/reverse/pointer-walk), by
// clear() being inline or its own call, by ref vs pointer, or by the table being
// function-static vs file-scope. Same scheduling family as the latch divergences
// in docs/lessons.md.
//
// The "Armor" INI block: name the armor, default every coefficient to 1.0, then
// let the field parser overwrite the ones the block lists.
/*static*/ void ArmorStore::parseArmorDefinition(INI *ini)
{
	static const FieldParse myFieldParse[] =
	{
		{ "Armor", ArmorTemplate::parseArmorCoefficients, NULL, 0 }
	};

	const char *c = ini->getNextToken();
	NameKeyType key = TheNameKeyGenerator->nameToKey(c);
	ArmorTemplate& armorTmpl = TheArmorStore->m_armorTemplates[key];
	armorTmpl.clear();
	ini->initFromINI(&armorTmpl, myFieldParse);
}
