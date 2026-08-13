struct TrivigenaryIdentityWithArgumentThunk
{
    TrivigenaryIdentityWithArgumentThunk *identity(int unused);
};

TrivigenaryIdentityWithArgumentThunk *TrivigenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
