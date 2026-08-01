// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The File base class. Its three subclasses' vtables all carry
// ?close@File@@UAEXXZ at slot 2, which is what identifies the family, and BFME's
// layout is Zero Hour's 15 File slots with two appended -- so slots 0..14 mean
// exactly what Zero Hour's file.h declares them to mean:
//
//   0x01143A38  MemoryReadFile
//   0x01143AA8  MemoryWriteFile
//   0x01143AF8  File itself
//
// The first two are named by their own constructors. 0x009CB3D0 installs
// 0x01143A38 and then sets the file's name to "<MemoryReadFile>"; 0x009CB4E0
// installs 0x01143AA8 and sets "<MemoryWriteFile>". That is the same kind of
// evidence "<no file>" gives for File -- a literal the object's own constructor
// uses to identify it -- and both classes are BFME-only, appearing nowhere in
// the Zero Hour tree.
//
// There are seven File vtables in all, found by looking for the ones that carry
// File::print (0x009CB6C0) at slot 10, which every subclass here inherits:
//
//   0x01143A38  MemoryReadFile      dtor 0x009CB440
//   0x01143AA8  MemoryWriteFile     dtor 0x009CB650
//   0x01143AF8  File                dtor 0x009CB950
//   0x01143C10  unnamed             dtor 0x009D1960   (see below)
//   0x01143C58  unnamed             dtor 0x009D1C30   -- the only one that also
//                                                        overrides close
//   0x01143CA8  unnamed             dtor 0x009D22B0
//   0x01143D38  unnamed             dtor 0x009D26C0
//
// So the family runs past 0x009CE000 into 0x009D2xxx. The four unnamed ones set
// no identifying literal the way MemoryReadFile and MemoryWriteFile do. The
// 0x01143C10 one is constructed near the string "Streaming from a compressed
// archive file is not supported", which points at Zero Hour's
// StreamingArchiveFile -- but that text is BFME's own, appearing nowhere in the
// Zero Hour tree, so it is a lead and not a name.
//
// 0x01143AF8 is File's own: MemoryReadFile's constructor calls 0x009CB7A0 first,
// and that is what stores 0x01143AF8 and sets "<no file>", so 0x009CB7A0 is
// File::File and 0x009CB8C0 (which MemoryReadFile's deleting destructor calls)
// is File::~File. Counting slots forward from a vtable overruns into the next
// one -- .rdata packs them adjacently with nothing between -- so all three are
// 17 slots, not the 40 a naive walk reports for the last.
//
// Slots holding the same address in all three are File's own un-overridden
// implementations: slot 2 close (0x009CB880), slot 10 print (0x009CB6C0), and
// slots 15/16 (0x009CB760, 0x009CB790) -- the two BFME added, which Zero Hour
// has no name for.
//
// The class is declared here rather than taken from Zero Hour's Common/file.h
// because BFME's differs in the two ways close() shows: File is not a
// MemoryPoolObject here (m_deleteOnClose closes by deleting through the vtable,
// not through the pool's three-call sequence), and the member layout is proven
// directly -- m_nameStr at +4, m_open at +0xc, m_deleteOnClose at +0xd.
#include "PreRTS.h"
#include "Common/AsciiString.h"

class File
{
public:
	// Access flags. TEXT is the bit print() tests -- retail is
	// test byte ptr [esi+8], 0x20 -- and READ|BINARY is what MemoryReadFile's
	// constructor stores (0x41).
	enum { READ = 0x01, WRITE = 0x02, TEXT = 0x20, BINARY = 0x40 };

	File();
	virtual ~File();							// slot 0
	virtual Bool open( const char *filename, Int access = 0 );	// slot 1
	virtual void close( void );					// slot 2
	virtual Int read( void *buffer, Int bytes );			// slot 3
	virtual Int write( const void *buffer, Int bytes );		// slot 4
	virtual Int seek( Int bytes, Int mode );				// slot 5
	virtual void nextLine( char *buf, Int bufSize );		// slot 6
	virtual Bool scanInt( Int &newInt );				// slot 7
	virtual Bool scanReal( Real &newReal );				// slot 8
	virtual Bool scanString( AsciiString &newString );		// slot 9
	virtual Bool print( const char *format, ... );			// slot 10
	virtual Int size( void );					// slot 11
	virtual Int position( void );					// slot 12
	virtual char *readEntireAndClose( void );			// slot 13
	virtual File *convertToRAMFile( void );				// slot 14
	// slots 15 and 16 are BFME additions (0x009CB760, 0x009CB790); Zero Hour has
	// no name for either, so they are absent here rather than guessed at.

protected:
	void setName( const char *name ) { m_nameStr = name; }

