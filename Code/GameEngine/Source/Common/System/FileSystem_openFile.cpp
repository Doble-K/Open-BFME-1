// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// FileSystem::openFile retail 0x009C8860 size 394
//
// STILL A BYTE DUMP. __declspec(naked) with 394 _emit bytes carries no
// relocations, so it names nothing -- which is not merely untidy: it is what
// made the ?TheLocalFileSystem@@ DIR32 conflict unresolvable, because this
// function is one of the two that read both globals and neither could be
// asked which was which. FileSystem_createDirectory.cpp was recovered as C++
// for exactly that reason and answered the question immediately.
//
// The structure is decoded below so the next attempt starts here rather than at
// the bytes. Slot numbers are what the calls actually use, and they differ
// between the two interfaces, which is itself the proof they are different
// classes:
//
//   char buf[0x200];
//   sprintf(buf, "%s\\%s", byte_134CA48, filename);   // via __imp__sprintf
//   File *file = NULL;
//
//   if (byte_134CB50[0]) {                            // non-empty prefix string
//       AsciiString s(byte_134CB50);
//       s.concat(filename, strlen(filename));         // strlen inlined
//       file = TheLocalFileSystem->openFile(s.str(), access);   // slot 2, +0x08
//   }                                                 // s destroyed here (SEH)
//
//   if (!byte_134CB4C && file == NULL && TheArchiveFileSystem) {
//       if (!(access & 8))
//           file = TheArchiveFileSystem->openFile(buf, access);      // slot 5, +0x14
//       if (file == NULL)
//           file = TheArchiveFileSystem->openFile(filename, access);
//   }
//
//   if (TheLocalFileSystem && file == NULL) {
//       if (!(access & 2))
//           file = TheLocalFileSystem->openFile(buf, access);       // slot 2, +0x08
//       ...
//   }
//   return file;
//
// Two globals still need names. 0x0134CB50 is a char array used as an alternate
// path prefix, and 0x0134CB4C is a Bool that suppresses the archive lookup. Both
// live in the zero-fill tail of .data, so reading them out of the file yields the
// next section's bytes rather than their contents -- the same trap that hid 17
// subsystems from tools/dump_subsystems.py until it was taught about raw extents.
//
// 0x0134CC50 is TheArchiveFileSystem and 0x0134D060 is TheLocalFileSystem; both
// are in reverse/symbols.csv now.

class File;
class FileSystem { public: File *openFile(const char *filename, int access); };

