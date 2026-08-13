struct RvaCB0F0IdentityWithArgumentThunk
{
    RvaCB0F0IdentityWithArgumentThunk *identity(int unused);
};

RvaCB0F0IdentityWithArgumentThunk *RvaCB0F0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
