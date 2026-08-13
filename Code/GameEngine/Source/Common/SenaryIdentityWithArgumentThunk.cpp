struct SenaryIdentityWithArgumentThunk
{
    SenaryIdentityWithArgumentThunk *identity(int unused);
};

SenaryIdentityWithArgumentThunk *SenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
