struct RvaE6B80IdentityWithArgumentThunk
{
    RvaE6B80IdentityWithArgumentThunk *identity(int unused);
};

RvaE6B80IdentityWithArgumentThunk *RvaE6B80IdentityWithArgumentThunk::identity(int)
{
    return this;
}