// ?openFile@FileSystem@@QAEPAVFile@@PBDH@Z
__declspec(naked) File *FileSystem::openFile(const char * /*filename*/, int /*access*/)
{
	__asm {
		_emit 064h
		_emit 0A1h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 06Ah
		_emit 0FFh
		_emit 068h
		_emit 01Bh
		_emit 003h
		_emit 006h
		_emit 001h
		_emit 050h
		_emit 064h
		_emit 089h
		_emit 025h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 081h
		_emit 0ECh
		_emit 004h
		_emit 002h
		_emit 000h
		_emit 000h
		_emit 053h
		_emit 056h
		_emit 057h
		_emit 08Bh
		_emit 0BCh
		_emit 024h
		_emit 020h
		_emit 002h
		_emit 000h
		_emit 000h
		_emit 057h
		_emit 068h
		_emit 048h
		_emit 0CAh
		_emit 034h
		_emit 001h
		_emit 08Dh
		_emit 044h
		_emit 024h
		_emit 018h
		_emit 068h
		_emit 000h
		_emit 041h
		_emit 00Fh
		_emit 001h
		_emit 050h
		_emit 033h
		_emit 0F6h
		_emit 0FFh
		_emit 015h
		_emit 08Ch
		_emit 094h
		_emit 035h
		_emit 001h
		_emit 0A0h
		_emit 050h
		_emit 0CBh
		_emit 034h
		_emit 001h
		_emit 08Bh
		_emit 09Ch
		_emit 024h
		_emit 034h
		_emit 002h
		_emit 000h
		_emit 000h
		_emit 083h
		_emit 0C4h
		_emit 010h
		_emit 084h
		_emit 0C0h
		_emit 074h
		_emit 06Dh
		_emit 068h
		_emit 050h
		_emit 0CBh
		_emit 034h
		_emit 001h
		_emit 08Dh
		_emit 04Ch
		_emit 024h
		_emit 010h
		_emit 0E8h
		_emit 002h
		_emit 003h
		_emit 0ECh
		_emit 0FFh
		_emit 085h
		_emit 0FFh
		_emit 089h
		_emit 0B4h
		_emit 024h
		_emit 018h
		_emit 002h
		_emit 000h
		_emit 000h
		_emit 074h
		_emit 012h
		_emit 08Bh
		_emit 0C7h
		_emit 08Dh
		_emit 050h
		_emit 001h
		_emit 08Bh
		_emit 0FFh
		_emit 08Ah
		_emit 008h
		_emit 040h
		_emit 084h
		_emit 0C9h
		_emit 075h
		_emit 0F9h
		_emit 02Bh
		_emit 0C2h
		_emit 0EBh
		_emit 002h
		_emit 033h
		_emit 0C0h
		_emit 050h
		_emit 057h
		_emit 08Dh
		_emit 04Ch
		_emit 024h
		_emit 014h
		_emit 0E8h
		_emit 078h
		_emit 0F4h
		_emit 0EBh
		_emit 0FFh
		_emit 08Bh
		_emit 044h
		_emit 024h
		_emit 00Ch
		_emit 085h
		_emit 0C0h
		_emit 074h
		_emit 005h
		_emit 083h
		_emit 0C0h
		_emit 008h
		_emit 0EBh
		_emit 005h
		_emit 0B8h
		_emit 08Bh
		_emit 038h
		_emit 007h
		_emit 001h
		_emit 08Bh
		_emit 00Dh
		_emit 060h
		_emit 0D0h
		_emit 034h
		_emit 001h
		_emit 08Bh
		_emit 011h
		_emit 053h
		_emit 050h
		_emit 0FFh
		_emit 052h
		_emit 008h
		_emit 08Dh
		_emit 04Ch
		_emit 024h
		_emit 00Ch
		_emit 08Bh
		_emit 0F0h
		_emit 0C7h
		_emit 084h
		_emit 024h
		_emit 018h
		_emit 002h
		_emit 000h
		_emit 000h
		_emit 0FFh
		_emit 0FFh
		_emit 0FFh
		_emit 0FFh
		_emit 0E8h
		_emit 023h
		_emit 0F0h
		_emit 0EBh
		_emit 0FFh
		_emit 0A0h
		_emit 04Ch
		_emit 0CBh
		_emit 034h
		_emit 001h
		_emit 084h
		_emit 0C0h
		_emit 075h
		_emit 033h
		_emit 085h
		_emit 0F6h
		_emit 075h
		_emit 02Fh
		_emit 08Bh
		_emit 00Dh
		_emit 050h
		_emit 0CCh
		_emit 034h
		_emit 001h
		_emit 085h
		_emit 0C9h
		_emit 074h
		_emit 02Bh
		_emit 0F6h
		_emit 0C3h
		_emit 008h
		_emit 075h
		_emit 017h
		_emit 08Bh
		_emit 001h
		_emit 053h
		_emit 08Dh
		_emit 054h
		_emit 024h
		_emit 014h
		_emit 052h
		_emit 0FFh
		_emit 050h
		_emit 014h
		_emit 08Bh
		_emit 00Dh
		_emit 050h
		_emit 0CCh
		_emit 034h
		_emit 001h
		_emit 08Bh
		_emit 0F0h
		_emit 085h
		_emit 0F6h
		_emit 075h
		_emit 00Fh
		_emit 08Bh
		_emit 001h
		_emit 053h
		_emit 057h
		_emit 0FFh
		_emit 050h
		_emit 014h
		_emit 08Bh
		_emit 0F0h
		_emit 08Bh
		_emit 00Dh
		_emit 050h
		_emit 0CCh
		_emit 034h
		_emit 001h
		_emit 0A1h
		_emit 060h
		_emit 0D0h
		_emit 034h
		_emit 001h
		_emit 085h
		_emit 0C0h
		_emit 074h
		_emit 032h
		_emit 085h
		_emit 0F6h
		_emit 075h
		_emit 02Eh
		_emit 0F6h
		_emit 0C3h
		_emit 002h
		_emit 075h
		_emit 018h
		_emit 08Bh
		_emit 010h
		_emit 053h
		_emit 08Dh
		_emit 04Ch
		_emit 024h
		_emit 014h
		_emit 051h
		_emit 08Bh
		_emit 0C8h
		_emit 0FFh
		_emit 052h
		_emit 008h
		_emit 08Bh
		_emit 0F0h
		_emit 085h
		_emit 0F6h
		_emit 075h
		_emit 010h
		_emit 0A1h
		_emit 060h
		_emit 0D0h
		_emit 034h
		_emit 001h
		_emit 08Bh
		_emit 010h
		_emit 053h
		_emit 057h
		_emit 08Bh
		_emit 0C8h
		_emit 0FFh
		_emit 052h
		_emit 008h
		_emit 08Bh
		_emit 0F0h
		_emit 08Bh
		_emit 00Dh
		_emit 050h
		_emit 0CCh
		_emit 034h
		_emit 001h
		_emit 0A0h
		_emit 04Ch
		_emit 0CBh
		_emit 034h
		_emit 001h
		_emit 084h
		_emit 0C0h
		_emit 074h
		_emit 02Bh
		_emit 085h
		_emit 0F6h
		_emit 075h
		_emit 027h
		_emit 085h
		_emit 0C9h
		_emit 074h
		_emit 023h
		_emit 0F6h
		_emit 0C3h
		_emit 008h
		_emit 075h
		_emit 015h
		_emit 08Bh
		_emit 001h
		_emit 053h
		_emit 08Dh
		_emit 054h
		_emit 024h
		_emit 014h
		_emit 052h
		_emit 0FFh
		_emit 050h
		_emit 014h
		_emit 085h
		_emit 0C0h
		_emit 075h
		_emit 011h
		_emit 08Bh
		_emit 00Dh
		_emit 050h
		_emit 0CCh
		_emit 034h
		_emit 001h
		_emit 08Bh
		_emit 001h
		_emit 053h
		_emit 057h
		_emit 0FFh
		_emit 050h
		_emit 014h
		_emit 0EBh
		_emit 002h
		_emit 08Bh
		_emit 0C6h
		_emit 08Bh
		_emit 08Ch
		_emit 024h
		_emit 010h
		_emit 002h
		_emit 000h
		_emit 000h
		_emit 05Fh
		_emit 05Eh
		_emit 05Bh
		_emit 064h
		_emit 089h
		_emit 00Dh
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 081h
		_emit 0C4h
		_emit 010h
		_emit 002h
		_emit 000h
		_emit 000h
		_emit 0C2h
		_emit 008h
		_emit 000h
	}
}
