struct QuaternaryIdentityWithArgumentThunk
{
    QuaternaryIdentityWithArgumentThunk *identity(int unused);
};

QuaternaryIdentityWithArgumentThunk *QuaternaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
