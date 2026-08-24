// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: _STL::vector<unsigned short>::_M_fill_insert, retail 0x0093FC10,
// 294 bytes. The body carried only a machine byte-dump row;
// reverse/reloc_names.csv holds the name with identity=real.
//
// A trivially copyable element, so the whole body is block moves and the stock
// header instantiation is the model.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

void BfmeUnsignedShortVectorFillInsertAnchor(_STL::vector<unsigned short> &v,
	unsigned int n, const unsigned short &value)
{
	v.insert(v.begin(), n, value);
}
