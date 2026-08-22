// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// This TU instantiates STLport's non-POD vector insertion path for the
// four-byte AsciiString handle.  The retail body is an incremental-link
// target distinct from the five-byte forwarding thunk in
// AsciiStringVectorOverflowThunk.cpp.
#include <vector>

class AsciiString
{
public:
	int data[1];
	AsciiString();
	AsciiString(const AsciiString &);
	~AsciiString();
};

template class _STL::vector<AsciiString>;
