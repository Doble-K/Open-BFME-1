struct DuotricenaryIdentityWithArgumentThunk
{
    DuotricenaryIdentityWithArgumentThunk *identity(int unused);
};

DuotricenaryIdentityWithArgumentThunk *DuotricenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
