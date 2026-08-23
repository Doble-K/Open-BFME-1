// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: the vector<ModuleInfo::Nugget> internals -- _M_clear at
// 0x00771D00, __copy at 0x00770E00 and _M_allocate_and_copy at 0x0076B3B0.
// All three names were parked on 5-byte thunks.
//
// The element is 0x14 bytes, which the stride and the divide-by-twenty in the
// size arithmetic both carry, and that is the reference's Nugget unchanged:
// two AsciiStrings, a module-data pointer, an interface mask and three Bools.
// Its assignment is StringBase<char>::set twice and its destructor
// releaseBuffer twice, which is what the copy loop and the clear loop call.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;
typedef bool Bool;

// Only the two members these bodies reach; declaring the whole of
// string_base.h's StringBase would add its private destructor as a second call.
template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	void set(const StringBase<T> &src);			// retail 0x00887C90

private:
	void releaseBuffer();					// retail 0x00887940

	void *m_data;
};

class AsciiString
{
public:
	~AsciiString() { m_string.releaseBuffer(); }

	const AsciiString &operator=(const AsciiString &src) { m_string.set(src.m_string); return *this; }

	StringBase<char> m_string;
};

class ModuleData;

class ModuleInfo
{
public:
	struct Nugget
	{
		AsciiString first;
		AsciiString m_moduleTag;
		const ModuleData *second;
		Int interfaceMask;
		Bool copiedFromDefault;
		Bool inheritable;
		Bool overrideableByLikeKind;
	};
};

void BfmeModuleInfoNuggetVectorAnchor(_STL::vector<ModuleInfo::Nugget> &out, const _STL::vector<ModuleInfo::Nugget> &in)
{
	out = in;
}
