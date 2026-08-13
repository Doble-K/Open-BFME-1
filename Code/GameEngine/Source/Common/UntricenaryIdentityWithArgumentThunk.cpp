struct UntricenaryIdentityWithArgumentThunk
{
    UntricenaryIdentityWithArgumentThunk *identity(int unused);
};

UntricenaryIdentityWithArgumentThunk *UntricenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
