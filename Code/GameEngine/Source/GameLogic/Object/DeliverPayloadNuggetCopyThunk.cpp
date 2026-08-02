// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class DeliverPayloadNugget
{
public:
    struct Payload;
};

struct ParticleSysBoneInfo;

namespace _STL
{
struct random_access_iterator_tag {};

template <class In, class Out, class Distance>
Out __copy(In, In, Out, const random_access_iterator_tag &, Distance *);

class DeliverPayloadCopyShim
{
public:
    static void *copy(void *first, void *last, void *result, const random_access_iterator_tag &, int *n);
};

template <class In, class Out, class Distance>
Out __copy(In first, In last, Out result, const random_access_iterator_tag &tag, Distance *n)
{
    return (Out)DeliverPayloadCopyShim::copy((void *)first, (void *)last, (void *)result, tag, (int *)n);
}

template DeliverPayloadNugget::Payload *__copy<DeliverPayloadNugget::Payload *, DeliverPayloadNugget::Payload *, int>(DeliverPayloadNugget::Payload *, DeliverPayloadNugget::Payload *, DeliverPayloadNugget::Payload *, const random_access_iterator_tag &, int *);
template ParticleSysBoneInfo *__copy<ParticleSysBoneInfo *, ParticleSysBoneInfo *, int>(ParticleSysBoneInfo *, ParticleSysBoneInfo *, ParticleSysBoneInfo *, const random_access_iterator_tag &, int *);
}
