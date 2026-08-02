// cl: /DNDEBUG /D_STLP_USE_STATIC_LIB /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/archivefilesystem_nosubsystem /Ireference/shims/asciistring_thin /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//----------------------------------------------------------------------------
//
// Project:   Generals
//
// Module:    Game Engine Common
//
// File name: ArchiveFileSystem.cpp
//
// Created:   11/26/01 TR
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//         Includes                                                      
//----------------------------------------------------------------------------

#include "PreRTS.h"
#include "Common/ArchiveFile.h"
#include "Common/ArchiveFileSystem.h"
#include "Common/AsciiString.h"
#include "Common/PerfTimer.h"

// Retail's one-argument concats are inline wrappers over the two-argument
// StringBase body at 0x00887D60: concat(token) passes the token's characters and
// its 16-bit length, concat(BACKSLASH) passes a one-byte stack buffer and 1. The
// reference header instead inlines concat down to ensureUniqueBufferOfSize, so
// the wrappers are written out here. Declaring StringBase rather than inventing a
// name is what makes the call mangle to the body the ledger already claims.
template <class T> class StringBase
{
public:
	void concat( const T *s, int len );
};

static inline void bfmeConcat( AsciiString &s, const AsciiString &t )
{
	const char *d = *(const char * const *)&t;
	((StringBase<char> *)&s)->concat( d ? d + 8 : "",
	                                  d ? *(const unsigned short *)(d + 4) : 0 );
}

static inline void bfmeConcat( AsciiString &s, char c )
{
	((StringBase<char> *)&s)->concat( &c, 1 );
}

// BFME's find(char) scans str() to str()+length rather than calling strchr, so
// it reads the same 16-bit header field bfmeLength does. On a null buffer it
// uses the shared empty string and a zero length, which makes the range empty
// and the search fail immediately -- the same shape as retail's
// `mov eax, offset ""; xor ecx,ecx`.
static inline const char *bfmeFind( const AsciiString &s, char c )
{
	const char *d = *(const char * const *)&s;
	const char *p = d ? d + 8 : "";
	const char *end = p + (d ? *(const unsigned short *)(d + 4) : 0);

	for (; p != end; ++p) {
		if (*p == c) {
			return p;
		}
	}
	return NULL;
}

// ?doesFileExist@ArchiveFileSystem@@UBE_NPBD@Z
// Vtable slot 8 of 0x01143A08, which FileSystem::doesFileExist reaches through
// [eax+0x20]; that caller byte-matches retail, so the slot is a fact. The two
// "\\/" literals in the body are this function's two nextToken calls.
Bool ArchiveFileSystem::doesFileExist(const Char *filename) const
{
	AsciiString path = filename;
	path.toLower();
	AsciiString token;

	const ArchivedDirectoryInfo *dirInfo = &m_rootDirectory;

	path.nextToken(&token, "\\/");

	while (!bfmeFind(token, '.') || bfmeFind(path, '.'))
	{
		ArchivedDirectoryInfoMap::const_iterator tempiter = dirInfo->m_directories.find(token);
		if (tempiter != dirInfo->m_directories.end()) 
		{
			dirInfo = &tempiter->second;
			path.nextToken(&token, "\\/");
		}
		else
		{
			// the directory doesn't exist, so return false
			return FALSE;
		}
	}

	// token is the filename, and dirInfo is the directory that this file is in.
	if (dirInfo->m_files.find(token) == dirInfo->m_files.end()) {
		return FALSE;
	}
	return TRUE;
}

// BFME keeps the string length as a 16-bit field in the buffer header rather
// than measuring it, so getLength() is `movzx eax, word ptr [eax+4]` guarded by
// a null check -- not the strlen the Zero Hour header inlines.
static inline Int bfmeLength( const AsciiString &s )
{
	const char *d = *(const char * const *)&s;
	return d ? *(const unsigned short *)(d + 4) : 0;
}


#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//----------------------------------------------------------------------------
//         Externals                                                     
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Defines                                                         
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Private Types                                                     
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//         Private Data                                                     
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Public Data                                                      
//----------------------------------------------------------------------------

