struct RvaCAC90IdentityWithArgumentThunk
{
    RvaCAC90IdentityWithArgumentThunk *identity(int unused);
};

RvaCAC90IdentityWithArgumentThunk *RvaCAC90IdentityWithArgumentThunk::identity(int)
{
    return this;
}
