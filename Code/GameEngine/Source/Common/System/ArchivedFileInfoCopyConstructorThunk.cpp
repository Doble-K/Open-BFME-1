// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /ICode/Libraries/Source/WWVegas/WWLib

#include "Common/AsciiString.h"

typedef unsigned int UnsignedInt;

class ArchivedFileInfo
{
public:
    AsciiString m_filename;
    AsciiString m_archiveFilename;
    UnsignedInt m_offset;
    UnsignedInt m_size;

    ArchivedFileInfo(const ArchivedFileInfo &that);
};

// ??0ArchivedFileInfo@@QAE@ABV0@@Z
ArchivedFileInfo::ArchivedFileInfo(const ArchivedFileInfo &that) :
    m_filename(that.m_filename),
    m_archiveFilename(that.m_archiveFilename)
{
    m_offset = that.m_offset;
    m_size = that.m_size;
}
