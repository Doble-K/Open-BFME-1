#pragma once
#include <list>
#include <vector>
#include "ascii_string.h"
#include "subsystem_interface.h"

class INI;

// One "LoadSubsystem" INI block: the file set the engine loads for one named
// engine subsystem. The field names and offsets below are read straight off the
// retail FieldParse table at 0x011415C0, which parseLoadSubsystem hands to
// INI::initFromINI — each row there carries the INI keyword and the member
// offset it writes. InitFileDebug and ExcludePathDebug are two keywords onto
// the same field, which is what retail's table says.
struct SubsystemLegendEntry
{
	AsciiString					m_name;				// +0x00  the block's subsystem name
	std::vector<AsciiString>	m_initFile;			// +0x04  "InitFile"
	std::vector<AsciiString>	m_initPath;			// +0x10  "InitPath"
	std::vector<AsciiString>	m_extension;		// +0x1c  "Extension"
	Int							m_loader;			// +0x28  "Loader" (lookup list 0x012D7758)
	AsciiString					m_initFileDebug;	// +0x2c  "InitFileDebug" / "ExcludePathDebug"

	SubsystemLegendEntry();
};

// A BFME-only subsystem with no ZH counterpart. GameEngine::init registers it as
// "TheSubsystemLegend" and feeds it Data\INI\Default\SubsystemLegend.ini; the
// initSubsystem site (0x00079272) news 0x0c bytes and calls the ctor.
class SubsystemLegend : public SubsystemInterface
{
public:
	SubsystemLegend();
	virtual ~SubsystemLegend();

	virtual void init();
	virtual void reset();
	virtual void update();

	Int getEntryCount() const;
	SubsystemLegendEntry *findEntry(AsciiString name);
	void addEntry(const SubsystemLegendEntry &entry);
	void parseLoadSubsystem(INI *ini);

private:
	std::list<SubsystemLegendEntry> m_entries;	// +0x08
};

extern SubsystemLegend *TheSubsystemLegend;		// 0x0134C6C4