	AsciiString m_nameStr;		// +0x04
	Int m_access;				// +0x08
	Bool m_open;				// +0x0c
	Bool m_deleteOnClose;		// +0x0d
	void *m_ownedBuffer;		// +0x10 -- File::~File free()s it if non-null
};

// ?close@File@@UAEXXZ
// Must be called once per successful open(). Zero Hour ends with
// this->deleteInstance(); BFME clears m_deleteOnClose first and then deletes
// through vtable slot 0 -- a plain delete this, not MemoryPoolObject's
// getObjectMemoryPool/dtor/freeBlock sequence.
void File::close( void )
{
	if( m_open )
	{
		setName( "<no file>" );
		m_open = FALSE;
		if ( m_deleteOnClose )
		{
			m_deleteOnClose = FALSE;
			delete this;
		}
	}
}

// ?print@File@@UAA_NPBDZZ
// Slot 10, and the same address in all three vtables, so this is File's own.
// TEXT is 0x20 in m_access, read straight off retail's test byte ptr [esi+8], 0x20.
Bool File::print( const char *format, ... )
{
	char buffer[10*1024];
	Int len;

	if ( ! (m_access & TEXT ) )
	{
		return FALSE;
	}

	va_list args;
	va_start( args, format );
	len = vsprintf( buffer, format, args );
	va_end( args );

	if ( len >= sizeof(buffer) )
	{
		return FALSE;
	}

	return (write ( buffer, len ) == len);
}

//-----------------------------------------------------------------------------
// MemoryReadFile -- a File over a block of memory the caller already has.
// Named by its own constructor at 0x009CB3D0, which installs vtable 0x01143A38
// and then sets the file's name to "<MemoryReadFile>". BFME-only; Zero Hour has
// no such class.
//
// Layout, read off the overrides below: m_data at +0x14, m_size at +0x18 and
// m_pos at +0x1c -- straight after File, whose own last member is the buffer
// pointer at +0x10 that File::File zeroes and File::~File frees.
//-----------------------------------------------------------------------------
class MemoryReadFile : public File
{
public:
	virtual Bool open( const char *filename, Int access = 0 );
	virtual Int read( void *buffer, Int bytes );
	virtual Int write( const void *buffer, Int bytes );
	virtual Int seek( Int bytes, Int mode );
	virtual void nextLine( char *buf, Int bufSize );
	virtual Bool scanInt( Int &newInt );
	virtual Bool scanReal( Real &newReal );
	virtual Bool scanString( AsciiString &newString );
	virtual Int size( void );
	virtual Int position( void );
	virtual char *readEntireAndClose( void );
	virtual File *convertToRAMFile( void );

public:
	MemoryReadFile( char *data, Int size );

private:
	char *m_data;			// +0x14
	Int m_size;				// +0x18
	Int m_pos;				// +0x1c
};

// ??0MemoryReadFile@@QAE@PADH@Z
// Wraps a block the caller already owns: nothing is copied, and the file reports
// itself as READ|BINARY and already open.
MemoryReadFile::MemoryReadFile( char *data, Int size )
{
	m_data = data;
	m_size = size;
	m_pos = 0;
	m_open = TRUE;
	m_access = READ | BINARY;
	setName( "<MemoryReadFile>" );
}

// ?open@MemoryReadFile@@UAE_NPBDH@Z
Bool MemoryReadFile::open( const char * /*filename*/, Int /*access*/ )
{
	return FALSE;
}

// ?read@MemoryReadFile@@UAEHPAXH@Z present-unmatched
// 70 of 75 bytes. Everything matches except where the compiler restores edi:
// retail pops it at the join of the if(buffer) branch and then does the m_pos
// update, we do the update first. Same registers, same order otherwise. Tried
// hoisting the source pointer, an early return on zero, and the &m_data[m_pos]
// form -- all three are worse, so it is not the obvious shapes.
Int MemoryReadFile::read( void *buffer, Int bytes )
{
	if( bytes < 0 )
	{
		return -1;
	}

	// Unsigned compare: retail is jbe, not jle. The negative case is already
	// gone by here, so the clamp is done in UnsignedInt.
	UnsignedInt remaining = (UnsignedInt)m_size - (UnsignedInt)m_pos;
	if( (UnsignedInt)bytes > remaining )
	{
		bytes = remaining;
	}

	if( bytes )
	{
		if( buffer )
		{
			memcpy( buffer, m_data + m_pos, bytes );
		}
		m_pos += bytes;
	}

	return bytes;
}

// ?write@MemoryReadFile@@UAEHPBXH@Z
// Read-only, so writing always fails.
Int MemoryReadFile::write( const void * /*buffer*/, Int /*bytes*/ )
{
	return -1;
}

