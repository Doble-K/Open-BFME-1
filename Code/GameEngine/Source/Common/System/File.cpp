// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The File base class. Its three subclasses' vtables all carry
// ?close@File@@UAEXXZ at slot 2, which is what identifies the family, and BFME's
// layout is Zero Hour's 15 File slots with two appended -- so slots 0..14 mean
// exactly what Zero Hour's file.h declares them to mean:
//
//   0x01143A38  17 slots
//   0x01143AA8  17 slots
//   0x01143AF8  40 slots  (slots 3..9 share one stub, so read/write/seek and
//                          friends are pure in that class)
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
	virtual ~File();
	virtual Bool open( const char *filename, Int access = 0 );
	virtual void close( void );

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
