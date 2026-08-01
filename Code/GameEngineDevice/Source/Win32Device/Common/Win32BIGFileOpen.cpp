// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep
//
// Win32BIGFile::openFile(const Char *, Int) -- the two-argument form.
//
// BFME split Zero Hour's single openFile into two virtuals: this one takes the
// filename and access flags and forwards to a four-argument form with two zeros
// appended. That extra virtual is the whole reason ArchiveFile has nine vtable
// slots where Zero Hour's has eight, and it is why every slot from
// closeAllFiles onward sits one lower than Zero Hour's declaration order.
//
// It cannot live in Win32BIGFile.cpp because the four-argument overload does not
// exist in Zero Hour's Win32BIGFile.h, and the forward has to go through the
// vtable -- retail is call [eax+0xc], slot 3 -- so the class needs the real slot
// numbering to reproduce that displacement. The class below is therefore a
// layout skeleton whose only job is to put the two overloads at slots 2 and 3,
// the same dummy-virtual technique already used for the InGameUI and Radar slot
// pins; the two virtuals ahead of them are the destructor and getFileInfo.
//
// What the four-argument form does with its extra two arguments is not settled
// here, so they are spelled as an untyped buffer and a length, which is what the
// call site passes (two zeros) and all this function needs them to be. Its body
// at 0x009D1560 looks the filename up and then allocates either 0x2C bytes and
// runs StreamingArchiveFile's constructor, or 0x20 bytes and RAMFile's,
// selected by testing bit 8 of access -- Zero Hour's File::STREAMING.
class File;

class Win32BIGFile
{
public:
	virtual ~Win32BIGFile();									// slot 0
	virtual bool getFileInfo( const void *filename, void *fileInfo ) const;	// slot 1
	// Declared four-argument first so that the two land at slots 2 and 3 in that
	// order: MSVC lays overloads of one name into the vtable back to front, and
	// declaring them the readable way round put the four-argument form at slot 2,
	// which showed up as the one wrong byte in an otherwise exact forward
	// (call [eax+8] where retail has call [eax+0xc]).
	virtual File *openFile( const char *filename, int access, void *buffer, int bufferSize );	// slot 3
	virtual File *openFile( const char *filename, int access );		// slot 2
};

// ?openFile@Win32BIGFile@@UAEPAVFile@@PBDH@Z
File *Win32BIGFile::openFile( const char *filename, int access )
{
	return openFile( filename, access, 0, 0 );
}
