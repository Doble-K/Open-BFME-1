struct RvaE0E70IdentityWithArgumentThunk
{
    RvaE0E70IdentityWithArgumentThunk *identity(int unused);
};

RvaE0E70IdentityWithArgumentThunk *RvaE0E70IdentityWithArgumentThunk::identity(int)
{
    return this;
}
