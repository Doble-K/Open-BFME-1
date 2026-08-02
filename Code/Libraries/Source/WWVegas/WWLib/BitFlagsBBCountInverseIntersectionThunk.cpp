template <int Bits>
class BitFlags
{
public:
    int countInverseIntersection(const BitFlags &) const;
};

class BitFlagsCountInverseIntersectionShim
{
public:
    int run(const BitFlagsCountInverseIntersectionShim &) const;
};

template <int Bits>
int BitFlags<Bits>::countInverseIntersection(const BitFlags<Bits> &other) const
{
    return ((const BitFlagsCountInverseIntersectionShim *)this)->run(
        *(const BitFlagsCountInverseIntersectionShim *)&other);
}

template int BitFlags<17>::countInverseIntersection(const BitFlags<17> &) const;
