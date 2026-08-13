struct RvaA0350TwoValueCopyThunk
{
    int first;
    int second;

    RvaA0350TwoValueCopyThunk *copy(const RvaA0350TwoValueCopyThunk *source);
};

RvaA0350TwoValueCopyThunk *RvaA0350TwoValueCopyThunk::copy(
    const RvaA0350TwoValueCopyThunk *source)
{
    first = source->first;
    second = source->second;
    return this;
}
