struct RvaE6D20IdentityWithArgumentThunk
{
    RvaE6D20IdentityWithArgumentThunk *identity(int unused);
};

RvaE6D20IdentityWithArgumentThunk *RvaE6D20IdentityWithArgumentThunk::identity(int)
{
    return this;
}
