class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &);

private:
	void *m_data;
};

struct FXBoneInfo
{
	const void *particleSystemTemplate;
	AsciiString boneName;
};

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result,
	const random_access_iterator_tag &, Distance *)
{
	for (Distance count = last - first; count > 0; --count, ++first, ++result)
		*result = *first;
	return result;
}

template FXBoneInfo *__copy<FXBoneInfo *, FXBoneInfo *, int>(FXBoneInfo *, FXBoneInfo *,
	FXBoneInfo *, const random_access_iterator_tag &, int *);
}
