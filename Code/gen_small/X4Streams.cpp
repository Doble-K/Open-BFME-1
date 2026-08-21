// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_istream/basic_ostream instantiations, the library
// object the retail image carries around 0x00843860.

#include <istream>
#include <ostream>

template class _STL::basic_istream<char, _STL::char_traits<char> >;
template class _STL::basic_istream<wchar_t, _STL::char_traits<wchar_t> >;
template class _STL::basic_ostream<char, _STL::char_traits<char> >;
template class _STL::basic_ostream<wchar_t, _STL::char_traits<wchar_t> >;
