// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4

#include "PreRTS.h"

#define AsciiString BFMERetailModuleInfoString
#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"
#undef AsciiString

class BFMERetailModuleInfoString
{
public:
	BFMERetailModuleInfoString() : m_text(NULL) {}
	BFMERetailModuleInfoString(const BFMERetailModuleInfoString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~BFMERetailModuleInfoString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

private:
	char *m_text;
};

struct BFME_ModuleInfoNuggetCopyLayout
{
	BFMERetailModuleInfoString first;
	BFMERetailModuleInfoString m_moduleTag;
	const void *second;
	int interfaceMask;
	bool copiedFromDefault;
	bool inheritable;
	bool overrideableByLikeKind;
};

__declspec(noinline) void bfmeConstructModuleInfoNugget(
	BFME_ModuleInfoNuggetCopyLayout *dest,
	const BFME_ModuleInfoNuggetCopyLayout &src)
{
	std::_Construct(dest, src);
}
