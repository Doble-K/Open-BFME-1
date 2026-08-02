// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

struct EvaSideSounds;

namespace _STL
{
template <class T, class U>
void _Construct(T *, const U &);

class EvaSideSoundsConstructShim
{
public:
    static void construct(EvaSideSounds *p, const EvaSideSounds &v);
};

template <class T, class U>
void _Construct(T *p, const U &v)
{
    EvaSideSoundsConstructShim::construct((EvaSideSounds *)p, *(const EvaSideSounds *)&v);
}

template void _Construct<EvaSideSounds, EvaSideSounds>(EvaSideSounds *, const EvaSideSounds &);
}
