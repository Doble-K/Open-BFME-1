struct SeptenaryIdentityWithArgumentThunk
{
    SeptenaryIdentityWithArgumentThunk *identity(int unused);
};

SeptenaryIdentityWithArgumentThunk *SeptenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
