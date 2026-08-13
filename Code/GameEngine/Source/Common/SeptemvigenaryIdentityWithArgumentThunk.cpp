struct SeptemvigenaryIdentityWithArgumentThunk
{
    SeptemvigenaryIdentityWithArgumentThunk *identity(int unused);
};

SeptemvigenaryIdentityWithArgumentThunk *SeptemvigenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
