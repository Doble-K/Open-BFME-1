// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/iniexception /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The CloudBreakEffect block -- BFME-only, one AsciiString naming the sunbeam
// object. Same override bookkeeping as GlowEffect and friends in Drawable.cpp:
// copy saved into active, parse over active, write back only when this is not an
// override load. Two load types suppress the write-back, INI_LOAD_CREATE_OVERRIDES
// and BFME's fourth type with value 4.
//
// It then pokes the cloud system so the change takes effect, through vtable slot
// 9 as a tail call. Names: the block keyword gives the settings class; the two
// statics and the system pointer at 0x012F10F0 have no recoverable names, so
// those are ours. All three are DIR32 slots the verifier fills in from the
// target, so none of them affect the bytes.
//
// CloudEffect next door is the same shape and stays unclaimed: its settings
// struct is 0x90 bytes with non-trivial members, so the copy goes through a
// compiler-generated operator= that nothing in the image names, and an
// unresolved REL32 does not verify.
#include "PreRTS.h"
#include "Common/INI.h"

static INILoadType retailLoadType( const INI *ini )
{
	struct RetailINI { char m_pad[ 0x08 ]; INILoadType m_loadType; };
	return reinterpret_cast<const RetailINI *>( ini )->m_loadType;
}

static const INILoadType INI_LOAD_BFME_TYPE_4 = (INILoadType)4;

struct CloudBreakEffect
{
	AsciiString m_sunbeamObject;		// 0x00  SunbeamObject

	static const FieldParse m_fieldParseTable[];
};

class CloudSystem
{
public:
	virtual void _bfme_pad_0() = 0;
	virtual void _bfme_pad_1() = 0;
	virtual void _bfme_pad_2() = 0;
	virtual void _bfme_pad_3() = 0;
	virtual void _bfme_pad_4() = 0;
	virtual void _bfme_pad_5() = 0;
	virtual void _bfme_pad_6() = 0;
	virtual void _bfme_pad_7() = 0;
	virtual void _bfme_pad_8() = 0;
	virtual void settingsChanged() = 0;		// slot 9, +0x24
};

extern CloudBreakEffect TheCloudBreakEffectSaved;		// 0x012F10F4
extern CloudBreakEffect TheCloudBreakEffectActive;		// 0x012F10F8
extern CloudSystem *TheCloudSystem;						// 0x012F10F0

void parseCloudBreakEffect( INI *ini )
{
	TheCloudBreakEffectActive = TheCloudBreakEffectSaved;
	ini->initFromINI( &TheCloudBreakEffectActive, CloudBreakEffect::m_fieldParseTable );

	const INILoadType loadType = retailLoadType( ini );
	if( loadType != INI_LOAD_CREATE_OVERRIDES && loadType != INI_LOAD_BFME_TYPE_4 )
		TheCloudBreakEffectSaved = TheCloudBreakEffectActive;

	if( TheCloudSystem )
		TheCloudSystem->settingsChanged();
}
