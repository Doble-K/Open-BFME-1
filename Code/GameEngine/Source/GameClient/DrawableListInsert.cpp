// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: list<Drawable *>::_M_insert_dispatch over a const-iterator range,
// retail 0x001C53B0, 66 bytes. The name was parked on a 5-byte thunk.
//
// STLport's own body out of the real header: one node per source element, each
// taken from the 0x0C-byte node allocator and linked in front of the position.
// The element is a pointer, so the value is a store rather than a call.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

class Drawable;

void BfmeDrawableListInsertAnchor(_STL::list<Drawable *> &dst, _STL::list<Drawable *>::iterator where, const _STL::list<Drawable *> &src)
{
	dst.insert(where, src.begin(), src.end());
}
