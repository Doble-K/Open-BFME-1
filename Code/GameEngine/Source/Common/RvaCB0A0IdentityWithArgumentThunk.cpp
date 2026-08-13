struct RvaCB0A0IdentityWithArgumentThunk
{
    RvaCB0A0IdentityWithArgumentThunk *identity(int unused);
};

RvaCB0A0IdentityWithArgumentThunk *RvaCB0A0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
