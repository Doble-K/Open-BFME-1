struct RvaE8CD0IdentityWithArgumentThunk
{
    RvaE8CD0IdentityWithArgumentThunk *identity(int unused);
};

RvaE8CD0IdentityWithArgumentThunk *RvaE8CD0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
