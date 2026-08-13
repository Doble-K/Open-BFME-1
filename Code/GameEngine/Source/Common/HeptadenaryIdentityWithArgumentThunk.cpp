struct HeptadenaryIdentityWithArgumentThunk
{
    HeptadenaryIdentityWithArgumentThunk *identity(int unused);
};

HeptadenaryIdentityWithArgumentThunk *HeptadenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
