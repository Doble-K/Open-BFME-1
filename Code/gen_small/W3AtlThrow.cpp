// cl: /DNDEBUG /MD /EHsc
// Open-BFME-1: the ATL throw helper the ANSI/wide conversion macros share.
//
// Retail keeps one out-of-line body at 0x0005BA40 -- every conversion failure
// funnels here, including Rva0005BA60ThrowLastWin32 in
// W3AtlConversionSupport.cpp, whose own TU compiles without exception handling
// and therefore only declares this. The thrown object is the four-byte ATL
// exception carrier: nothing but the HRESULT.
//
// Identity is address-derived; the ILT thunk at 0x00019ACE reaches it.

typedef long HRESULT;

class CAtlException
{
public:
	CAtlException(HRESULT hr) { m_hr = hr; }
	HRESULT m_hr;
};

extern "C" __declspec(noreturn) void __stdcall W3AtlThrow(HRESULT hr)
{
	throw CAtlException(hr);
}
