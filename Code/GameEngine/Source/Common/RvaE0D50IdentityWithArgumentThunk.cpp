struct RvaE0D50IdentityWithArgumentThunk
{
    RvaE0D50IdentityWithArgumentThunk *identity(int unused);
};

RvaE0D50IdentityWithArgumentThunk *RvaE0D50IdentityWithArgumentThunk::identity(int)
{
    return this;
}
