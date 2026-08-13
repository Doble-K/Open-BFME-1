struct RvaA0320SingleValueCopyThunk
{
    int value;

    RvaA0320SingleValueCopyThunk *copy(const RvaA0320SingleValueCopyThunk *source);
};

RvaA0320SingleValueCopyThunk *RvaA0320SingleValueCopyThunk::copy(
    const RvaA0320SingleValueCopyThunk *source)
{
    value = source->value;
    return this;
}