ArchiveFileSystem *TheArchiveFileSystem = NULL;


//----------------------------------------------------------------------------
//         Private Prototypes                                               
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Private Functions                                               
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Public Functions                                                
//----------------------------------------------------------------------------

//------------------------------------------------------
// ArchivedFileInfo
//------------------------------------------------------
ArchiveFileSystem::ArchiveFileSystem() 
{
}

ArchiveFileSystem::~ArchiveFileSystem() 
{
	ArchiveFileMap::iterator iter = m_archiveFileMap.begin();
	while (iter != m_archiveFileMap.end()) {
		ArchiveFile *file = iter->second;
		if (file != NULL) {
			delete file;
			file = NULL;
		}
		iter++;
	}
}

// ?loadIntoDirectoryTree@ArchiveFileSystem@@MAEXPBVArchiveFile@@ABVAsciiString@@_N@Z present-unmatched
// Retail 0x009CACF0, 898 bytes -- vtable slot 10 of 0x01143A08. The slot is
// settled by elimination: Zero Hour declares exactly three non-pure virtuals on
// this class (openFile, doesFileExist, loadIntoDirectoryTree), the binary has
// four real slots, and the extra one is BFME's wide openFile at slot 6. Slots 5
// and 8 are the two already matched, in the same relative order, so 10 is this.
// The object emits MAE (protected virtual), not UAE.
//
// The callee names are NOT the blocker; all five now have addresses in
// reverse/symbols.csv. Correcting an earlier note here: a wrong address in one
// of those rows FAILS rather than masks. build.py computes the REL32
// displacement from the symbol's address and compares it to retail, so a wrong
// callee address makes the caller mismatch. That is the opposite of the DIR32
// case, and it means these rows fail safe -- a wrong one blocks a match, it
// cannot manufacture one. They are still positional guesses and marked as such
// in symbols.csv; only _M_erase at 0x009CAAD0 has structural backing, being
// recursive.
//
// The real blocker is structural. With all five resolved the body is still the
// wrong shape: retail reserves 0x24 of frame where this reserves 0x30, and the
// two use different callee-saved registers throughout (retail carries the node
// pointer in esi/ebp, this in edi/ebp). Both come out 898 bytes, which is
// coincidence rather than progress.
//
// It is NOT that debugpath and path2 are absent, which is the first thing to
// suspect given the DEBUG_LOG they feed is commented out. Retail has exactly
// three concat calls, at 0x009CAF52, 0x009CAF67 and 0x009CAFDA, which is one
// for each of this function's three -- two on debugpath and one on path2. Both
// locals are real. The extra 0xC of frame is something else.
void ArchiveFileSystem::loadIntoDirectoryTree(const ArchiveFile *archiveFile, const AsciiString& archiveFilename, Bool overwrite)
{

	FilenameList filenameList;

	archiveFile->getFileListInDirectory(AsciiString(""), AsciiString(""), AsciiString("*"), filenameList, TRUE);

	FilenameListIter it = filenameList.begin();

	while (it != filenameList.end()) {
		// add this filename to the directory tree.
		AsciiString path = *it;
		path.toLower();
		AsciiString token;
		AsciiString debugpath;

		ArchivedDirectoryInfo *dirInfo = &m_rootDirectory;

		Bool infoInPath;
		infoInPath = path.nextToken(&token, "\\/");

		while (infoInPath && (!bfmeFind(token, '.') || bfmeFind(path, '.'))) {
			ArchivedDirectoryInfoMap::iterator tempiter = dirInfo->m_directories.find(token);
			if (tempiter == dirInfo->m_directories.end()) 
			{
				dirInfo->m_directories[token].clear();
				dirInfo->m_directories[token].m_directoryName = token;
			}

			dirInfo = &(dirInfo->m_directories[token]);
			bfmeConcat(debugpath, token);
			bfmeConcat(debugpath, '\\');
			infoInPath = path.nextToken(&token, "\\/");
		}

		// token is the filename, and dirInfo is the directory that this file is in.
		if (dirInfo->m_files.find(token) == dirInfo->m_files.end() || overwrite) {
			AsciiString path2;
			path2 = debugpath;
			bfmeConcat(path2, token);
//			DEBUG_LOG(("ArchiveFileSystem::loadIntoDirectoryTree - adding file %s, archived in %s\n", path2.str(), archiveFilename.str()));
			dirInfo->m_files[token] = archiveFilename;
		}

		it++;
	}
}

