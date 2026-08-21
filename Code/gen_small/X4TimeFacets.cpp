// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 time_get/time_put facet instantiations. Each of the four
// protected (_Locale_time*, size_t) constructors the retail image carries at
// 0x00846C80..0x00846DA0 stores a DIFFERENT facet vftable, and the RTTI
// complete-object locator four bytes below each of those vftables names the
// facet outright, which is what assigns the four otherwise identical bodies.

#include <locale>

template class _STL::time_put<char, _STL::ostreambuf_iterator<char, _STL::char_traits<char> > >;
template class _STL::time_get<char, _STL::istreambuf_iterator<char, _STL::char_traits<char> > >;
template class _STL::time_put<wchar_t, _STL::ostreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;
template class _STL::time_get<wchar_t, _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;
