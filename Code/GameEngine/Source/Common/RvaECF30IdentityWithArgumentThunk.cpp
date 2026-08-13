struct RvaECF30IdentityWithArgumentThunk
{
    RvaECF30IdentityWithArgumentThunk *identity(int unused);
};

RvaECF30IdentityWithArgumentThunk *RvaECF30IdentityWithArgumentThunk::identity(int)
{
    return this;
}
