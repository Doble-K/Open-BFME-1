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

// Only the shape findArmorTemplate needs. The template's real size does not
// enter this function: retail reaches the mapped value at node+8 regardless.
class ArmorTemplate
{
public:
	Real m_damageCoefficient[16];
};

class ArmorStore : public SubsystemInterface
{
public:
	void init() {}
	void reset() {}
	void update() {}
	const ArmorTemplate *findArmorTemplate(AsciiString name) const;
private:
	typedef std::hash_map< NameKeyType, ArmorTemplate, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> > ArmorTemplateMap;
	ArmorTemplateMap m_armorTemplates;
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
