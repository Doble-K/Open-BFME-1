struct RvaECF60IdentityWithArgumentThunk
{
    RvaECF60IdentityWithArgumentThunk *identity(int unused);
};

RvaECF60IdentityWithArgumentThunk *RvaECF60IdentityWithArgumentThunk::identity(int)
{
    return this;
}
