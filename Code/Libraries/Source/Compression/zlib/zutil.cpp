// cl: /DNDEBUG /MD

/* zutil.c -- target dependent utility functions for the compression library
 * Copyright (C) 1995-2002 Jean-loup Gailly.
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

// zlib 1.1.4, statically linked into BFME. ZLIB_VERSION is the string at
// 0x112D2F8, which sits between the "deflate 1.1.4" and "inflate 1.1.4"
// banners; zlibVersion is the only zlib function that returns it.

#define ZLIB_VERSION "1.1.4"

extern "C" const char * zlibVersion()
{
	return ZLIB_VERSION;
}
