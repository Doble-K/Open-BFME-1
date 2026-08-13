struct RvaCB090IdentityWithArgumentThunk
{
    RvaCB090IdentityWithArgumentThunk *identity(int unused);
};

RvaCB090IdentityWithArgumentThunk *RvaCB090IdentityWithArgumentThunk::identity(int)
{
    return this;
}