// ?loadMods@ArchiveFileSystem@@QAEXXZ present-unmatched
// Ruled out: 0x00063BA0, 474 bytes. That function is the obvious candidate --
// it is one of only two places referencing the "*.big" literal at 0x0107532C
// (the other is Win32BIGFileSystem::init), and it calls TheArchiveFileSystem
// through [edx+0x24], which is loadBigFilesFromDirectory at slot 9. But this
// body compiles to 231 bytes against its 474, and 0x00063BA0 reads a stack
// argument at entry while loadMods takes none. Two different functions.
//
// Whatever 0x00063BA0 is, it also sets byte_134CB50 -- the second path prefix --
// from TheWritableGlobalData+0xDC0 at 0x00063D5F, so it is mod-directory setup
// of some kind, just not this method.
void ArchiveFileSystem::loadMods() {
	if (TheGlobalData->m_modBIG.isNotEmpty())
	{
		ArchiveFile *archiveFile = openArchiveFile(TheGlobalData->m_modBIG.str());

		if (archiveFile != NULL) {
			DEBUG_LOG(("ArchiveFileSystem::loadMods - loading %s into the directory tree.\n", TheGlobalData->m_modBIG.str()));
			loadIntoDirectoryTree(archiveFile, TheGlobalData->m_modBIG, TRUE);
			m_archiveFileMap[TheGlobalData->m_modBIG] = archiveFile;
			DEBUG_LOG(("ArchiveFileSystem::loadMods - %s inserted into the archive file map.\n", TheGlobalData->m_modBIG.str()));
		}
		else
		{
			DEBUG_LOG(("ArchiveFileSystem::loadMods - could not openArchiveFile(%s)\n", TheGlobalData->m_modBIG.str()));
		}
	}

	if (TheGlobalData->m_modDir.isNotEmpty())
	{
#ifdef DEBUG_LOGGING
		Bool ret =
#endif
		loadBigFilesFromDirectory(TheGlobalData->m_modDir, "*.big", TRUE);
		DEBUG_ASSERTLOG(ret, ("loadBigFilesFromDirectory(%s) returned FALSE!\n", TheGlobalData->m_modDir.str()));
	}
}


// ?openFile@ArchiveFileSystem@@UAEPAVFile@@PBDH@Z
// Vtable slot 5 of 0x01143A08, which FileSystem::openFile reaches through
// [eax+0x14]; that caller byte-matches retail, so the slot is a fact. The
// archive map is at this+4 and ArchiveFile::openFile is its slot 2.
File * ArchiveFileSystem::openFile(const Char *filename, Int access /* = 0 */)
{
	AsciiString archiveFilename;
	{
		// The argument temporary is named and block-scoped on purpose. Written as
		// one expression -- getArchiveFilenameForFile(AsciiString(filename)) -- the
		// compiler gives the argument and the returned temporary the opposite pair
		// of stack slots, which shows up as the two releaseBuffer calls coming out
		// in the wrong order. Same lifetimes either way: both temporaries die
		// before the length check.
		AsciiString key(filename);
		archiveFilename = getArchiveFilenameForFile(key);
	}

	if (bfmeLength(archiveFilename) == 0) {
		return NULL;
	}

	return m_archiveFileMap[archiveFilename]->openFile(filename, access);
}

// ?openFile@ArchiveFileSystem@@UAEPAVFile@@PBDHHH@Z
// The wide form, vtable slot 6, retail 0x009CA6E0 and ret 0x10. Same body as the
// narrow one above except that it reaches ArchiveFile slot 3 rather than slot 2,
// which is the same one-slot step the wide FileSystem::openFile takes.
File * ArchiveFileSystem::openFile(const Char *filename, Int access, Int a3, Int a4)
{
	AsciiString archiveFilename;
	{
		AsciiString key(filename);
		archiveFilename = getArchiveFilenameForFile(key);
	}

	if (bfmeLength(archiveFilename) == 0) {
		return NULL;
	}

	return m_archiveFileMap[archiveFilename]->openFile(filename, access, a3, a4);
}

