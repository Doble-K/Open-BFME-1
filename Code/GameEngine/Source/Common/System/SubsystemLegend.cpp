// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// SubsystemLegend — a BFME-only engine subsystem with no ZH counterpart.
// GameEngine::init registers it as "TheSubsystemLegend" (global 0x0134C6C4)
// and feeds it Data\INI\Default\SubsystemLegend.ini; the initSubsystem site
// (0x00079272) news 0x0c bytes and calls the ctor matched below.
//
// Layout recovered from retail, all offsets proven by the bodies here:
//   +0x00  SubsystemInterface base (vptr; AsciiString m_name at +0x04 — the
//          base ctor 0x009A1A30 writes exactly those two words)
//   +0x08  std::list<SubsystemLegendEntry> m_entries
// The element is 0x30 bytes (list node 0x38, the size the ctor and dtor
// allocate/free). Its dtor (0x00078210) destroys, in reverse declaration order,
// +0x2c, +0x1c, +0x10, +0x04, +0x00 — which pins the field layout below; the
// copy ctor (0x009A12B0) confirms it independently, copying +0x28 as a plain
// dword between two StringBase copy-ctor calls.
//
// The field NAMES come from the retail FieldParse table at 0x011415C0, which
// parseLoadSubsystem below hands to INI::initFromINI: each row carries the INI
// keyword and the member offset it writes. The INI block keyword itself is
// "LoadSubsystem" (block table row at 0x00ED7768), so an entry describes one
// engine subsystem's INI/asset load set, not a "legend" — the class name comes
// from the two "SubsystemLegend" strings in the exe and is kept for continuity.
//
#define __PLACEMENT_VEC_NEW_INLINE
#include <list>		// before PreRTS.h so STLport node_alloc is used (not NEWALLOC)
#include "PreRTS.h"
#include "Common/INI.h"

// Retail destroys both member types out-of-line, while the ZH AsciiString header
// and STLport's vector inline their release paths — that inlining is what blew
// the element dtor's register allocation. These stand-ins carry the same size
// and a declared-but-undefined dtor, so the call survives to be pinned in
// reverse/symbols.csv against the retail body it folds to.
// findEntry inlines the string compare, which pins the retail buffer header: a
// 16-bit length at +0x04 and the characters at +0x08.
struct BfmeLegendStringData
{
	Int				m_refCount;		// +0x00
	UnsignedShort	m_len;			// +0x04
	UnsignedShort	m_allocated;	// +0x06
	char			m_chars[1];		// +0x08
};

struct BfmeLegendString			// AsciiString, 4B  -> dtor 0x00887940
{
	BfmeLegendStringData *m_data;
	BfmeLegendString() { m_data = 0; }
	BfmeLegendString(const char *s);
	BfmeLegendString(const BfmeLegendString &s);
	BfmeLegendString &operator=(const BfmeLegendString &s);
	~BfmeLegendString();
	void clear();

	Int compare(const BfmeLegendString &other) const
	{
		Int otherLen = other.m_data ? other.m_data->m_len : 0;
		const char *otherChars = other.m_data ? other.m_data->m_chars : "";
		Int len = m_data ? m_data->m_len : 0;
		const char *chars = m_data ? m_data->m_chars : "";
		Int n = len < otherLen ? len : otherLen;
		Int result = memcmp(chars, otherChars, n);
		if (result != 0)
			return result;
		return len - otherLen;
	}
};

// STLport parks a vector's end-of-storage pointer inside an _STLP_alloc_proxy
// subobject rather than storing it directly. That extra construction boundary is
// load-bearing: without it the default ctor below schedules its EH-state store two
// instructions early, and the entry ctor misses by exactly that one instruction.
struct BfmeLegendAllocProxy		// _STLP_alloc_proxy<AsciiString*, ...>, 4B
{
	void *m_data;
	BfmeLegendAllocProxy(void *p) : m_data(p) {}
};

struct BfmeLegendStringVec		// std::vector<AsciiString>, 12B -> dtor 0x000658A0
{
	void *m_start, *m_finish;
	BfmeLegendAllocProxy m_endOfStorage;
	BfmeLegendStringVec() : m_start(0), m_finish(0), m_endOfStorage(0) {}
	BfmeLegendStringVec(const BfmeLegendStringVec &v);
	~BfmeLegendStringVec();
	void erase(void *first, void *last);
	void clear() { erase(m_start, m_finish); }
};

struct SubsystemLegendEntry
{
	BfmeLegendString			m_name;				// +0x00  the block's subsystem name
	BfmeLegendStringVec			m_initFile;			// +0x04  "InitFile"
	BfmeLegendStringVec			m_initPath;			// +0x10  "InitPath"
	BfmeLegendStringVec			m_extension;		// +0x1c  "Extension"
	Int							m_loader;			// +0x28  "Loader" (lookup list 0x012D7758)
	BfmeLegendString			m_initFileDebug;	// +0x2c  "InitFileDebug" / "ExcludePathDebug"

	SubsystemLegendEntry();
};

// ??0SubsystemLegendEntry@@QAE@XZ
SubsystemLegendEntry::SubsystemLegendEntry()
{
	m_name.clear();
	m_initFile.clear();
	m_initPath.clear();
	m_extension.clear();
	m_loader = 0;
	m_initFileDebug.clear();
}

class SubsystemLegend : public SubsystemInterface
{
public:
	SubsystemLegend();
	virtual ~SubsystemLegend();

	virtual void init();
	virtual void reset();
	virtual void update();

