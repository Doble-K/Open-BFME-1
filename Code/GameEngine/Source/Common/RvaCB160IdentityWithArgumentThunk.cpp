struct RvaCB160IdentityWithArgumentThunk
{
    RvaCB160IdentityWithArgumentThunk *identity(int unused);
};

RvaCB160IdentityWithArgumentThunk *RvaCB160IdentityWithArgumentThunk::identity(int)
{
    return this;
}
