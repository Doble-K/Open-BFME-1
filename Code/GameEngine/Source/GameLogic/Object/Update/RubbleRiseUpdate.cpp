// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME5: RubbleRiseUpdate.cpp's copy of buildNonDupRandomIndexList,
// retail 0x002A35A0, zh_sweep packet 002a35a0.
//
// The body is the reference one unchanged. What placed it was not the code but
// the two immediates the random-value macro expands to: retail pushes the
// __FILE__ pointer of RubbleRiseUpdate.cpp and 272 for __LINE__. Four BFME
// sources carry a byte-identical copy of this helper -- StructureCollapse,
// StructureTopple, BoneFX and RubbleRise -- so the code alone cannot say which
// address belongs to which, and only those two immediates can. The neighbours
// agree: ?inList@@YA_NHHQBH@Z sits at 0x002A3570 and RubbleRiseUpdate's own
// constructor at 0x002A3640, immediately below and above this address.
//
// Its own TU because #line in a shared file renumbers everything beneath it.

typedef int Int;
typedef bool Bool;

Int GetGameLogicRandomValue( Int lo, Int hi, char *file, Int line );
#define GameLogicRandomValue(lo, hi) GetGameLogicRandomValue((lo), (hi), (char *)__FILE__, __LINE__)

static Bool inList( Int value, Int count, const Int idxList[] )
{
	for( Int j = 0; j < count; ++j )
	{
		if( idxList[j] == value )
			return true;
	}
	return false;
}

// ?buildNonDupRandomIndexList@@YAXHHQAH@Z
#line 265 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\RubbleRiseUpdate.cpp"
static void buildNonDupRandomIndexList( Int range, Int count, Int idxList[] )
{
	for( Int i = 0; i < count; ++i )
	{
		Int idx;
		do
		{
			idx = GameLogicRandomValue(0, range-1);
		}
		while( inList( idx, i, idxList ) );
		idxList[i] = idx;
	}
}

// The helper is static, so retail's register convention -- range in eax and the
// list in edi -- only survives while a call site in the same TU exists to pin
// it. This is that call site.
void RubbleRiseUpdate_buildIndexList( Int range, Int count, Int idxList[] )
{
	buildNonDupRandomIndexList( range, count, idxList );
}
