struct RvaCB040IdentityWithArgumentThunk
{
    RvaCB040IdentityWithArgumentThunk *identity(int unused);
};

RvaCB040IdentityWithArgumentThunk *RvaCB040IdentityWithArgumentThunk::identity(int)
{
    return this;
}
