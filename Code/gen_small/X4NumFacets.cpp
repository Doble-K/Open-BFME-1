// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 num_put/num_get facet instantiations. The retail image links
// STLport as a static library; the range around 0x00844A00 is that library's
// numeric-facet object, and the rows this file claims are the
// istreambuf_iterator members and the <algorithm> __find instantiation the
// facet bodies pull in. Every row claimed here is relocation-free, so the
// byte comparison is fully concrete.

#include <locale>

template class _STL::num_put<char, _STL::ostreambuf_iterator<char, _STL::char_traits<char> > >;
template class _STL::num_get<char, _STL::istreambuf_iterator<char, _STL::char_traits<char> > >;
template class _STL::num_put<wchar_t, _STL::ostreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;
template class _STL::num_get<wchar_t, _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;
