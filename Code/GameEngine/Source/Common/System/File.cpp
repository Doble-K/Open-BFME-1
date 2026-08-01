// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The File base class. Its three subclasses' vtables all carry
// ?close@File@@UAEXXZ at slot 2, which is what identifies the family, and BFME's
// layout is Zero Hour's 15 File slots with two appended -- so slots 0..14 mean
// exactly what Zero Hour's file.h declares them to mean:
//
//   0x01143A38  17 slots  MemoryReadFile
//   0x01143AA8  17 slots  MemoryWriteFile
//   0x01143AF8  40 slots  (slots 3..9 share one stub, so read/write/seek and
//                          friends are pure in that class)
//
// The first two are named by their own constructors. 0x009CB3D0 installs
// 0x01143A38 and then sets the file's name to "<MemoryReadFile>"; 0x009CB4E0
// installs 0x01143AA8 and sets "<MemoryWriteFile>". That is the same kind of
// evidence "<no file>" gives for File itself -- a literal the object's own
// constructor uses to identify it -- and both classes are BFME-only, appearing
// nowhere in the Zero Hour tree. The 40-slot class is still unnamed: its two
// constructors at 0x009CB7A0 and 0x009CB8C0 set only "<no file>", which they
// inherit from File and which therefore says nothing about them.
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
	enum { TEXT = 0x20 };		// the bit print() tests: retail is test byte ptr [esi+8], 0x20

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
