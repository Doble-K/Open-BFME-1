struct RvaE59E0IdentityWithArgumentThunk
{
    RvaE59E0IdentityWithArgumentThunk *identity(int unused);
};

RvaE59E0IdentityWithArgumentThunk *RvaE59E0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