Bool ArchiveFileSystem::getFileInfo(const AsciiString& filename, FileInfo *fileInfo) const
{
	if (fileInfo == NULL) {
		return FALSE;
	}

	if (bfmeLength(filename) <= 0) {
		return FALSE;
	}

	AsciiString archiveFilename = getArchiveFilenameForFile(filename);
	ArchiveFileMap::const_iterator it = m_archiveFileMap.find(archiveFilename);
	if (it != m_archiveFileMap.end())
	{
		return it->second->getFileInfo(filename, fileInfo);
	}
	else
	{
		return FALSE;
	}
}

// ?getArchiveFilenameForFile@ArchiveFileSystem@@QBE?AVAsciiString@@ABV2@@Z
// Retail 0x009CA2A0, 411 bytes. The address was settled before the body was:
// it is the only callee of ArchiveFileSystem::openFile at 0x009CA62B, and that
// caller byte-matches.
//
// Three reference inlines had to be written out or un-inlined to get here, and
// they are all the same kind of difference -- retail keeps a thin out-of-line
// body where the Zero Hour header expands one. concat is an inline wrapper over
// the two-argument StringBase form rather than an expansion down to
// ensureUniqueBufferOfSize; find(char) is a length-bounded scan off the 16-bit
// header field rather than strchr; and the copy constructor is out-of-line at
// 0x00887B60, which this function reaches three times, once for it->second and
// twice for TheEmptyString.
AsciiString ArchiveFileSystem::getArchiveFilenameForFile(const AsciiString& filename) const
{
	AsciiString path;
	path = filename;
	path.toLower();
	AsciiString token;
	AsciiString debugpath;

	const ArchivedDirectoryInfo *dirInfo = &m_rootDirectory;

	path.nextToken(&token, "\\/");

	while (!bfmeFind(token, '.') || bfmeFind(path, '.')) {

		ArchivedDirectoryInfoMap::const_iterator it = dirInfo->m_directories.find(token);
		if (it != dirInfo->m_directories.end())
		{
			dirInfo = &it->second;
		}
		else
		{
			// the directory doesn't exist, so return NULL

			// dump the directories;
			//DEBUG_LOG(("directory %s not found in %s in archive file system\n", token.str(), debugpath.str()));
			//DEBUG_LOG(("directories in %s in archive file system are:\n", debugpath.str()));
			//ArchivedDirectoryInfoMap::const_iterator it = dirInfo->m_directories.begin();
			//while (it != dirInfo->m_directories.end()) {
			//	DEBUG_LOG(("\t%s\n", it->second.m_directoryName.str()));
			//	it++;
			//}
			//DEBUG_LOG(("end of directory list.\n"));
			return AsciiString::TheEmptyString;
		}

		bfmeConcat(debugpath, token);
		bfmeConcat(debugpath, '\\');

		path.nextToken(&token, "\\/");
	}

	ArchivedFileLocationMap::const_iterator it = dirInfo->m_files.find(token);
	if (it != dirInfo->m_files.end())
	{
		return it->second;
	}
	else
	{
		return AsciiString::TheEmptyString;
	}

}

// ?getFileListInDirectory@ArchiveFileSystem@@ present-unmatched
void ArchiveFileSystem::getFileListInDirectory(const AsciiString& currentDirectory, const AsciiString& originalDirectory, const AsciiString& searchName, FilenameList &filenameList, Bool searchSubdirectories) const
{
	ArchiveFileMap::const_iterator it = m_archiveFileMap.begin();
	while (it != m_archiveFileMap.end()) {
		it->second->getFileListInDirectory(currentDirectory, originalDirectory, searchName, filenameList, searchSubdirectories);
		it++;
	}
}
