struct RvaCB0C0IdentityWithArgumentThunk
{
    RvaCB0C0IdentityWithArgumentThunk *identity(int unused);
};

RvaCB0C0IdentityWithArgumentThunk *RvaCB0C0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
