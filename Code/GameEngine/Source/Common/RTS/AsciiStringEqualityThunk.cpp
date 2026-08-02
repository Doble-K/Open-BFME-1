// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class AsciiString;

class AsciiStringEqualityShim
{
public:
    static bool equal(const AsciiString &, const AsciiString &);
};

bool operator==(const AsciiString &a, const AsciiString &b)
{
    return AsciiStringEqualityShim::equal(a, b);
}
