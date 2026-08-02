// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

struct Video;

namespace _STL
{
struct random_access_iterator_tag {};

template <class In, class Out, class Distance>
Out __copy(In, In, Out, const random_access_iterator_tag &, Distance *);

class VideoCopyShim
{
public:
    static Video *copy(Video *first, Video *last, Video *result, const random_access_iterator_tag &, int *n);
};

template <class In, class Out, class Distance>
Out __copy(In first, In last, Out result, const random_access_iterator_tag &tag, Distance *n)
{
    return (Out)VideoCopyShim::copy((Video *)first, (Video *)last, (Video *)result, tag, (int *)n);
}

template Video *__copy<Video *, Video *, int>(Video *, Video *, Video *, const random_access_iterator_tag &, int *);
}