// ?seek@MemoryReadFile@@UAEHHH@Z
Int MemoryReadFile::seek( Int bytes, Int mode )
{
	Int pos;

	switch( mode )
	{
		case 0:		// START
			pos = bytes;
			break;
		case 1:		// CURRENT
			pos = m_pos + bytes;
			break;
		case 2:		// END
			pos = m_size + bytes;
			break;
		default:
			return -1;
	}

	if( (UnsignedInt)pos > (UnsignedInt)m_size )
	{
		return -1;
	}

	m_pos = pos;
	return pos;
}

// ?nextLine@MemoryReadFile@@UAEXPADH@Z
void MemoryReadFile::nextLine( char * /*buf*/, Int /*bufSize*/ )
{
}

// ?scanInt@MemoryReadFile@@UAE_NAAH@Z
Bool MemoryReadFile::scanInt( Int & /*newInt*/ )
{
	return FALSE;
}

// ?scanReal@MemoryReadFile@@UAE_NAAM@Z
Bool MemoryReadFile::scanReal( Real & /*newReal*/ )
{
	return FALSE;
}

// ?scanString@MemoryReadFile@@UAE_NAAVAsciiString@@@Z
Bool MemoryReadFile::scanString( AsciiString & /*newString*/ )
{
	return FALSE;
}

// ?size@MemoryReadFile@@UAEHXZ
Int MemoryReadFile::size( void )
{
	return m_size;
}

// ?position@MemoryReadFile@@UAEHXZ
Int MemoryReadFile::position( void )
{
	return m_pos;
}

// ?readEntireAndClose@MemoryReadFile@@UAEPADXZ
// Hands back a copy of the whole block and closes. An empty file still returns
// an allocation rather than NULL, so the caller can always delete[] the result.
char *MemoryReadFile::readEntireAndClose( void )
{
	if( m_size == 0 )
	{
		close();
		return NEW char[1];
	}

	char *buffer = NEW char[m_size];
	memcpy( buffer, m_data, m_size );
	close();
	return buffer;
}

// ?convertToRAMFile@MemoryReadFile@@UAEPAVFile@@XZ
// Already in memory, so it is its own RAM file.
File *MemoryReadFile::convertToRAMFile( void )
{
	return this;
}

//-----------------------------------------------------------------------------
// MemoryWriteFile -- a File that accumulates into a heap buffer it grows itself.
// Named by its constructor at 0x009CB4E0, which installs vtable 0x01143AA8 and
// sets the file's name to "<MemoryWriteFile>". BFME-only, like MemoryReadFile.
//
// Same three members as MemoryReadFile, plus m_capacity at +0x20: the
// buffer is realloc'd to 2*needed + 0x1000 whenever a write would run past it,
// so it grows geometrically with a 4K floor.
//-----------------------------------------------------------------------------
class MemoryWriteFile : public File
{
public:
	virtual Bool open( const char *filename, Int access = 0 );
	virtual Int read( void *buffer, Int bytes );
	virtual Int write( const void *buffer, Int bytes );
	virtual Int seek( Int bytes, Int mode );
	virtual void nextLine( char *buf, Int bufSize );
	virtual Bool scanInt( Int &newInt );
	virtual Bool scanReal( Real &newReal );
	virtual Bool scanString( AsciiString &newString );
	virtual Int size( void );
	virtual Int position( void );
	virtual char *readEntireAndClose( void );
	virtual File *convertToRAMFile( void );

public:
	MemoryWriteFile( const char *name );

private:
	char *m_data;			// +0x14
	Int m_size;				// +0x18
	Int m_pos;				// +0x1c
	Int m_capacity;			// +0x20
	AsciiString m_pendingName;	// +0x24 -- the destructor releases it
};

// ??0MemoryWriteFile@@QAE@PBD@Z present-unmatched
// 71 of 173 bytes. Content matches -- same stores, same fallback, same 0x42 --
// but retail keeps its zero in edx, a caller-saved register it can use freely
// because nothing between the File::File call and the name test is a call. We
// put the zero in ebx, which costs a third callee-saved push, because the
// implicit m_pendingName construction lands before the body assignments in our
// schedule and after them in retail's. Same class of difference as
// friend_parseRankDefinition.
// Starts with no buffer at all; the first write allocates. Reports itself as
// WRITE|BINARY and already open. A null name falls back to the placeholder, the
// same way File's own constructor uses "<no file>".
MemoryWriteFile::MemoryWriteFile( const char *name )
{
	m_data = NULL;
	m_size = 0;
	m_pos = 0;
	m_capacity = 0;
	m_open = TRUE;
	m_access = WRITE | BINARY;

	if( name )
	{
		setName( name );
	}
	else
	{
		setName( "<MemoryWriteFile>" );
	}
}

