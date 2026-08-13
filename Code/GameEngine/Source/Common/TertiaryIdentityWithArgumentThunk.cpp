struct TertiaryIdentityWithArgumentThunk
{
    TertiaryIdentityWithArgumentThunk *identity(int unused);
};

TertiaryIdentityWithArgumentThunk *TertiaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
