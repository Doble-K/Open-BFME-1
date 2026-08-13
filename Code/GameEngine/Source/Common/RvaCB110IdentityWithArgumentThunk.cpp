struct RvaCB110IdentityWithArgumentThunk
{
    RvaCB110IdentityWithArgumentThunk *identity(int unused);
};

RvaCB110IdentityWithArgumentThunk *RvaCB110IdentityWithArgumentThunk::identity(int)
{
    return this;
}
