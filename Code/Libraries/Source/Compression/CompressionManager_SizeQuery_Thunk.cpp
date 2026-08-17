// cl: /DNDEBUG /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include

#include "compression.h"

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);

// ?getCompressionType@CompressionManager@@SA?AW4CompressionType@@PBXH@Z
CompressionType CompressionManager::getCompressionType( const void *mem, Int len )
{
	if (len < 8)
		return COMPRESSION_NONE;

	if (memcmp(mem, "NOX", 4) == 0)
		return COMPRESSION_NOXLZH;
	if (memcmp(mem, "ZL1", 4) == 0)
		return COMPRESSION_ZLIB1;
	if (memcmp(mem, "ZL2", 4) == 0)
		return COMPRESSION_ZLIB2;
	if (memcmp(mem, "ZL3", 4) == 0)
		return COMPRESSION_ZLIB3;
	if (memcmp(mem, "ZL4", 4) == 0)
		return COMPRESSION_ZLIB4;
	if (memcmp(mem, "ZL5", 4) == 0)
		return COMPRESSION_ZLIB5;
	if (memcmp(mem, "ZL6", 4) == 0)
		return COMPRESSION_ZLIB6;
	if (memcmp(mem, "ZL7", 4) == 0)
		return COMPRESSION_ZLIB7;
	if (memcmp(mem, "ZL8", 4) == 0)
		return COMPRESSION_ZLIB8;
	if (memcmp(mem, "ZL9", 4) == 0)
		return COMPRESSION_ZLIB9;
	if (memcmp(mem, "EAB", 4) == 0)
		return COMPRESSION_BTREE;
	if (memcmp(mem, "EAH", 4) == 0)
		return COMPRESSION_HUFF;

	return (CompressionType)(memcmp(mem, "EAR", 4) == 0);
}

Bool CompressionManager::isDataCompressed( const void *mem, Int len )
{
	CompressionType t = getCompressionType(mem, len);
	return t != COMPRESSION_NONE;
}

Int CompressionManager::getUncompressedSize( const void *mem, Int len )
{
	if (len < 8)
		return len;

	CompressionType compType = getCompressionType( mem, len );
	switch (compType)
	{
		case COMPRESSION_NOXLZH:
		case COMPRESSION_ZLIB1:
		case COMPRESSION_ZLIB2:
		case COMPRESSION_ZLIB3:
		case COMPRESSION_ZLIB4:
		case COMPRESSION_ZLIB5:
		case COMPRESSION_ZLIB6:
		case COMPRESSION_ZLIB7:
		case COMPRESSION_ZLIB8:
		case COMPRESSION_ZLIB9:
		case COMPRESSION_BTREE:
		case COMPRESSION_HUFF:
		case COMPRESSION_REFPACK:
			return *(Int *)(((UnsignedByte *)mem)+4);
	}

	return len;
}