	Int getEntryCount() const;
	SubsystemLegendEntry *findEntry(BfmeLegendString name);
	void addEntry(const SubsystemLegendEntry &entry);
	void parseLoadSubsystem(INI *ini);

private:
	std::list<SubsystemLegendEntry> m_entries;	// +0x08
};

extern SubsystemLegend *TheSubsystemLegend;		// 0x0134C6C4

// Retail's table lives at 0x011415C0 and is not ported yet; its six rows are, in
// order: InitFile/InitPath/Extension -> parseAsciiStringVectorAppend at +0x04/+0x10/
// +0x1c, Loader -> parseLookupList at +0x28 (list 0x012D7758), then InitFileDebug
// and ExcludePathDebug -> parseAsciiString, both at +0x2c. Those offsets are what
// name the entry fields below.
extern const FieldParse TheSubsystemLegendFieldParse[];

// ??0SubsystemLegend@@QAE@XZ
SubsystemLegend::SubsystemLegend()
{
}

// ??1SubsystemLegend@@UAE@XZ
SubsystemLegend::~SubsystemLegend()
{
	m_entries.clear();
}

// ?init@SubsystemLegend@@UAEXXZ
void SubsystemLegend::init()
{
	m_entries.clear();
}

// ?reset@SubsystemLegend@@UAEXXZ
void SubsystemLegend::reset()
{
	m_entries.clear();
}

// ?update@SubsystemLegend@@UAEXXZ
void SubsystemLegend::update()
{
}

// ?getEntryCount@SubsystemLegend@@QBEHXZ
Int SubsystemLegend::getEntryCount() const
{
	return m_entries.size();
}

// ?findEntry@SubsystemLegend@@QAEPAUSubsystemLegendEntry@@UBfmeLegendString@@@Z present-unmatched
// The ledger row for 0x009A11A0 points at Code/masm_dumps/SubsystemLegend_findEntry_9A11A0.asm,
// so the marker here is deliberate: those 264 bytes are owned by another file.
// This body still belongs in this TU and must stay — it is the only thing that
// instantiates _List_iterator<Entry>::operator* and operator-> (0x009A1090 and
// 0x009A10A0, matched from here), which is itself evidence that retail's TU
// carries findEntry as C++ rather than as a blob.
//
// It compiles to 262 of the 264 retail bytes. The two that differ are one
// register in the loop latch at 0x009A123C: retail reloads the spilled `this`
// into eax (reading [eax+8]), MSVC 7.1 here picks ecx. Frame, EH states, the
// inlined StringBase compare and both epilogues are byte-identical.
//
// The eax form is not beyond this toolchain — ?update@ControlBarScheme@@QAEXXZ
// (0x004AD484) is matched from C++ and emits it — but there the loop body is
// call-free, so the iterator lives in ecx and pushes `this` into eax. Ours has
// calls, so the iterator takes ebp, leaves ecx free, and MSVC takes it. Across
// the image the same ebp-iterator-with-calls latch resolves eax x3 / ecx x2 /
// edx x1, so retail's choice here is close to a coin flip, not a rule.
//
// ~190 source variants all land on exactly these two bytes: loop form, compare
// placement/orientation/spelling, all 24 declaration orders, member vs free vs
// template vs out-of-line-inline definition, __thiscall/__fastcall/__cdecl, with
// and without the ZH base class, iterator-internal (_M_node) comparisons, and CFG
// reshapes (switch, goto, empty else). So did every flag (/G3../G7 /GB /Ox /Og
// /Ot /Os /Oy /Ob0..2 /Oa /Ow /Oi- /arch:SSE /arch:SSE2 /Zi /Z7 /GX /GR /Gm /Gf
// /Gz /GT /Zp1 /Op) and every STLport config macro. An isolated reproducer with
// the same frame stays on ecx even with three extra loop-carried values competing
// for it. Delete the .asm and repoint the row the day that gap closes.
SubsystemLegendEntry *SubsystemLegend::findEntry(BfmeLegendString name)
{
	std::list<SubsystemLegendEntry>::iterator it;
	for (it = m_entries.begin(); it != m_entries.end(); ++it)
	{
		BfmeLegendString entryName = it->m_name;
		if (entryName.compare(name) == 0)
			return &(*it);
	}
	return NULL;
}

// ?addEntry@SubsystemLegend@@QAEXABUSubsystemLegendEntry@@@Z
void SubsystemLegend::addEntry(const SubsystemLegendEntry &entry)
{
	m_entries.push_back(entry);
}

// ?parseLoadSubsystem@SubsystemLegend@@QAEXPAVINI@@@Z
void SubsystemLegend::parseLoadSubsystem(INI *ini)
{
	BfmeLegendString name(ini->getNextToken(NULL));
	SubsystemLegendEntry entry;
	entry.m_name = name;
	ini->initFromINI(&entry, TheSubsystemLegendFieldParse);
	if (TheSubsystemLegend)
		TheSubsystemLegend->m_entries.push_back(entry);
}

// The INI block table registers this under the keyword "LoadSubsystem".
// ?parseSubsystemLegendDefinition@@YAXPAVINI@@@Z
void parseSubsystemLegendDefinition(INI *ini)
{
	if (TheSubsystemLegend)
		TheSubsystemLegend->parseLoadSubsystem(ini);
}

// The rest of this TU's COMDAT run is claimed above. Five of those bodies are
// byte-identical across two or three emitted symbols (iterator ctor/operator++/
// begin and the allocator ctor), so the linker folded them; each surplus symbol
// is carried as an --icf-owner alias on the row that kept the address, per the
// repo rule for identical-code-folded template COMDATs.
