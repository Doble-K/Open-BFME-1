struct RvaBE980IdentityWithArgumentThunk
{
    RvaBE980IdentityWithArgumentThunk *identity(int unused);
};

RvaBE980IdentityWithArgumentThunk *RvaBE980IdentityWithArgumentThunk::identity(int)
{
    return this;
}
