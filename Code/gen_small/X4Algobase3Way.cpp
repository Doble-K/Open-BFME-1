// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 <algorithm> extension __lexicographical_compare_3way, the
// instantiations the retail exe carries next to the collate<> facets. Both
// bodies are relocation-free, so the byte comparison is fully concrete.

#include <algorithm>

template int _STL::__lexicographical_compare_3way(const char*, const char*, const char*, const char*);
template int _STL::__lexicographical_compare_3way(const wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*);
