struct TricenaryIdentityWithArgumentThunk
{
    TricenaryIdentityWithArgumentThunk *identity(int unused);
};

TricenaryIdentityWithArgumentThunk *TricenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
