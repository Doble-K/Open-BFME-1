struct RvaCB0E0IdentityWithArgumentThunk
{
    RvaCB0E0IdentityWithArgumentThunk *identity(int unused);
};

RvaCB0E0IdentityWithArgumentThunk *RvaCB0E0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