// ?open@MemoryWriteFile@@UAE_NPBDH@Z
Bool MemoryWriteFile::open( const char * /*filename*/, Int /*access*/ )
{
	return FALSE;
}

// ?read@MemoryWriteFile@@UAEHPAXH@Z
// Write-only, so reading always fails.
Int MemoryWriteFile::read( void * /*buffer*/, Int /*bytes*/ )
{
	return -1;
}

// ?write@MemoryWriteFile@@UAEHPBXH@Z
Int MemoryWriteFile::write( const void *buffer, Int bytes )
{
	if( bytes < 0 )
	{
		return -1;
	}

	if( bytes > 0 && buffer == NULL )
	{
		return -1;
	}

	Int needed = m_pos + bytes;
	if( (UnsignedInt)needed > (UnsignedInt)m_capacity )
	{
		m_capacity = needed * 2 + 0x1000;
		m_data = (char *)realloc( m_data, m_capacity );
	}

	memcpy( m_data + m_pos, buffer, bytes );

	m_pos += bytes;
	if( (UnsignedInt)m_pos > (UnsignedInt)m_size )
	{
		m_size = m_pos;
	}

	return bytes;
}

// ?seek@MemoryWriteFile@@UAEHHH@Z
Int MemoryWriteFile::seek( Int bytes, Int mode )
{
	Int pos;

	switch( mode )
	{
		case 0:		// START
			pos = bytes;
			break;
		case 1:		// CURRENT
			pos = m_pos + bytes;
			break;
		case 2:		// END
			pos = m_size + bytes;
			break;
		default:
			return -1;
	}

	if( (UnsignedInt)pos > (UnsignedInt)m_size )
	{
		return -1;
	}

	m_pos = pos;
	return pos;
}

// ?nextLine@MemoryWriteFile@@UAEXPADH@Z
void MemoryWriteFile::nextLine( char * /*buf*/, Int /*bufSize*/ )
{
}

// ?scanInt@MemoryWriteFile@@UAE_NAAH@Z
Bool MemoryWriteFile::scanInt( Int & /*newInt*/ )
{
	return FALSE;
}

// ?scanReal@MemoryWriteFile@@UAE_NAAM@Z
Bool MemoryWriteFile::scanReal( Real & /*newReal*/ )
{
	return FALSE;
}

// ?scanString@MemoryWriteFile@@UAE_NAAVAsciiString@@@Z
Bool MemoryWriteFile::scanString( AsciiString & /*newString*/ )
{
	return FALSE;
}

// ?size@MemoryWriteFile@@UAEHXZ
Int MemoryWriteFile::size( void )
{
	return m_size;
}

// ?position@MemoryWriteFile@@UAEHXZ
Int MemoryWriteFile::position( void )
{
	return m_pos;
}

// ?readEntireAndClose@MemoryWriteFile@@UAEPADXZ
// Nothing to hand back: this file exists to be written into.
char *MemoryWriteFile::readEntireAndClose( void )
{
	return NULL;
}

// ?convertToRAMFile@MemoryWriteFile@@UAEPAVFile@@XZ
File *MemoryWriteFile::convertToRAMFile( void )
{
	return this;
}

// ??0File@@QAE@XZ
// Zeroes everything and gives the file the placeholder name. m_access starts at
// 0, i.e. NONE.
File::File()
:	m_access(0),
	m_open(FALSE),
	m_deleteOnClose(FALSE),
	m_ownedBuffer(NULL)
{
	setName( "<no file>" );
}

// ??1File@@UAE@XZ present-unmatched
// 101 of 133 bytes, and both remaining divergences are understood.
//
// The deallocator is __stdcall, not free. Retail does push eax; call [imported]
// and then never adjusts esp -- its epilogue's add esp,0x10 covers exactly the
// three EH pushes plus the one local slot, with nothing left over for a cdecl
// argument. (The IAT address matching ours proves nothing: a call through an
// absolute address is a DIR32 slot, which the verifier fills from the target.)
// So this wants a __stdcall deallocator, and which one is still open.
//
// The other is instruction order inside the inlined close(): retail pushes the
// "<no file>" pointer before computing &m_nameStr, we compute it first. The same
// call in File::File matches exactly, so it is specific to close() being inlined
// here rather than to how setName is written.
// Clears m_deleteOnClose before closing, so a File that would normally delete
// itself on close does not re-enter delete while already being destroyed.
File::~File()
{
	m_deleteOnClose = FALSE;
	close();

	if( m_ownedBuffer )
	{
		free( m_ownedBuffer );
	}
}
