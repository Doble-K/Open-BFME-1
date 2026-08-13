struct RvaCAE90IdentityWithArgumentThunk
{
    RvaCAE90IdentityWithArgumentThunk *identity(int unused);
};

RvaCAE90IdentityWithArgumentThunk *RvaCAE90IdentityWithArgumentThunk::identity(int)
{
    return this;
}
