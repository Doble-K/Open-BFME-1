// cl: /DNDEBUG /DWIN32 /MD -Ireference/shims/gamespy
/* GameSpy SDK, 2004 vintage -- pristine upstream C source.
   Sourced from the Area 51 (Inevitable Entertainment / Midway) source release,
   github.com/bisc67/Area51, Support/NetworkMgr/GameSpy -- the only public
   carrier found with the pre-2005 SDK layout (top-level nonport.c, no common/).
   Dated by nonport.h's own marker "Added by Saad Nader on 08-02-2004".
   That vintage is not assumed, it is measured: against lotrbfme.exe this tree
   scores 440 byte-exact whole functions where the 2007 SDK (nitrocaster/GameSpy,
   GS_Aluigi) scores 51 and 48 on the same TUs.
   Retail linked the DLL CRT, so libc calls are __imp__ indirect -- /MD is what
   makes those call sites byte-exact -- and built the SDK __cdecl: /Gz collapses
   the qr2+GP+ghttp core from 108 exact hits to 6.
   Win32 headers come from reference/shims/gamespy (see its windows.h): the
   toolchain ships no PlatformSDK, and the sweep shim next door is C++-only.

   This TU (ghttpCallbacks.c) is not present in the Area51 carrier tree -- the
   three ghiCall*Callback() trampolines are declared in ghttpCallbacks.h but
   were never checked in as a standalone .c anywhere upstream that has been
   found. Only ghiCallProgressCallback is reconstructed here, from the retail
   disassembly at 0x0087B610 (connection->progressCallback dispatch, matching
   the ghttpProgressCallback typedef in ghttp.h field-for-field). The other
   two declared trampolines are absent-from-retail in this TU: they are not
   part of this lane's target pool and are left undefined here. */
/*
GameSpy GHTTP SDK
Dan "Mr. Pants" Schoenblum
dan@gamespy.com

Copyright 1999-2001 GameSpy Industries, Inc

18002 Skypark Circle
Irvine, California 92614
949.798.4200 (Tel)
949.798.4299 (Fax)
devsupport@gamespy.com
*/

#include "ghttpCallbacks.h"

// ghiCallProgressCallback present-unmatched
// Call the progress callback for this connection.
//////////////////////////////////////////////////
void ghiCallProgressCallback
(
	GHIConnection * connection,
	const char * buffer,
	GHTTPByteCount bufferLen
)
{
	if(connection->progressCallback)
	{
		connection->progressCallback(connection->request, connection->state,
			buffer, bufferLen, connection->fileBytesReceived,
			connection->totalSize, connection->callbackParam);
	}
}
