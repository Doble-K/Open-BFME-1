// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: FontLibraryBFMERetail::getFont, retail 0x004772D0, 60 bytes. The
// body carried only a machine byte-dump row; the symbols.csv pin names it as
// the BFME retail FontLibrary ABI alias.
//
// The name and size go first to the record lookup. A record, if there is one,
// supplies the byte at +8; without one the byte stands at 1. That byte only
// decides between two weights, four and one, which the compiler produces
// without a branch: negate to set carry, subtract with borrow into itself, mask
// to three and add one.
//
// Both helpers are pinned with this body, at the ILTs the two calls use.

typedef int Int;
typedef float Real;

class AsciiString;
class GameFont;

struct BfmeFontRecord
{
	unsigned char m_bfmeHead[0x08];
	unsigned char m_bfmeWeighted;				// +0x08
};

class FontLibraryBFMERetail
{
public:
	GameFont *getFont(AsciiString *name, Real size, unsigned char style);

private:
	BfmeFontRecord *bfmeFindRecord(AsciiString *name, Real size);
	GameFont *bfmeBuildFont(AsciiString *name, Real size, unsigned char style,
			Int weight);
};

// ?getFont@FontLibraryBFMERetail@@QAEPAVGameFont@@PAVAsciiString@@ME@Z
GameFont *FontLibraryBFMERetail::getFont(AsciiString *name, Real size,
		unsigned char style)
{
	unsigned char weighted = 1;

	BfmeFontRecord *record = bfmeFindRecord(name, size);

	if (record)
		weighted = record->m_bfmeWeighted;

	return bfmeBuildFont(name, size, style, weighted ? 4 : 1);
}
