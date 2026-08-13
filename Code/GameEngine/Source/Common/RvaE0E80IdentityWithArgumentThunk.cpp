struct RvaE0E80IdentityWithArgumentThunk
{
    RvaE0E80IdentityWithArgumentThunk *identity(int unused);
};

RvaE0E80IdentityWithArgumentThunk *RvaE0E80IdentityWithArgumentThunk::identity(int)
{
    return this;
}
