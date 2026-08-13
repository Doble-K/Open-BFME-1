struct QuinaryIdentityWithArgumentThunk
{
    QuinaryIdentityWithArgumentThunk *identity(int unused);
};

QuinaryIdentityWithArgumentThunk *QuinaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
