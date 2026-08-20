// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#include "GameLogic/Module/UpdateModule.h"

// GateProxyBehavior is a BFME-only module whose original header is not in the
// vendored Generals tree.  The factory registration names it directly, and its
// retail constructor calls the GateOpenAndCloseBehavior base constructor.  Keep
// the recovered ABI layout local to this TU until the module header is restored.
class __declspec(novtable) GateOpenAndCloseBehavior : public UpdateModule
{
public:
	GateOpenAndCloseBehavior(Thing *, const ModuleData *);
	virtual UpdateSleepTime update();
	virtual DisabledMaskType getDisabledTypesToProcess() const;

private:
	unsigned char m_unrecoveredFields[0x2c];
};

class GateProxyBehavior : public GateOpenAndCloseBehavior
{
public:
	GateProxyBehavior(Thing *, const ModuleData *);
	virtual UpdateSleepTime update();
	virtual DisabledMaskType getDisabledTypesToProcess() const;

private:
	void *m_gateProxy;
};

// ??0GateProxyBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
GateProxyBehavior::GateProxyBehavior(Thing *thing, const ModuleData *moduleData)
	: GateOpenAndCloseBehavior(thing, moduleData), m_gateProxy(0)
{
}
