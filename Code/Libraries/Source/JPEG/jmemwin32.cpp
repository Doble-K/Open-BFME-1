// cl: /MD /Gz
/* jmemwin32.cpp
 *
 * System-dependent memory manager for the Independent JPEG Group's library
 * (jpeg-6b), Win32/DirectX flavor: small objects come back 16-byte aligned
 * (jpeg_get_small over-allocates via ::operator new[] and rounds the
 * pointer up), with the alignment padding recorded in the byte just before
 * the pointer handed back to the caller. jpeg_free_small reads that pad
 * byte back out to recover the true block start before releasing it.
 * See jmemsys.h for the interface jmemmgr.c (the system-independent half)
 * calls through.
 */

extern "C" {
#include "jinclude.h"
#include "jpeglib.h"
#include "jmemsys.h"
}

extern "C" {

GLOBAL(void)
jpeg_free_small (j_common_ptr cinfo, void * object, size_t sizeofobject)
{
	if (object != NULL)
	{
		unsigned char * aligned = (unsigned char *) object;
		unsigned char offset = aligned[-1];

		delete [] (aligned - offset);
	}
}

}
